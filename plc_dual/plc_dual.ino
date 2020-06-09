#define COUNT_SIGNALS 50 // 30 + 20
#define COUNT_STORE 6
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
#include <OneWire.h>
#include <Ticker.h>
#include "DallasTemperature.h"


#define PIN_BUTTON    10
#define PIN_LED_MODE  13
#define PIN_ONEWIRE   9
static byte pinRelays[2] = {12, 5};

/*#define PIN_BUTTON    0
#define PIN_LED_MODE  13
#define PIN_ONEWIRE   14
static byte pinRelays[2] = {12, 5};*/

struct MapNameItem {
  char* name;
  struct Signal* signal;
};
static struct MapNameItem mapSignalName[COUNT_SIGNALS];
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
  char buf[100];
  vsnprintf_P(buf, sizeof(buf), (const char*)aFormat, args);
  Serial.print(buf);
  va_end(args);
}

static struct Signal* sRelay; // relay_1, relay_2
static struct Signal* sSensor; // sensor_1, sensor_2, sensor_3, sensor_4
static struct Signal* sDI; // DI
static struct Signal* sSchedule; // schedule_1, schedule_2
static struct Signal* sStored; // stored_1, stored_2, stored_3, stored_4, stored_5, stored_6, stored_7, stored_8
static struct Signal* sVariable; // variable_1, variable_2
static struct Signal* sReverse; // reverse_1, reverse_2
static struct Signal* sScriptMode; // scriptMode
static struct Signal* sScript; // script
static struct Signal* sDebug; // debug
static struct Signal* sScheduleData; // scheduleData_1, scheduleData_2
static struct Signal* sLed; // led
static struct Signal* sIPAddress; // IPAddress
static struct Signal* sVersion; // version
static struct Signal* sUpdate; // update

static struct MgtClient client;


float variables[2] = {NAN, NAN};

static OneWire oneWire(PIN_ONEWIRE);
static DallasTemperature sensors[4] = {
  DallasTemperature(EC_config.app.romArr[0], &oneWire),
  DallasTemperature(EC_config.app.romArr[1], &oneWire),
  DallasTemperature(EC_config.app.romArr[2], &oneWire),
  DallasTemperature(EC_config.app.romArr[3], &oneWire)
};

static bool getRelay(int aNumber) {
  if (EC_config.app.reverse[aNumber])
    return !digitalRead(pinRelays[aNumber]);
  return digitalRead(pinRelays[aNumber]);
}

static void setRelay(int aNumber, bool aValue) {
  if (EC_config.app.reverse[aNumber])
    aValue = !aValue;
  digitalWrite(pinRelays[aNumber], aValue);
}


// write with confirmation for "relay"
static void write_relay(int aNumber, bool aValue) {
  setRelay(aNumber, aValue);
  signal_updateInt(sRelay + aNumber, aValue, getUTCTime());
  mgt_writeAns(&client, sRelay + aNumber, erOk); // confirmation
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


// write with confirmation for "scheduleData"
static void write_scheduleData(int aNumber, __uint8* aValue) {
  __uint16 length = (aValue[1] << 8) | aValue[0];

  int start = aNumber ? EC_config.app.schedulePtr[aNumber - 1] * 9 : 0;
  int startMove = EC_config.app.schedulePtr[aNumber] * 9;
  int shift = (length - 2) - (startMove - start);
//  int sizeMove = EC_Config.schedulePtr[3] * 9 - startMove;
  int sizeMove = EC_config.app.schedulePtr[1] * 9 - startMove;

  if (sizeMove < 0)
    sizeMove = -sizeMove;


  //if ((EC_Config.schedulePtr[3] * 9 + shift) > sizeof(EC_Config.scheduleData)) {
  if ((EC_config.app.schedulePtr[1] * 9 + shift) > sizeof(EC_config.app.scheduleData)) {
    mgt_writeAns(&client, sScheduleData + aNumber, erWriteFailed);
    return;
  }

//  for (int i = 0; i < 4; i++) {
  for (int i = 0; i < 2; i++) {
    if (i < aNumber)
      continue;
    EC_config.app.schedulePtr[i] += shift / 9;
  }

  __int16 temp = (aValue[3] << 8) | aValue[2];
  EC_config.app.bias = (__int32)temp * 60;

  memmove(EC_config.app.scheduleData + startMove + shift, EC_config.app.scheduleData + startMove, sizeMove);
  memcpy(EC_config.app.scheduleData + start, aValue + 4, length - 2);

  int end = startMove + shift;
  byte canal = aNumber << 3;
  for (int i = start; i < end; i += 9) {
    EC_config.app.scheduleData[i] &= 0x07;
    EC_config.app.scheduleData[i] |= canal;
  }

  EC_save();
  signal_updateTime(sScheduleData + aNumber, getUTCTime());
  mgt_writeAns(&client, sScheduleData + aNumber, erOk); // confirmation

  sch_init(getUTCTime());
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

// write with confirmation for "reverse"
static void write_reverse(int aNumber, bool aValue) {
  EC_config.app.reverse[aNumber] = aValue;
  EC_save();
  digitalWrite(pinRelays[aNumber], !digitalRead(pinRelays[aNumber]));
  signal_updateInt(sReverse + aNumber, aValue, getUTCTime());
  mgt_writeAns(&client, sReverse + aNumber, erOk); // confirmation
}

// write with confirmation for "led"
static void write_led(bool aValue) {
  EC_config.app.led = aValue;
  EC_save();
  
  signal_updateInt(sLed, aValue, getUTCTime());
  mgt_writeAns(&client, sLed, erOk); // confirmation
}

// write with confirmation for "update"
static void write_update(bool aValue) {
  mgt_writeAns(&client, sUpdate, erWriteFailed); // confirmation
  myUpdate();
}

static void readScheduleData(int aNumber) {
  int begin = aNumber ? EC_config.app.schedulePtr[aNumber - 1] * 9 : 0;
  int end = EC_config.app.schedulePtr[aNumber] * 9;
  __int16 value = end - begin + 2;

  __int16 bias = EC_config.app.bias / 60;

  __uint8 temp[4];
  temp[0] = *(EC_config.app.scheduleData + begin - 4);
  temp[1] = *(EC_config.app.scheduleData + begin - 3);
  temp[2] = *(EC_config.app.scheduleData + begin - 2);
  temp[3] = *(EC_config.app.scheduleData + begin - 1);

  *(EC_config.app.scheduleData + begin - 4) = *((__uint8*)&value + 0);
  *(EC_config.app.scheduleData + begin - 3) = *((__uint8*)&value + 1);
  *(EC_config.app.scheduleData + begin - 2) = *((__uint8*)&bias + 0);
  *(EC_config.app.scheduleData + begin - 1) = *((__uint8*)&bias + 1);

  signal_updatePtr(sScheduleData + aNumber, EC_config.app.scheduleData + begin - 4, getUTCTime());
  mgt_readAns(&client, sScheduleData + aNumber, erOk);

  *(EC_config.app.scheduleData + begin - 4) = temp[0];
  *(EC_config.app.scheduleData + begin - 3) = temp[1];
  *(EC_config.app.scheduleData + begin - 2) = temp[2];
  *(EC_config.app.scheduleData + begin - 1) = temp[3];
}

static void handler(enum OpCode aOpCode, struct Signal* aSignal, struct SignalValue* aWriteValue) {
  switch (aOpCode) {
    case opRead:
      if ((aSignal >= sScheduleData) && (aSignal < sLed))
        readScheduleData(aSignal - sScheduleData);
      else {
        signal_updateTime(aSignal, getUTCTime());
        mgt_readAns(&client, aSignal, erOk);
      }
      break;
    case opAttach:
        break;
    case opWrite:
      if ((aSignal >= sRelay) && (aSignal < sSensor))
        write_relay(aSignal - sRelay, aWriteValue->u.m_bool);
      else if ((aSignal >= sStored) && (aSignal < sVariable))
        write_stored(aSignal - sStored, aWriteValue->u.m_float);
      else if ((aSignal >= sVariable) && (aSignal < sReverse))
        write_variable(aSignal - sVariable, aWriteValue->u.m_float);
      else if ((aSignal >= sReverse) && (aSignal < sScriptMode))
        write_reverse(aSignal - sReverse, aWriteValue->u.m_bool);
      else if (aSignal == sScriptMode)
        write_scriptMode(aWriteValue->u.m_bool);
      else if (aSignal == sScript)
        write_script(aWriteValue->u.m_blob);
      else if (aSignal == sDebug)
        write_debug(aWriteValue->u.m_blob);
      else if ((aSignal >= sScheduleData) && (aSignal < sLed))
        write_scheduleData(aSignal - sScheduleData, aWriteValue->u.m_blob);
      else if (aSignal == sLed)
        write_led(aWriteValue->u.m_bool);
      else if (aSignal == sUpdate)
        write_update(aWriteValue->u.m_bool);

      break;
    case opWriteAsync:
      break;
    case opRecv:
      aSignal->m_value.m_time = getUTCTime();
      aSignal->m_value.u = aWriteValue->u;
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
      digitalWrite(PIN_RELAY, !digitalRead(PIN_RELAY));
      EC_config.app.scriptMode = 0; // ручной режим
    }
  }
}

void setup() {
  // Последовательный порт для отладки
  Serial.begin(115200);
  debugLog(F("\n\nFree memory %d\n"), ESP.getFreeHeap());

  pinMode(3, INPUT_PULLUP);

  // Инициализация EEPROM
  EC_begin();
  EC_read();

  // Подключаемся к WiFi
  WiFi_begin();
  if (WiFi.status() == WL_CONNECTED) blink_mode = 0B11111111;
  else blink_mode = 0B00000101;
  delay(2000);

  // Старт внутреннего WEB-сервера
  HTTP_begin();

  pinMode(PIN_LED_MODE, OUTPUT);

  DallasTemperature::convertAll(&oneWire);
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

  sRelay = mgt_createSignal(&client, "relay_1", tpBool, SEC_LEV_READ | SIG_ACCESS_READ | SIG_ACCESS_WRITE, STORE_MODE_CHANGE | STORE_UNIT_MIN | 1, 0);
  mgt_createSignal(&client, "relay_2", tpBool, SEC_LEV_READ | SIG_ACCESS_READ | SIG_ACCESS_WRITE, STORE_MODE_CHANGE | STORE_UNIT_MIN | 1, 0);
  sSensor = mgt_createSignal(&client, "sensor_1", tpFloat, SEC_LEV_READ | SIG_ACCESS_READ, STORE_MODE_AVERAGE | STORE_UNIT_SEC | 15, 0);
  mgt_createSignal(&client, "sensor_2", tpFloat, SEC_LEV_READ | SIG_ACCESS_READ, STORE_MODE_AVERAGE | STORE_UNIT_SEC | 15, 0);
  mgt_createSignal(&client, "sensor_3", tpFloat, SEC_LEV_READ | SIG_ACCESS_READ, STORE_MODE_AVERAGE | STORE_UNIT_SEC | 15, 0);
  mgt_createSignal(&client, "sensor_4", tpFloat, SEC_LEV_READ | SIG_ACCESS_READ, STORE_MODE_AVERAGE | STORE_UNIT_SEC | 15, 0);
  sDI = mgt_createSignal(&client, "DI", tpBool, SEC_LEV_READ | SIG_ACCESS_READ, STORE_MODE_OFF, 0);
  sSchedule = mgt_createSignal(&client, "schedule_1", tpBool, SEC_LEV_READ | SIG_ACCESS_READ, STORE_MODE_OFF, 0);
  mgt_createSignal(&client, "schedule_2", tpBool, SEC_LEV_READ | SIG_ACCESS_READ, STORE_MODE_OFF, 0);
  sStored = mgt_createSignal(&client, "stored_1", tpFloat, SEC_LEV_READ | SIG_ACCESS_READ | SIG_ACCESS_WRITE, STORE_MODE_OFF, 0);
  mgt_createSignal(&client, "stored_2", tpFloat, SEC_LEV_READ | SIG_ACCESS_READ | SIG_ACCESS_WRITE, STORE_MODE_OFF, 0);
  mgt_createSignal(&client, "stored_3", tpFloat, SEC_LEV_READ | SIG_ACCESS_READ | SIG_ACCESS_WRITE, STORE_MODE_OFF, 0);
  mgt_createSignal(&client, "stored_4", tpFloat, SEC_LEV_READ | SIG_ACCESS_READ | SIG_ACCESS_WRITE, STORE_MODE_OFF, 0);
  mgt_createSignal(&client, "stored_5", tpFloat, SEC_LEV_READ | SIG_ACCESS_READ | SIG_ACCESS_WRITE, STORE_MODE_OFF, 0);
  mgt_createSignal(&client, "stored_6", tpFloat, SEC_LEV_READ | SIG_ACCESS_READ | SIG_ACCESS_WRITE, STORE_MODE_OFF, 0);
  mgt_createSignal(&client, "stored_7", tpFloat, SEC_LEV_READ | SIG_ACCESS_READ | SIG_ACCESS_WRITE, STORE_MODE_OFF, 0);
  mgt_createSignal(&client, "stored_8", tpFloat, SEC_LEV_READ | SIG_ACCESS_READ | SIG_ACCESS_WRITE, STORE_MODE_OFF, 0);
  sVariable = mgt_createSignal(&client, "variable_1", tpFloat, SEC_LEV_READ | SIG_ACCESS_READ | SIG_ACCESS_WRITE, STORE_MODE_OFF, 0);
  mgt_createSignal(&client, "variable_2", tpFloat, SEC_LEV_READ | SIG_ACCESS_READ | SIG_ACCESS_WRITE, STORE_MODE_OFF, 0);
  sReverse = mgt_createSignal(&client, "reverse_1", tpBool, SEC_LEV_READ | SIG_ACCESS_READ | SIG_ACCESS_WRITE, STORE_MODE_OFF, 0);
  mgt_createSignal(&client, "reverse_2", tpBool, SEC_LEV_READ | SIG_ACCESS_READ | SIG_ACCESS_WRITE, STORE_MODE_OFF, 0);
  sScriptMode = mgt_createSignal(&client, "scriptMode", tpBool, SEC_LEV_READ | SIG_ACCESS_READ | SIG_ACCESS_WRITE, STORE_MODE_OFF, 0);
  sScript = mgt_createSignal(&client, "script", tpBlob, SEC_LEV_READ | SIG_ACCESS_READ | SIG_ACCESS_WRITE, STORE_MODE_OFF, 0);
  sDebug = mgt_createSignal(&client, "debug", tpBlob, SEC_LEV_NO_ACCESS | SIG_ACCESS_READ | SIG_ACCESS_WRITE, STORE_MODE_OFF, 0);
  sScheduleData = mgt_createSignal(&client, "scheduleData_1", tpBlob, SEC_LEV_READ | SIG_ACCESS_READ | SIG_ACCESS_WRITE, STORE_MODE_OFF, 0);
  mgt_createSignal(&client, "scheduleData_2", tpBlob, SEC_LEV_READ | SIG_ACCESS_READ | SIG_ACCESS_WRITE, STORE_MODE_OFF, 0);
  sLed = mgt_createSignal(&client, "led", tpBool, SEC_LEV_READ | SIG_ACCESS_READ | SIG_ACCESS_WRITE, STORE_MODE_OFF, 0);
  sIPAddress = mgt_createSignal(&client, "IPAddress", tpString, SEC_LEV_READ | SIG_ACCESS_READ, STORE_MODE_OFF, 0);
  sVersion = mgt_createSignal(&client, "version", tpString, SEC_LEV_READ | SIG_ACCESS_READ, STORE_MODE_OFF, 0);
  sUpdate = mgt_createSignal(&client, "update", tpBool, SEC_LEV_READ | SIG_ACCESS_READ | SIG_ACCESS_WRITE, STORE_MODE_OFF, 0);


  signal_updateInt(sScriptMode, EC_config.app.scriptMode, 0);
  signal_updateInt(sLed, EC_config.app.led, 0);

  but_init(&but, PIN_BUTTON, 2000);

  for (int i = 0; i < 2; i++) {
    pinMode(pinRelays[i], OUTPUT);
    signal_updateInt(sReverse + i, EC_config.app.reverse[i], 0);
  }

  for (int i = 0; i < 8; i++)
    signal_updateDouble(sStored + i, EC_config.app.stored[i], 0);

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

  const char* ver = "PLC Sonoff Dual R2 v0.4 30/XII/2019";

  
  signal_updatePtr(sVersion, ver, 0);

  signal_updatePtr(sScript, EC_config.app.script, 0);
  signal_updatePtr(sDebug, debugArr, 0);

  signal_updatePtr(sIPAddress, localIp, 0);

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

struct Period _1_min = { 1L * 60 * 1000, 0 };
//struct Period _801_ms = { 801, 0 };

void loop() {
  static uint32_t ms2 = 0;

  static bool synchronization = false;


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
      if (WiFi.status() == WL_CONNECTED) {
        if (sLed->m_value.u.m_bool)
          blink_mode = 0B11111111;
        else
          blink_mode = 0;
      }
      else {
        blink_mode = 0B00000101;
        WiFi_begin();
      }
    }
  }

  HTTP_loop();
  delay(1); // TODO борюсь с переконектами

  TimeStamp t = getUTCTime();

  bool temperatureDirty[4] = {false, false, false, false};
  bool relayDirty[2] = {false, false};
  bool variableDirty[2] = {false, false};
  bool DIDirty = false;
  bool scriptModeDirty = false;
  bool scheduleDirty[2] = {false, false};

  static __uint32 convertTime = 0;
  static bool convertDone = false;

  bool DI = digitalRead(3); // читаем цифровой вход
  if (sDI->m_value.u.m_bool ^ DI) {
    signal_updateInt(sDI, DI, t);
    DIDirty = true;
  }

  for (int i = 0; i < 2; i++) {
    float v = sVariable[i].m_value.u.m_float;
    if ((v == v) || (variables[i] == variables[i])) {
      if (v != variables[i]) {
        signal_updateDouble(sVariable + i, variables[i], t);
        variableDirty[i] = true;
      }
    }
  }
  
  if ((__uint32)(millis() - convertTime) >= 800) {
    //debugLog(F("pin3:%d\n"), digitalRead(3));
   
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

  for (int i = 0; i < 2; i++) {
    if (sSchedule[i].m_value.u.m_bool ^ canals[i]) {
      signal_updateInt(sSchedule + i, canals[i], t);
      scheduleDirty[i] = true;
    }
  }


  if ((sScriptMode->m_value.u.m_bool == true) && (EC_config.app.scriptMode == false)) // если нажали на механическую кнопку
    EC_save();

  if (EC_config.app.scriptMode || bk_debug) { // если работа по сценариию или отладка
    if (!bk_run())
      EC_config.app.scriptMode = false;
  }

  bool flagEvent = periodEvent(&_1_min, t);

  for (int i = 0; i < 2; i++) {
    bool relay = getRelay(i);
    if ((flagEvent) || (sRelay[i].m_value.u.m_bool ^ relay)) {
      signal_updateInt(sRelay + i, relay, t);
      relayDirty[i] = true;
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
        if (relayDirty[i])
          mgt_send(&client, sRelay + i);
        if (scheduleDirty[i])
          mgt_send(&client, sSchedule + i);
        if (variableDirty[i])
          mgt_send(&client, sVariable + i);
      }
      if (scriptModeDirty)
        mgt_send(&client, sScriptMode);
      if (DIDirty)
        mgt_send(&client, sDI);
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
        signal_updateTime(sRelay + i, t);
        mgt_send(&client, sRelay + i); // relay
        signal_updateTime(sReverse + i, t);
        mgt_send(&client, sReverse + i); // reverse
        signal_updateTime(sSchedule + i, t);
        mgt_send(&client, sSchedule + i); // schedule
        signal_updateTime(sVariable + i, t);
        mgt_send(&client, sVariable + i); // variable
      }

      signal_updateTime(sScriptMode, t);
      mgt_send(&client, sScriptMode); // scriptMode
      
      signal_updateTime(sDI, t);
      mgt_send(&client, sDI); // DI
    }
    else if (mgtState == stDisconnect) {
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
}

__int32 getBias() {
  return EC_config.app.bias;
}

__uint8 getEventInfo(__uint8 aIndex) {
  if (aIndex < EC_config.app.schedulePtr[1]) {
    __uint8* ptr = EC_config.app.scheduleData + 9 * aIndex;
    return ptr[0];
  }
  else
    return 0x80;
}

__uint32 getStartEvent(__uint8 aIndex) {
  if (aIndex < EC_config.app.schedulePtr[1]) {
    __uint8* ptr = EC_config.app.scheduleData + 1 + 9 * aIndex;
    __uint32 time = (ptr[3] << 24) + (ptr[2] << 16) + (ptr[1] << 8) + ptr[0];
    return time;
  }
  else
    return 0;
}

__uint32 getStopEvent(__uint8 aIndex) {
  if (aIndex < EC_config.app.schedulePtr[1]) {
    __uint8* ptr = EC_config.app.scheduleData + 1 + 4 + 9 * aIndex;
    __uint32 time = (ptr[3] << 24) + (ptr[2] << 16) + (ptr[1] << 8) + ptr[0];
    return time;
  }
  else
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

  struct Signal* s = sRelay;
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
    mapSignalName[lenMapSignalName].name = aName;
    mapSignalName[lenMapSignalName++].signal = s;
    s->m_value.m_time = -1; // пометим, что параметр не действителен
  }

  return s;
}


float bk_getSignal(char* aName, __uint16 aLifetime) {
  struct Signal* s = findSignal(aName);
  if (!s)
    return NAN;

  int canal = s - sRelay;
  if (canal < 2)
    return getRelay(canal);
  else if (s == sVariable)
    return variables[0];
  else if (s == (sVariable + 1))
    return variables[1];

  if (s->m_value.m_time == -1)
      return NAN;

  if (aLifetime) {
    if ((s > sUpdate) || ((s >= sSensor) && (s < sDI))) {
      TimeStamp t = getUTCTime();
      if (s->m_value.m_time + ((int)aLifetime * 1000) < t)
        return NAN;
    }
  }

  float result = convertToFloat(s);
  return result;
}

void bk_setSignal(char* aName, float aValue) {
  struct Signal* s = findSignal(aName);
  if ((s >= sRelay) && (s < sSensor)) {
    if (aValue == aValue) {
      if (aValue)
        setRelay(s - sRelay, true);
      else
        setRelay(s - sRelay, false);
    }
  }
  else if (s == sVariable)
    variables[0] = aValue;
  else if (s == (sVariable + 1))
    variables[1] = aValue;   
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
  }}

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
