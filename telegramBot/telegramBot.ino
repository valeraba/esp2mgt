#define COUNT_SIGNALS 41 // 21 + 20
#define COUNT_STORE 5
#include "Types.h"
#include "MgtClient.h"
#include "schedul.h"
#include "blockly.h"

#include "ESP8266_Board.h"
#include <ESP8266WiFi.h>
#include <ESP8266httpUpdate.h>

#include "config.h"
#include "http.h"
#include "button.h"
#include <Ticker.h>
#include <OneWire.h>
#include "DallasTemperature.h"

#include "Telegram.h"
#include "solarTime.h"

#define PIN_BUTTON    0
#define PIN_LED_MODE  13
#define PIN_ONEWIRE  2
#define PIN_DI  3



struct MapNameItem {
  char* name;
  struct Signal* signal;
};
static struct MapNameItem mapSignalName[COUNT_SIGNALS];
static TimeStamp deviceTimeArray[COUNT_SIGNALS];
static int lenMapSignalName = 0;


const char* WIFI_SSID = EC_config.net.ssid;
const char* WIFI_PASSWORD = EC_config.net.pass;

extern struct PortableSocket mySocket;

Ticker ticker;


uint8_t blink_mode = 0B00000101;
But_ctx but;

void debugLog(const __FlashStringHelper* aFormat, ...) {
  va_list args;
  va_start(args, aFormat);
  //  char buf[100];
  char buf[1024];
  vsnprintf_P(buf, sizeof(buf), (const char*)aFormat, args);
  Serial.print(buf);
  va_end(args);
}

static struct Signal* sSensor; // sensor_1, sensor_2, sensor_3, sensor_4
static struct Signal* sDI; // DI
static struct Signal* sMessage; // message
static struct Signal* sToken; // token
static struct Signal* sChatId; // chatId
static struct Signal* sStored; // stored_1, stored_2, stored_3, stored_4, stored_5
static struct Signal* sVariable; // variable_1, variable_2
static struct Signal* sScriptMode; // scriptMode
static struct Signal* sScript; // script
static struct Signal* sDebug; // debug
static struct Signal* sIPAddress; // IPAddress
static struct Signal* sVersion; // version
static struct Signal* sUpdate; // update

static struct MgtClient client;

float variables[2] = { NAN, NAN };

static OneWire oneWire(PIN_ONEWIRE);
static DallasTemperature sensors[4] = {
  DallasTemperature(EC_config.app.romArr[0], &oneWire),
  DallasTemperature(EC_config.app.romArr[1], &oneWire),
  DallasTemperature(EC_config.app.romArr[2], &oneWire),
  DallasTemperature(EC_config.app.romArr[3], &oneWire)
};


double updateChartId(double aChatId) {
  if (aChatId == aChatId) {
    EC_config.app.chatId = aChatId;
    EC_save();
    signal_updateDouble(sChatId, EC_config.app.chatId, 0);
    mgt_send(&client, sChatId);
  }
  return EC_config.app.chatId;
}
TelegramBot tlgBot(EC_config.app.token, updateChartId, "t.gate.mgt24.ru", 8080);
//TelegramBot tlgBot(EC_config.app.token, updateChartId, "192.168.1.44", 80);

char msg[256];


// write with confirmation for "token"
static void write_token(char* aValue) {
  strncpy(EC_config.app.token, aValue, sizeof(EC_config.app.token));
  EC_config.app.chatId = NAN;
  EC_save();
  mgt_writeAns(&client, sToken, erOk); // confirmation
  signal_updateDouble(sChatId, EC_config.app.chatId, getUTCTime());
  mgt_send(&client, sChatId);
}

// write with confirmation for "chatId"
static void write_chatId(double aValue) {
  EC_config.app.chatId = aValue;
  EC_save();
  signal_updateDouble(sChatId, aValue, getUTCTime());
  mgt_writeAns(&client, sChatId, erOk); // confirmation

  if (EC_config.app.token[0] && (EC_config.app.chatId == EC_config.app.chatId)) // если токет и чат установлены
    sendStartAns();
}

// write with confirmation for "stored"
static void write_stored(int aNumber, float aValue) {
  EC_config.app.stored[aNumber] = aValue;
  EC_save();
  signal_updateDouble(sStored + aNumber, aValue, getUTCTime());
  mgt_writeAns(&client, sStored + aNumber, erOk); // confirmation
}

// write with confirmation for "variable"
static void write_variable(int aNumber, float aValue) {
  variables[aNumber] = aValue;
  signal_updateDouble(sVariable + aNumber, aValue, getUTCTime());
  mgt_writeAns(&client, sVariable + aNumber, erOk); // confirmation
}

// write with confirmation for "scriptMode"
static void write_scriptMode(bool aValue) {
  EC_config.app.scriptMode = aValue;
  EC_save();

  signal_updateInt(sScriptMode, aValue, getUTCTime());
  mgt_writeAns(&client, sScriptMode, erOk);
}

// write with confirmation for "script"
static void write_script(__uint8* aValue) {
  __uint16 length = (aValue[1] << 8) | aValue[0];

  if (length <= (sizeof(EC_config.app.script) - 2)) {
    memcpy(EC_config.app.script, aValue, length + 2);
    EC_save();
    signal_updateTime(sScript, getUTCTime());
    mgt_writeAns(&client, sScript, erOk); // confirmation

    lenMapSignalName = 0;
    struct Signal* s = sUpdate + 1;
    for (int i = 0; i < 20; i++) {
      s->m_name = 0;
      s++;
    }
    mgt_detachAll(&client);

    bk_init(EC_config.app.script + 2);
  }
  else
    mgt_writeAns(&client, sScript, erWriteFailed);
}

static __uint8 debugArr[10] = { 1, 0, 0 };

// write with confirmation for "debug"
static void write_debug(__uint8* aValue) {
  __uint16 length = (aValue[1] << 8) | aValue[0];

  if (aValue[2] == 0xff) {
    bk_debug = true;
    bk_break((aValue[4] << 8) | aValue[3]);
  }
  else
    bk_debug = false;

  memcpy(debugArr, aValue, length + 2);

  mgt_writeAns(&client, sDebug, erOk); // confirmation
}


// write with confirmation for "update"
static void write_update(bool aValue) {
  mgt_writeAns(&client, sUpdate, erWriteFailed); // confirmation
  myUpdate();
}


static void handler(enum OpCode aOpCode, struct Signal* aSignal, struct SignalValue* aWriteValue) {
  switch (aOpCode) {
    case opRead:
      signal_updateTime(aSignal, getUTCTime());
      mgt_readAns(&client, aSignal, erOk);
      break;
    case opAttach:
      break;
    case opWrite:
      if (aSignal == sToken)
        write_token(aWriteValue->u.m_string);
      else if (aSignal == sChatId)
        write_chatId(aWriteValue->u.m_double);
      else if ((aSignal >= sStored) && (aSignal < sVariable))
        write_stored(aSignal - sStored, aWriteValue->u.m_float);
      else if ((aSignal >= sVariable) && (aSignal < sScriptMode))
        write_variable(aSignal - sVariable, aWriteValue->u.m_float);
      else if (aSignal == sScriptMode)
        write_scriptMode(aWriteValue->u.m_bool);
      else if (aSignal == sScript)
        write_script(aWriteValue->u.m_blob);
      else if (aSignal == sDebug)
        write_debug(aWriteValue->u.m_blob);
      else if (aSignal == sUpdate)
        write_update(aWriteValue->u.m_bool);

      break;
    case opWriteAsync:
      break;
    case opRecv:
      aSignal->m_value.m_time = getUTCTime();
      aSignal->m_value.u = aWriteValue->u;
      aSignal->m_value.m_reg = 1; // устройство на связи
      break;
    case opDetach:
      if (aSignal > sUpdate) {
        if (aSignal->m_value.m_reg == 1) { // если устройство было на связи
          aSignal->m_value.m_reg = 0; // пометим, что устройство в отрыве
          deviceTimeArray[aSignal - sUpdate - 1] = getUTCTime(); // отметим время отрыва устройства
        }
      }
      break;    
  }
}

// Событие срабатывающее каждые 25 мс
void tick() {
  static uint8_t blink_loop = 0;
  static uint8_t count = 0;
  count++;
  if (count == 5) { // cобытие срабатывающее каждые 125 мс
    count = 0;
    // Режим светодиода ищем по битовой маске
    if (blink_mode & 1 << (blink_loop & 0x07))
      digitalWrite(PIN_LED_MODE, LOW);
    else
      digitalWrite(PIN_LED_MODE, HIGH);
    blink_loop++;
  }

  uint32_t t = millis();
  but_run(&but, t);
  if (but.butInfo == BUT_NONE) {
    if (but_get(&but) == BUT_CLICK) {
    }
  }
}

void setup() {
  // Последовательный порт для отладки
  Serial.begin(115200);
  debugLog(F("\n\nFree memory %d\n"), ESP.getFreeHeap());

  // Инициализация EEPROM
  EC_begin();
  EC_read();

  solarInit(EC_config.app.latitude, EC_config.app.longitude, EC_config.app.bias);

  // Подключаемся к WiFi
  WiFi_begin();
  if (WiFi.status() == WL_CONNECTED) blink_mode = 0B11111111;
  else blink_mode = 0B00000101;
  delay(2000);

  // Старт внутреннего WEB-сервера
  HTTP_begin();

  pinMode(PIN_LED_MODE, OUTPUT);

  delay(2000);


  struct DeviceConfig deviceConfig;
  deviceConfig.m_deviceId = EC_config.net.deviceId;
  deviceConfig.m_login = 0;
  deviceConfig.m_password = EC_config.net.key;
  deviceConfig.m_debugLog = debugLog;
  deviceConfig.m_handler = handler;
  deviceConfig.m_storeFields = client.m_storeFields;
  deviceConfig.m_regSize = COUNT_STORE;

  if (!mgt_init(&client, &deviceConfig, &mySocket))
    while (1);

  sSensor = mgt_createSignal(&client, "sensor_1", tpFloat, SEC_LEV_READ | SIG_ACCESS_READ, STORE_MODE_AVERAGE | STORE_UNIT_SEC | 15, 0);
  mgt_createSignal(&client, "sensor_2", tpFloat, SEC_LEV_READ | SIG_ACCESS_READ, STORE_MODE_AVERAGE | STORE_UNIT_SEC | 15, 0);
  mgt_createSignal(&client, "sensor_3", tpFloat, SEC_LEV_READ | SIG_ACCESS_READ, STORE_MODE_AVERAGE | STORE_UNIT_SEC | 15, 0);
  mgt_createSignal(&client, "sensor_4", tpFloat, SEC_LEV_READ | SIG_ACCESS_READ, STORE_MODE_AVERAGE | STORE_UNIT_SEC | 15, 0);
  sDI = mgt_createSignal(&client, "DI", tpBool, SEC_LEV_READ | SIG_ACCESS_READ, STORE_MODE_CHANGE | STORE_UNIT_MIN | 1, 0);
  sMessage = mgt_createSignal(&client, "message", tpString, SEC_LEV_READ | SIG_ACCESS_READ, STORE_MODE_OFF, 0);
  sToken = mgt_createSignal(&client, "token", tpString, SEC_LEV_NO_ACCESS | SIG_ACCESS_READ | SIG_ACCESS_WRITE, STORE_MODE_OFF, 0);
  sChatId = mgt_createSignal(&client, "chatId", tpDouble, SEC_LEV_NO_ACCESS | SIG_ACCESS_READ | SIG_ACCESS_WRITE, STORE_MODE_OFF, 0);
  sStored = mgt_createSignal(&client, "stored_1", tpFloat, SEC_LEV_READ | SIG_ACCESS_READ | SIG_ACCESS_WRITE, STORE_MODE_OFF, 0);
  mgt_createSignal(&client, "stored_2", tpFloat, SEC_LEV_READ | SIG_ACCESS_READ | SIG_ACCESS_WRITE, STORE_MODE_OFF, 0);
  mgt_createSignal(&client, "stored_3", tpFloat, SEC_LEV_READ | SIG_ACCESS_READ | SIG_ACCESS_WRITE, STORE_MODE_OFF, 0);
  mgt_createSignal(&client, "stored_4", tpFloat, SEC_LEV_READ | SIG_ACCESS_READ | SIG_ACCESS_WRITE, STORE_MODE_OFF, 0);
  mgt_createSignal(&client, "stored_5", tpFloat, SEC_LEV_READ | SIG_ACCESS_READ | SIG_ACCESS_WRITE, STORE_MODE_OFF, 0);
  sVariable = mgt_createSignal(&client, "variable_1", tpFloat, SEC_LEV_READ | SIG_ACCESS_READ | SIG_ACCESS_WRITE, STORE_MODE_OFF, 0);
  mgt_createSignal(&client, "variable_2", tpFloat, SEC_LEV_READ | SIG_ACCESS_READ | SIG_ACCESS_WRITE, STORE_MODE_OFF, 0);
  sScriptMode = mgt_createSignal(&client, "scriptMode", tpBool, SEC_LEV_READ | SIG_ACCESS_READ | SIG_ACCESS_WRITE, STORE_MODE_OFF, 0);
  sScript = mgt_createSignal(&client, "script", tpBlob, SEC_LEV_READ | SIG_ACCESS_READ | SIG_ACCESS_WRITE, STORE_MODE_OFF, 0);
  sDebug = mgt_createSignal(&client, "debug", tpBlob, SEC_LEV_NO_ACCESS | SIG_ACCESS_READ | SIG_ACCESS_WRITE, STORE_MODE_OFF, 0);
  sIPAddress = mgt_createSignal(&client, "IPAddress", tpString, SEC_LEV_READ | SIG_ACCESS_READ, STORE_MODE_OFF, 0);
  sVersion = mgt_createSignal(&client, "version", tpString, SEC_LEV_READ | SIG_ACCESS_READ, STORE_MODE_OFF, 0);
  sUpdate = mgt_createSignal(&client, "update", tpBool, SEC_LEV_READ | SIG_ACCESS_READ | SIG_ACCESS_WRITE, STORE_MODE_OFF, 0);


  pinMode(PIN_DI, INPUT_PULLUP);

  but_init(&but, PIN_BUTTON, 2000);

  delay(1); // разобъём долгую инициализацию
  bool newFind = false;
  for (int i = 0; i < 4; i++) {
    if (EC_config.app.romArr[i][0] == 0) {
      if (!sensors[i].search(EC_config.app.romArr, 4))
        break;
      newFind = true;
    }
  }
  if (newFind)
    EC_save(); // сохраним новые привязки

  for (int i = 0; i < 5; i++)
    signal_updateDouble(sStored + i, EC_config.app.stored[i], 0);
  for (int i = 0; i < 2; i++)
    signal_updateDouble(sVariable + i, variables[i], 0);


  msg[0] = 0;
  signal_updatePtr(sMessage, msg, 0);
  signal_updatePtr(sToken, EC_config.app.token, 0);
  signal_updateDouble(sChatId, EC_config.app.chatId, 0);

  signal_updateInt(sScriptMode, EC_config.app.scriptMode, 0);
  signal_updatePtr(sScript, EC_config.app.script, 0);
  signal_updatePtr(sDebug, debugArr, 0);
  signal_updatePtr(sIPAddress, localIp, 0);

  const char* ver = "Telegram Bot v0.43 24/I/2021";
  signal_updatePtr(sVersion, ver, 0);

  bk_init(EC_config.app.script + 2);
  mgt_start(&client, EC_config.net.host1);

  ticker.attach_ms(25, tick);
}



struct Period {
  TimeStamp m_interval; // интервал в миллисекундах
  TimeStamp m_last; // установить в 0
};

static bool periodEvent(struct Period* aPeriod, TimeStamp aTime) {
  TimeStamp t = aTime / aPeriod->m_interval;
  if (aPeriod->m_last != t) {
    aPeriod->m_last = t;
    return true;
  }
  return false;
}

struct Period _5_sec = { 1L * 5 * 1000, 0 };
struct Period _1_min = { 1L * 60 * 1000, 0 };
static bool synchronization = false;


void sendStartAns() {
  char buf[64];
  snprintf(buf, sizeof(buf), "Start OK. The number of your chat: %.f", EC_config.app.chatId);
  tlgBot.sendMessage(buf);
}

bool msgDirty;


void loop() {
  static uint32_t ms2 = 0;

  uint32_t ms = millis();
  switch (but_get(&but)) {
    case BUT_LONG_DOWN:
      isAP = !isAP;
      if (isAP) {
        blink_mode = 0B00010001;
        WiFi_begin();
      }
      break;
    default:
      break;
  }

  if (ms < ms2 || (ms - ms2) > 500) {
    ms2 = ms;
    if (isAP == false) {
      if (WiFi.status() == WL_CONNECTED)
        blink_mode = 0B11111111;
      else {
        blink_mode = 0B00000101;
        WiFi_begin();
      }
    }
  }

  HTTP_loop();
  delay(1); // TODO борюсь с переконектами


  TimeStamp t = getUTCTime();

  if (EC_config.app.token[0] && (EC_config.app.chatId != EC_config.app.chatId)) { // если токет установлен, а чат не прописан
    if (periodEvent(&_5_sec, t)) {
      if (tlgBot.getUpdates())
        sendStartAns();
      return;
    }
  }


  bool temperatureDirty[4] = { false, false, false, false };
  bool variableDirty[2] = {false, false};
  bool DIDirty = false;
  bool scriptModeDirty = false;
  msgDirty = false;

  static __uint32 convertTime = 0;
  static bool convertDone = false;

  bool flagEvent = periodEvent(&_1_min, t);


  bool DI = digitalRead(PIN_DI); // читаем цифровой вход
  if (flagEvent || (sDI->m_value.u.m_bool ^ DI)) {
    signal_updateInt(sDI, DI, t);
    DIDirty = true;
  }


  if ((__uint32)(millis() - convertTime) >= 800) {
    bool errorRead = false;
    if (convertDone) {
      convertDone = false;
      for (int i = 0; i < 4; i++) {
        temperatureDirty[i] = sensors[i].read();
        if (temperatureDirty[i]) {
          signal_updateDouble(sSensor + i, sensors[i].value, t);
          errorRead = true;
        }
      }
    }
    if (!errorRead) {
      if (DallasTemperature::convertAll(&oneWire))
        convertDone = true;
      else
        convertDone = false;
    }
    convertTime = millis();
  }

  if (synchronization)
    sch_run(t);

  if (EC_config.app.scriptMode || bk_debug) { // если работа по сценариию или отладка
    if (!bk_run())
      EC_config.app.scriptMode = false;
  }

  for (int i = 0; i < 2; i++) {
    float v = sVariable[i].m_value.u.m_float;
    if ((v == v) || (variables[i] == variables[i])) { // NAN отправляется только по изменению
      if (flagEvent || (v != variables[i])) {
        signal_updateDouble(sVariable + i, variables[i], t);
        variableDirty[i] = true;
      }
    }
  }



  if (sScriptMode->m_value.u.m_bool ^ EC_config.app.scriptMode) {
    signal_updateInt(sScriptMode, EC_config.app.scriptMode, t);
    scriptModeDirty = true;
  }

  static bool toggleServer = false;

  if (!isAP) {
    MgtState mgtState = mgt_run(&client);
    if (mgtState == stConnected) {
      for (int i = 0; i < 4; i++) {
        if (temperatureDirty[i])
          mgt_send(&client, sSensor + i);
      }
      for (int i = 0; i < 2; i++) {
        if (variableDirty[i])
          mgt_send(&client, sVariable + i);
      }

      if (DIDirty)
        mgt_send(&client, sDI);
      if (scriptModeDirty)
        mgt_send(&client, sScriptMode);
      if (msgDirty)
        mgt_send(&client, sMessage);
    }
    else if (mgtState == stEstablished) {
      TimeStamp t = getUTCTime();
      sch_init(t);
      synchronization = true;

      for (int i = 0; i < 4; i++) {
        if (temperatureDirty[i]) {
          signal_updateTime(sSensor + i, t);
          mgt_send(&client, sSensor + i);
        }
      }
      for (int i = 0; i < 2; i++) {
        if (variables[i] == variables[i]) { // NAN не будем отправлять (хотя клиенты могут его вычитать), чтобы не инициировать архивирование параметра
          signal_updateTime(sVariable + i, t);
          mgt_send(&client, sVariable + i); // variable
        }
      }

      signal_updateTime(sDI, t);
      mgt_send(&client, sDI); // DI
      signal_updateTime(sScriptMode, t);
      mgt_send(&client, sScriptMode); // scriptMode
    }
    else if (mgtState == stDisconnect) {
      struct Signal* s = sUpdate + 1;
      for (int i = 0; i < lenMapSignalName; i++)
        s[i].m_value.m_reg = 0; // нет связи с удалённым устройством

      if (strlen(EC_config.net.host2)) {
        mgt_stop(&client, 0);
        if (toggleServer) {
          toggleServer = false;
          mgt_start(&client, EC_config.net.host1);
          debugLog(F("start %s\n"), EC_config.net.host1);
        }
        else {
          toggleServer = true;
          mgt_start(&client, EC_config.net.host2);
          debugLog(F("start %s\n"), EC_config.net.host2);
        }
      }
    }
  }

  if (msgDirty)
    tlgBot.sendMessage(msg);

}

__int32 getBias() {
  return EC_config.app.bias;
}

__uint8 getEventInfo(__uint8 aIndex) {
    return 0x80;
}

__uint32 getStartEvent(__uint8 aIndex) {
    return 0;
}

__uint32 getStopEvent(__uint8 aIndex) {
    return 0;
}

static float convertToFloat(struct Signal* aSignal) {
  switch (aSignal->st.m_type) {
    case tpBool:
      return aSignal->m_value.u.m_bool;
    case tpInt8:
      return aSignal->m_value.u.m_uint8;
    case tpUInt8:
      return aSignal->m_value.u.m_uint8;
    case tpInt16:
      return aSignal->m_value.u.m_int16;
    case tpUInt16:
      return aSignal->m_value.u.m_uint16;
    case tpInt32:
      return (float)aSignal->m_value.u.m_int32;
    case tpUInt32:
      return (float)aSignal->m_value.u.m_uint32;
    case tpFloat:
      return aSignal->m_value.u.m_float;
    case tpDouble:
      return (float)aSignal->m_value.u.m_double;
    default:
      return NAN;
  }
}


static struct Signal* findSignal(char* aName) {
  for (int i = 0; i < lenMapSignalName; i++) {
    if (mapSignalName[i].name == aName)
      return mapSignalName[i].signal; // если нашли в кэше
  }

  struct Signal* s = sSensor;
  for (int i = 0; i < COUNT_SIGNALS; i++) {
    if (s->m_name) {
      if (strcmp(s->m_name, aName) == 0) {
        // добавим в кэш
        mapSignalName[lenMapSignalName].name = aName;
        mapSignalName[lenMapSignalName++].signal = s;
        return s;
      }
    }
    s++;
  }


  s = mgt_attachSignal(&client, aName);
  if (s) {
    // добавим в кэш
    deviceTimeArray[lenMapSignalName] = -1; // сбросим время отрыва устройства
    
    mapSignalName[lenMapSignalName].name = aName;
    mapSignalName[lenMapSignalName++].signal = s;
    s->m_value.m_time = -1; // пометим, что параметр не действителен
    s->m_value.m_reg = 0; 
  }

  return s;
}


float bk_getSignal(char* aName, __int16 aLifetime) {
  struct Signal* s = findSignal(aName);
  if (!s)
    return NAN;

  if (s->m_value.m_time == -1)
    return NAN;

  if ((s >= sVariable) && (s < sScriptMode))
    return variables[s - sVariable];

  if (aLifetime != 0) {
    if (aLifetime > 0) {
      if ((s > sUpdate) || ((s >= sSensor) && (s < sDI))) {
        TimeStamp t = getUTCTime();
        if (s->m_value.m_time + ((int)aLifetime * 1000) < t)
          return NAN;
      }
    }
    else {
      if (s > sUpdate) {
        TimeStamp t = getUTCTime();
        if ((s->m_value.m_reg == 0) && (deviceTimeArray[s - sUpdate - 1] - ((int)aLifetime * 1000) < t))
          return NAN;
      }
    }
  }

  float result = convertToFloat(s);
  return result;
}

void joinMsg(const char* aStr) {
  if (!msgDirty) // если это начало телеграммы
    msg[0] = 0;

  int len1 = strlen(msg);
  int len2 = strlen(aStr);
  int len = len1 + len2;
  if (len <= 255) {
    memcpy(msg + len1, aStr, len2);
    msg[len] = 0;
    msgDirty = true;
  }
}

void bk_setSignal(char* aName, float aValue) {
  struct Signal* s = findSignal(aName);

  if (s == sMessage) {
    char buf[50];
    snprintf(buf, sizeof(buf), "%.6g", aValue);
    joinMsg(buf);
  }
  else if ((s >= sVariable) && (s < sScriptMode))
    variables[s - sVariable] = aValue;

}

void bk_setSignal(char* aName, const char* aStr) {
  struct Signal* s = findSignal(aName);

  if (s == sMessage)
    joinMsg(aStr);
}

void bk_print(float aValue) {
  if (bk_debug) {
    if (mgt_getState(&client) == stConnected) {
      __uint8 buf[7];
      buf[0] = 5;
      buf[1] = 0;
      buf[2] = 0xfc;
      buf[3] = *((__uint8*)&aValue + 0);
      buf[4] = *((__uint8*)&aValue + 1);
      buf[5] = *((__uint8*)&aValue + 2);
      buf[6] = *((__uint8*)&aValue + 3);

      signal_updatePtr(sDebug, buf, 0);
      mgt_send(&client, sDebug);
      signal_updatePtr(sDebug, debugArr, 0);
    }
    sleepms(100);
  }
}

void bk_prints(const char* aStr) {
  if (bk_debug) {
    if (mgt_getState(&client) == stConnected) {
      char buf[256];
      //int count = sprintf(buf + 3, "%s", aStr);
      int count = snprintf(buf + 3, sizeof(buf) - 3, "%s", aStr);
      count += 2;
      buf[0] = (__uint8)count;
      buf[1] = (__uint8)(count >> 8);
      buf[2] = 0xfd;

      signal_updatePtr(sDebug, buf, 0);
      mgt_send(&client, sDebug);
      signal_updatePtr(sDebug, debugArr, 0);
    }
    sleepms(100);
  }
}

Time* m_clock = sch_getTime();


float bk_getTime(__uint8 aOp) {
  if (!synchronization)
    return NAN;
  float f;
  switch (aOp) {
    case 1:
      f = m_clock->Hour * 3600 + m_clock->Minute * 60 + m_clock->Second;
      break;
    case 2:
      f = m_clock->total_sec / 86400;
      break;
    case 3:
      f = m_clock->Second;
      break;
    case 4:
      f = m_clock->Minute;
      break;
    case 5:
      f = m_clock->Hour;
      break;
    case 6: {
        __uint8 wday = m_clock->Wday + 1;
        if (wday == 7)
          wday = 0;
        f = wday;
        break;
      }
    case 7:
      f = m_clock->Day;
      break;
    case 8:
      f = m_clock->Month;
      break;
    case 9:
      f = m_clock->Year + 1970;
      break;
    case 10: // sunrise
      f = solarCompute(m_clock->Day, m_clock->Month, true);
      break;
    case 11: // sunset
      f = solarCompute(m_clock->Day, m_clock->Month, false);
      break;    
    default:
      f = NAN;
      break;
  }
  return f;
}

void bk_onBreak(__uint16 aPoint) {
  if (mgt_getState(&client) == stConnected) {
    debugArr[0] = 3;
    debugArr[1] = 0;
    debugArr[2] = 0xfe;
    debugArr[3] = (__uint8)aPoint;
    debugArr[4] = *((__uint8*)&aPoint + 1);

    signal_updatePtr(sDebug, debugArr, 0);
    mgt_send(&client, sDebug);
  }
}


void myUpdate() {
  debugLog(F("Update sketch...\n"));
  ESPhttpUpdate.rebootOnUpdate(false);
  char url[25 + 10 + 1] = "http://mgt24.ru/firmware/";
  itoa(EC_config.net.deviceId, url + 25, 10);
  t_httpUpdate_return ret = ESPhttpUpdate.update(url);
  switch (ret) {
    case HTTP_UPDATE_FAILED:
      debugLog(F("HTTP_UPDATE_FAILD Error (%d): %s\n"), ESPhttpUpdate.getLastError(), ESPhttpUpdate.getLastErrorString().c_str());
      break;

    case HTTP_UPDATE_NO_UPDATES:
      debugLog(F("HTTP_UPDATE_NO_UPDATES\n"));
      break;

    case HTTP_UPDATE_OK:
      debugLog(F("HTTP_UPDATE_OK\n"));
      myReset();
      break;
  }
}

void myReset() {
  debugLog(F("\nReset\n"));
  ESP.restart();
}
