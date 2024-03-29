/*
Copyright © 2015, BVAgile. All rights reserved.
Contacts: <bvagile@gmail.com>
*/

#define COUNT_SIGNALS 64 // 44 + 20
#define COUNT_STORE 17
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
#include "solarTime.h"


#define PIN_BUTTON      0
#define PIN_LED_MODE    2
#define PIN_ONEWIRE     13 // D7

static byte pinDIO[5] = {5, 4, 14, 12, 3};

struct MapNameItem {
  char* name;
  struct Signal* signal;
};
static struct MapNameItem mapSignalName[COUNT_SIGNALS];
static TimeStamp deviceTimeArray[20];
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

static struct Signal* sDIO; // D1(5), D2(4), D5(14), D6(12), RX(3)
static struct Signal* sA0; // A0
static struct Signal* sSensor; // sensor_1, sensor_2, sensor_3, sensor_4
static struct Signal* sSchedule; // schedule_1, schedule_2, schedule_3, schedule_4
static struct Signal* sStored; // stored_1, stored_2, stored_3, stored_4, stored_5, stored_6, stored_7, stored_8
static struct Signal* sVariable; // variable_1, variable_2, variable_3, variable_4, variable_5, variable_6, variable_7, variable_8
static struct Signal* sDIOMode; // D1_mode, D2_mode, D5_mode, D6_mode
static struct Signal* sScriptMode; // scriptMode
static struct Signal* sScript; // script
static struct Signal* sDebug; // debug
static struct Signal* sScheduleData; // scheduleData_1, scheduleData_2, scheduleData_3, scheduleData_4
static struct Signal* sIPAddress; // IPAddress
static struct Signal* sVersion; // version
static struct Signal* sUpdate; // update

static struct MgtClient client;

float variables[8] = { NAN, NAN, NAN, NAN, NAN, NAN, NAN, NAN };

static OneWire oneWire(PIN_ONEWIRE);
static DallasTemperature sensors[4] = {
  DallasTemperature(EC_config.app.romArr[0], &oneWire),
  DallasTemperature(EC_config.app.romArr[1], &oneWire),
  DallasTemperature(EC_config.app.romArr[2], &oneWire),
  DallasTemperature(EC_config.app.romArr[3], &oneWire)
};


// write with confirmation for "DIO"
static void write_DIO(int aNumber, bool aValue) {
  if ((EC_config.app.DIOMode[aNumber] & 0x01) != 1) {
    mgt_writeAns(&client, sDIO + aNumber, erWriteFailed);
    return;
  }
  digitalWrite(pinDIO[aNumber], (EC_config.app.DIOMode[aNumber] & 0x80) ? (!aValue) : aValue);
  signal_updateInt(sDIO + aNumber, aValue, getUTCTime());
  mgt_writeAns(&client, sDIO + aNumber, erOk); // confirmation

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
  int sizeMove = EC_config.app.schedulePtr[3] * 9 - startMove;

  if (sizeMove < 0)
    sizeMove = -sizeMove;


  if ((EC_config.app.schedulePtr[3] * 9 + shift) > sizeof(EC_config.app.scheduleData)) {
    mgt_writeAns(&client, sScheduleData + aNumber, erWriteFailed);
    return;
  }

  for (int i = 0; i < 4; i++) {
    if (i < aNumber)
      continue;
    EC_config.app.schedulePtr[i] += shift / 9;
  }

  //__int16 temp = (aValue[3] << 8) | aValue[2];
  //EC_config.app.bias = (__int32)temp * 60;

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

// write with confirmation for "DIOMode"
static void write_DIOMode(int aNumber, __uint8 aValue) {
  if ((aValue & 0x7f) > 2) {
    mgt_writeAns(&client, sDIOMode + aNumber, erWriteFailed);
    return;
  }
  pinMode(pinDIO[aNumber], aValue & 0x7f);
  EC_config.app.DIOMode[aNumber] = aValue;
  EC_save();
  signal_updateInt(sDIOMode + aNumber, aValue, getUTCTime());
  mgt_writeAns(&client, sDIOMode + aNumber, erOk); // confirmation
}

// write with confirmation for "update"
static void write_update(bool aValue) {
  mgt_writeAns(&client, sUpdate, erWriteFailed); // confirmation
  myUpdate();
}

static void readScheduleData(int aNumber, enum OpCode aOpCode) {
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

  if (aOpCode == opRead) {
    signal_updatePtr(sScheduleData + aNumber, EC_config.app.scheduleData + begin - 4, getUTCTime());
    mgt_readAns(&client, sScheduleData + aNumber, erOk);
  }
  else {
    signal_updatePtr(sScheduleData + aNumber, EC_config.app.scheduleData + begin - 4, LLONG_MIN);
    mgt_send(&client, sScheduleData + aNumber);
  }

  *(EC_config.app.scheduleData + begin - 4) = temp[0];
  *(EC_config.app.scheduleData + begin - 3) = temp[1];
  *(EC_config.app.scheduleData + begin - 2) = temp[2];
  *(EC_config.app.scheduleData + begin - 1) = temp[3];
}

static void handler(enum OpCode aOpCode, struct Signal* aSignal, struct SignalValue* aWriteValue) {
  switch (aOpCode) {
    case opRead:
      if ((aSignal >= sScheduleData) && (aSignal < sIPAddress))
        readScheduleData(aSignal - sScheduleData, aOpCode);
      else {
        signal_updateTime(aSignal, getUTCTime());
        mgt_readAns(&client, aSignal, erOk);
      }
      break;
    case opAttach:
/*      if ((aSignal >= sScheduleData) && (aSignal < sIPAddress))
        readScheduleData(aSignal - sScheduleData, aOpCode);
      else
        mgt_send(&client, aSignal);*/
     if ((aSignal >= sDIO) && (aSignal < sScript))
        mgt_send(&client, aSignal);
      break;

    case opWrite:
      if ((aSignal >= sDIO) && (aSignal < (sDIO + 5))) // кроме RX
        write_DIO(aSignal - sDIO, aWriteValue->u.m_bool);
      else if ((aSignal >= sStored) && (aSignal < sVariable))
        write_stored(aSignal - sStored, aWriteValue->u.m_float);
      else if ((aSignal >= sVariable) && (aSignal < sDIOMode))
        write_variable(aSignal - sVariable, aWriteValue->u.m_float);
      else if ((aSignal >= sDIOMode) && (aSignal < sScriptMode))
        write_DIOMode(aSignal - sDIOMode, aWriteValue->u.m_uint8);
      else if (aSignal == sScriptMode)
        write_scriptMode(aWriteValue->u.m_bool);
      else if (aSignal == sScript)
        write_script(aWriteValue->u.m_blob);
      else if (aSignal == sDebug)
        write_debug(aWriteValue->u.m_blob);
      else if ((aSignal >= sScheduleData) && (aSignal < sIPAddress))
        write_scheduleData(aSignal - sScheduleData, aWriteValue->u.m_blob);
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

}

__uint16 getStoreMode(__uint8 aNum) {
  if (EC_config.app.history & (1 << aNum))
    return STORE_MODE_CHANGE | STORE_UNIT_MIN | 1;
  return STORE_MODE_OFF;
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

  sDIO = mgt_createSignal(&client, "D1", tpBool, SEC_LEV_READ | SIG_ACCESS_READ | SIG_ACCESS_WRITE, getStoreMode(0), 0);
  mgt_createSignal(&client, "D2", tpBool, SEC_LEV_READ | SIG_ACCESS_READ | SIG_ACCESS_WRITE, getStoreMode(1), 0);
  mgt_createSignal(&client, "D5", tpBool, SEC_LEV_READ | SIG_ACCESS_READ | SIG_ACCESS_WRITE, getStoreMode(2), 0);
  mgt_createSignal(&client, "D6", tpBool, SEC_LEV_READ | SIG_ACCESS_READ | SIG_ACCESS_WRITE, getStoreMode(3), 0);
  mgt_createSignal(&client, "RX", tpBool, SEC_LEV_READ | SIG_ACCESS_READ, getStoreMode(4), 0);
  sA0 = mgt_createSignal(&client, "A0", tpFloat, SEC_LEV_READ | SIG_ACCESS_READ, STORE_MODE_OFF, 0);
  sSensor = mgt_createSignal(&client, "sensor_1", tpFloat, SEC_LEV_READ | SIG_ACCESS_READ, STORE_MODE_AVERAGE | STORE_UNIT_SEC | 15, 0);
  mgt_createSignal(&client, "sensor_2", tpFloat, SEC_LEV_READ | SIG_ACCESS_READ, STORE_MODE_AVERAGE | STORE_UNIT_SEC | 15, 0);
  mgt_createSignal(&client, "sensor_3", tpFloat, SEC_LEV_READ | SIG_ACCESS_READ, STORE_MODE_AVERAGE | STORE_UNIT_SEC | 15, 0);
  mgt_createSignal(&client, "sensor_4", tpFloat, SEC_LEV_READ | SIG_ACCESS_READ, STORE_MODE_AVERAGE | STORE_UNIT_SEC | 15, 0);
  sSchedule = mgt_createSignal(&client, "schedule_1", tpBool, SEC_LEV_READ | SIG_ACCESS_READ, STORE_MODE_OFF, 0);
  mgt_createSignal(&client, "schedule_2", tpBool, SEC_LEV_READ | SIG_ACCESS_READ, STORE_MODE_OFF, 0);
  mgt_createSignal(&client, "schedule_3", tpBool, SEC_LEV_READ | SIG_ACCESS_READ, STORE_MODE_OFF, 0);
  mgt_createSignal(&client, "schedule_4", tpBool, SEC_LEV_READ | SIG_ACCESS_READ, STORE_MODE_OFF, 0);
  sStored = mgt_createSignal(&client, "stored_1", tpFloat, SEC_LEV_READ | SIG_ACCESS_READ | SIG_ACCESS_WRITE, STORE_MODE_OFF, 0);
  mgt_createSignal(&client, "stored_2", tpFloat, SEC_LEV_READ | SIG_ACCESS_READ | SIG_ACCESS_WRITE, STORE_MODE_OFF, 0);
  mgt_createSignal(&client, "stored_3", tpFloat, SEC_LEV_READ | SIG_ACCESS_READ | SIG_ACCESS_WRITE, STORE_MODE_OFF, 0);
  mgt_createSignal(&client, "stored_4", tpFloat, SEC_LEV_READ | SIG_ACCESS_READ | SIG_ACCESS_WRITE, STORE_MODE_OFF, 0);
  mgt_createSignal(&client, "stored_5", tpFloat, SEC_LEV_READ | SIG_ACCESS_READ | SIG_ACCESS_WRITE, STORE_MODE_OFF, 0);
  mgt_createSignal(&client, "stored_6", tpFloat, SEC_LEV_READ | SIG_ACCESS_READ | SIG_ACCESS_WRITE, STORE_MODE_OFF, 0);
  mgt_createSignal(&client, "stored_7", tpFloat, SEC_LEV_READ | SIG_ACCESS_READ | SIG_ACCESS_WRITE, STORE_MODE_OFF, 0);
  mgt_createSignal(&client, "stored_8", tpFloat, SEC_LEV_READ | SIG_ACCESS_READ | SIG_ACCESS_WRITE, STORE_MODE_OFF, 0);
  sVariable = mgt_createSignal(&client, "variable_1", tpFloat, SEC_LEV_READ | SIG_ACCESS_READ | SIG_ACCESS_WRITE, getStoreMode(5), 0);
  mgt_createSignal(&client, "variable_2", tpFloat, SEC_LEV_READ | SIG_ACCESS_READ | SIG_ACCESS_WRITE, getStoreMode(6), 0);
  mgt_createSignal(&client, "variable_3", tpFloat, SEC_LEV_READ | SIG_ACCESS_READ | SIG_ACCESS_WRITE, getStoreMode(7), 0);
  mgt_createSignal(&client, "variable_4", tpFloat, SEC_LEV_READ | SIG_ACCESS_READ | SIG_ACCESS_WRITE, getStoreMode(8), 0);
  mgt_createSignal(&client, "variable_5", tpFloat, SEC_LEV_READ | SIG_ACCESS_READ | SIG_ACCESS_WRITE, getStoreMode(9), 0);
  mgt_createSignal(&client, "variable_6", tpFloat, SEC_LEV_READ | SIG_ACCESS_READ | SIG_ACCESS_WRITE, getStoreMode(10), 0);
  mgt_createSignal(&client, "variable_7", tpFloat, SEC_LEV_READ | SIG_ACCESS_READ | SIG_ACCESS_WRITE, getStoreMode(11), 0);
  mgt_createSignal(&client, "variable_8", tpFloat, SEC_LEV_READ | SIG_ACCESS_READ | SIG_ACCESS_WRITE, getStoreMode(12), 0);
  sDIOMode = mgt_createSignal(&client, "D1_mode", tpUInt8, SEC_LEV_READ | SIG_ACCESS_READ | SIG_ACCESS_WRITE, STORE_MODE_OFF, 0);
  mgt_createSignal(&client, "D2_mode", tpUInt8, SEC_LEV_READ | SIG_ACCESS_READ | SIG_ACCESS_WRITE, STORE_MODE_OFF, 0);
  mgt_createSignal(&client, "D5_mode", tpUInt8, SEC_LEV_READ | SIG_ACCESS_READ | SIG_ACCESS_WRITE, STORE_MODE_OFF, 0);
  mgt_createSignal(&client, "D6_mode", tpUInt8, SEC_LEV_READ | SIG_ACCESS_READ | SIG_ACCESS_WRITE, STORE_MODE_OFF, 0);
  sScriptMode = mgt_createSignal(&client, "scriptMode", tpBool, SEC_LEV_READ | SIG_ACCESS_READ | SIG_ACCESS_WRITE, STORE_MODE_OFF, 0);
  sScript = mgt_createSignal(&client, "script", tpBlob, SEC_LEV_READ | SIG_ACCESS_READ | SIG_ACCESS_WRITE, STORE_MODE_OFF, 0);
  sDebug = mgt_createSignal(&client, "debug", tpBlob, SEC_LEV_NO_ACCESS | SIG_ACCESS_READ | SIG_ACCESS_WRITE, STORE_MODE_OFF, 0);
  sScheduleData = mgt_createSignal(&client, "scheduleData_1", tpBlob, SEC_LEV_READ | SIG_ACCESS_READ | SIG_ACCESS_WRITE, STORE_MODE_OFF, 0);
  mgt_createSignal(&client, "scheduleData_2", tpBlob, SEC_LEV_READ | SIG_ACCESS_READ | SIG_ACCESS_WRITE, STORE_MODE_OFF, 0);
  mgt_createSignal(&client, "scheduleData_3", tpBlob, SEC_LEV_READ | SIG_ACCESS_READ | SIG_ACCESS_WRITE, STORE_MODE_OFF, 0);
  mgt_createSignal(&client, "scheduleData_4", tpBlob, SEC_LEV_READ | SIG_ACCESS_READ | SIG_ACCESS_WRITE, STORE_MODE_OFF, 0);
  sIPAddress = mgt_createSignal(&client, "IPAddress", tpString, SEC_LEV_READ | SIG_ACCESS_READ, STORE_MODE_OFF, 0);
  sVersion = mgt_createSignal(&client, "version", tpString, SEC_LEV_READ | SIG_ACCESS_READ, STORE_MODE_OFF, 0);
  sUpdate = mgt_createSignal(&client, "update", tpBool, SEC_LEV_READ | SIG_ACCESS_READ | SIG_ACCESS_WRITE, STORE_MODE_OFF, 0);


  TimeStamp t = getUTCTime();

  signal_updateInt(sScriptMode, EC_config.app.scriptMode, t);
  but_init(&but, PIN_BUTTON, 2000);

  for (int i = 0; i < 4; i++) {
    digitalWrite(pinDIO[i], (EC_config.app.DIOMode[i] & 0x80) ? true : false);
    signal_updateInt(sDIOMode + i, EC_config.app.DIOMode[i], t);
    pinMode(pinDIO[i], EC_config.app.DIOMode[i] & 0x7f);

    signal_updateDouble(sSensor + i, NAN, t);
  }
  pinMode(pinDIO[4], INPUT_PULLUP); // RX

  for (int i = 0; i < 8; i++) {
    signal_updateDouble(sStored + i, EC_config.app.stored[i], t);
    signal_updateDouble(sVariable + i, variables[i], t);
  }

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


  const char* ver = "PLC NodeMCU v1.0 02/XIII/2021";
  signal_updatePtr(sVersion, ver, t);

  signal_updatePtr(sScript, EC_config.app.script, t);
  signal_updatePtr(sDebug, debugArr, t);

  signal_updatePtr(sIPAddress, localIp, t);

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
struct Period _1_sec = { 1L * 1000, 0 };

static bool synchronization = false;

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

  if (!isAP) { // если НЕ режим точки доступа

    TimeStamp t = getUTCTime();

    bool temperatureDirty[4] = {false, false, false, false};
    bool DIODirty[5] = {false, false, false, false , false};
    bool A0Dirty = false;
    bool variableDirty[8] = {false, false, false, false, false, false, false, false};
    bool scheduleDirty[4] = {false, false, false, false};

    static __uint32 convertTime = 0;
    static bool convertDone = false;

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

    int analog = analogRead(PIN_A0);
    sleepms(2);
    if ((abs(sA0->m_value.u.m_float - analog) >= 10) || (periodEvent(&_1_sec, t))) {
      signal_updateDouble(sA0, analog, t);
      A0Dirty = true;
    }

    bool flagEvent = periodEvent(&_1_min, t);

    for (int i = 0; i < 4; i++) {
      if (sSchedule[i].m_value.u.m_bool ^ canals[i]) {
        signal_updateInt(sSchedule + i, canals[i], t);
        scheduleDirty[i] = true;
      }
    }

    if (EC_config.app.scriptMode || bk_debug) { // если работа по сценариию или отладка
      if (!bk_run())
        EC_config.app.scriptMode = false;
    }

    for (int i = 0; i < 8; i++) {
      float v = sVariable[i].m_value.u.m_float;
      if ((v == v) || (variables[i] == variables[i])) { // NAN отправляется только по изменению
        if (flagEvent || (v != variables[i])) {
          signal_updateDouble(sVariable + i, variables[i], t);
          variableDirty[i] = true;
        }
      }
    }

    for (int i = 0; i < 5; i++) {
      bool dio = digitalRead(pinDIO[i]);
      if (i < 4) {
        if (EC_config.app.DIOMode[i] & 0x80)
          dio = !dio;
      }
      if ((flagEvent) || (sDIO[i].m_value.u.m_bool ^ dio)) {
        signal_updateInt(sDIO + i, dio, t);
        DIODirty[i] = true;
      }
    }



    static bool toggleServer = false;

    MgtState mgtState = mgt_run(&client);
    if (mgtState == stConnected) {
      for (int i = 0; i < 4; i++) {
        if (DIODirty[i])
          mgt_send(&client, sDIO + i);
        if (temperatureDirty[i])
          mgt_send(&client, sSensor + i);
        if (scheduleDirty[i])
          mgt_send(&client, sSchedule + i);
      }
      for (int i = 0; i < 8; i++) {
        if (variableDirty[i])
          mgt_send(&client, sVariable + i);
      }
      if (DIODirty[4]) // RX
        mgt_send(&client, sDIO + 4);
      if (A0Dirty)
        mgt_send(&client, sA0);
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
        signal_updateTime(sDIO + i, t);
        mgt_send(&client, sDIO + i);
        signal_updateTime(sDIOMode + i, t);
        mgt_send(&client, sDIOMode + i);
        signal_updateTime(sSchedule + i, t);
        mgt_send(&client, sSchedule + i); // schedule
      }
      for (int i = 0; i < 8; i++) {
        if (variables[i] == variables[i]) { // NAN не будем отправлять (хотя клиенты могут его вычитать), чтобы не инициировать архивирование параметра
          signal_updateTime(sVariable + i, t);
          mgt_send(&client, sVariable + i); // variable
        }
      }

      signal_updateTime(sScriptMode, t);
      mgt_send(&client, sScriptMode); // scriptMode
    }
    else if (mgtState == stDisconnect) {
      struct Signal* s = sUpdate + 1;
      for (int i = 0; i < 20; i++)
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
}

__int32 getBias() {
  return EC_config.app.bias;
}

__uint8 getEventInfo(__uint8 aIndex) {
  if (aIndex < EC_config.app.schedulePtr[3]) {
    __uint8* ptr = EC_config.app.scheduleData + 9 * aIndex;
    return ptr[0];
  }
  else
    return 0x80;
}

__uint32 getStartEvent(__uint8 aIndex) {
  if (aIndex < EC_config.app.schedulePtr[3]) {
    __uint8* ptr = EC_config.app.scheduleData + 1 + 9 * aIndex;
    __uint32 time = (ptr[3] << 24) + (ptr[2] << 16) + (ptr[1] << 8) + ptr[0];
    return time;
  }
  else
    return 0;
}

__uint32 getStopEvent(__uint8 aIndex) {
  if (aIndex < EC_config.app.schedulePtr[3]) {
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

  struct Signal* s = sDIO;
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
    s->m_value.m_reg = 0;
    deviceTimeArray[s - sUpdate - 1] = -1; // сбросим время отрыва устройства
  }

  return s;
}


float bk_getSignal(char* aName, __int16 aLifetime) {
  struct Signal* s = findSignal(aName);
  if (!s)
    return NAN;

  int num = s - sDIO;
  if (num < 4) {
    bool b = digitalRead(pinDIO[num]);
    if (EC_config.app.DIOMode[num] & 0x80)
      b = !b;
    return b;
  }
  else if (num == 4) { // для RX
    bool b = digitalRead(pinDIO[4]);
    return b;   
  }
  else if (s == sA0) {
    float f = analogRead(PIN_A0);
    sleepms(2);
    return f;
  }
  else if ((s >= sVariable) && (s < sDIOMode))
    return variables[s - sVariable];

  if (s->m_value.m_time == -1)
      return NAN;
      
  if (aLifetime != 0) {
    if (aLifetime > 0) {
      if ((s > sUpdate) || ((s >= sSensor) && (s < sSchedule))) {
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

void bk_setSignal(char* aName, float aValue) {
  struct Signal* s = findSignal(aName);
  int num = s - sDIO;
  if (num < 4) {
    if (aValue == aValue)
      digitalWrite(pinDIO[num], (EC_config.app.DIOMode[num] & 0x80) ? (!aValue) : aValue);
  }
  else if ((s >= sVariable) && (s < sDIOMode)) {
    variables[s - sVariable] = aValue;
  }
}

void bk_setSignal(char* aName, const char* aStr) {
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

      signal_updatePtr(sDebug, buf, getUTCTime());
      mgt_send(&client, sDebug);
      signal_updatePtr(sDebug, debugArr, getUTCTime());
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

      signal_updatePtr(sDebug, buf, getUTCTime());
      mgt_send(&client, sDebug);
      signal_updatePtr(sDebug, debugArr, getUTCTime());
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

    signal_updatePtr(sDebug, debugArr, getUTCTime());
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
