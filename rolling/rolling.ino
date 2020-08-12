#define COUNT_SIGNALS 37 // 17 + 20
#define COUNT_STORE 3
#include "Types.h"
#include "MgtClient.h"
#include "schedul2.h"
#include "blockly.h"

#include "ESP8266_Board.h"
#include <ESP8266WiFi.h>
#include <ESP8266httpUpdate.h>

#include "config.h"
#include "http.h"
#include "button.h"
#include <Ticker.h>

/*#define PIN_BUTTON    0
#define PIN_RELAY     12
#define PIN_LED_MODE  13
#define PIN_RELAY_2   14
#define PIN_BUTTON_UP    4
#define PIN_BUTTON_DOWN  4*/


#define PIN_BUTTON      10
#define PIN_BUTTON_UP    9
#define PIN_BUTTON_DOWN  0
//#define PIN_RELAY     12
#define PIN_LED_MODE    13
#define PIN_RELAY_2      5

#define PIN_DI  3

struct MapNameItem {
  char* name;
  struct Signal* signal;
};
static struct MapNameItem mapSignalName[COUNT_SIGNALS];
static int lenMapSignalName = 0;


extern struct PortableSocket mySocket;

Ticker ticker;

uint8_t blink_mode = 0B00000101;
But_ctx but;
But_ctx but_up;
But_ctx but_down;

void debugLog(const __FlashStringHelper* aFormat, ...) {
  va_list args;
  va_start(args, aFormat);
  char buf[100];
  vsnprintf_P(buf, sizeof(buf), (const char*)aFormat, args);
  Serial.print(buf);
  va_end(args);
}

static struct Signal* sDI; // DI
static struct Signal* sUp; // up
static struct Signal* sDown; // down
static struct Signal* sSetup; // setup
static struct Signal* sState; // state
static struct Signal* sPosition; // position
static struct Signal* sHalfCycle; // halfCycle
static struct Signal* sSchedule; // schedule
static struct Signal* sScheduleData; // scheduleData
static struct Signal* sAutoMode; // autoMode
static struct Signal* sScriptMode; // scriptMode
static struct Signal* sScript; // script
static struct Signal* sDebug; // debug
static struct Signal* sLed; // led
static struct Signal* sIPAddress; // IPAddress
static struct Signal* sVersion; // version
static struct Signal* sUpdate; // update

static struct MgtClient client;

__uint32 timeRelayOn = 0; // время последнего движения

enum RollState {
  roll_CLOSE = 0, // закрыто  
  roll_DOWN = 1, // опускается
  roll_NONE = 2, // остановлен в промежуточном положениии
  roll_UP = 3, // поднимается  
  roll_OPEN = 4 // открыто  
};

RollState rollState = roll_CLOSE;

volatile __int32 rollPosition = 0;
__int32 rollPositionSetup = 0;


static bool directFlag = false; // false: DOWN, true: UP

// если true, то открытие
void setDirection(bool aValue) {
  directFlag = aValue;
}

// если true, то движение
bool getMove() {
  return digitalRead(PIN_RELAY) || digitalRead(PIN_RELAY_2);  
}

// если false, то останов
void setMove(bool aValue) {
  if (aValue) {
    if (directFlag) {
      digitalWrite(PIN_RELAY_2, false); 
      digitalWrite(PIN_RELAY, true);
    }
    else {
      digitalWrite(PIN_RELAY, false);
      digitalWrite(PIN_RELAY_2, true); 
    }
  }
  else {
    digitalWrite(PIN_RELAY, false);
    digitalWrite(PIN_RELAY_2, false);
  }   
}


bool rollOpen(__uint32 aTime) {
  switch (rollState) {
  case roll_CLOSE:
  case roll_NONE:
    timeRelayOn = aTime;
    setDirection(true);
    setMove(true);
    rollState = roll_UP;
    return true;  
  default:
    return false;  
  }  
}

bool rollClose(__uint32 aTime) {
  switch (rollState) {
  case roll_OPEN:
  case roll_NONE:
    timeRelayOn = aTime;
    setDirection(false);
    setMove(true);
    rollState = roll_DOWN;
    return true;  
  default:
    return false;  
  } 
}

void presetPosition(__int8 aPercent) { 
  float f = EC_config.app.rollHalfCycle;
  f /= 100;
  f *= aPercent;
  rollPosition = f;
  rollPositionSetup = rollPosition;
}

static __int8 autoPosition; // позиция автоматических режимов

bool setPosition(__int8 aPercent) { 
  float f = EC_config.app.rollHalfCycle;
  f /= 100;
  f *= aPercent;
  rollPositionSetup = f;

  __uint32 t = millis();
  if ( (__uint32)(t - timeRelayOn) < 1000) // 1000мс  пауза между открытием и закрытием
    return false;

  __int32 dif = rollPositionSetup - rollPosition;
  if ((dif > 100) || ((dif > 0) && (aPercent == 100))) // разница больше 100мс или полное открытие
    return rollOpen(t);
  else if ((dif < -100) || ((dif < 0) && (aPercent == 0))) // разница больше 100мс или полное закрытие
    return rollClose(t);
  else
    return false;  
     
}

__int8 getPosition() {
  float f = 100;
  f /= EC_config.app.rollHalfCycle;
  f *= rollPosition;

  return roundf(f);
}


// write with confirmation for "up"
static void write_up(bool aValue) {
  if (autoPosition != -128) {
      mgt_writeAns(&client, sUp, erWriteFailed);
      return;
  }
  
  if (aValue) {
    if (!setPosition(100)) {
      mgt_writeAns(&client, sUp, erWriteFailed);
      rollPositionSetup = rollPosition;
      return;
    }
    else {
      signal_updateInt(sSetup, 100, getUTCTime());
      mgt_send(&client, sSetup);
    }
  }
  else {
    if (rollState == roll_UP) {
      rollState = roll_NONE;
      setMove(false);
      timeRelayOn = millis();
      rollPositionSetup = rollPosition;
    }
  }
  
  signal_updateInt(sUp, aValue, getUTCTime());
  mgt_writeAns(&client, sUp, erOk);
}

// write with confirmation for "down"
static void write_down(bool aValue) {
  if (autoPosition != -128) {
      mgt_writeAns(&client, sDown, erWriteFailed);
      return;
  }
  
  if (aValue) {
    if (!setPosition(0)) {
      mgt_writeAns(&client, sDown, erWriteFailed);
      rollPositionSetup = rollPosition;
      return;
    }
    else {
      signal_updateInt(sSetup, 0, getUTCTime());
      mgt_send(&client, sSetup);
    }
  }
  else {
    if (rollState == roll_DOWN) {
      rollState = roll_NONE;
      setMove(false);
      timeRelayOn = millis();
      rollPositionSetup = rollPosition;
    }
  }
 
  signal_updateInt(sDown, aValue, getUTCTime());
  mgt_writeAns(&client, sDown, erOk);
}

// asynchronous writes without confirmation for "setup"
static void writeAsync_sSetup(__int8 aValue) {
  if (autoPosition != -128)
    signal_updateInt(sSetup, autoPosition, getUTCTime());
  else {
    setPosition(aValue);
    signal_updateInt(sSetup, aValue, getUTCTime());
  }
  mgt_send(&client, sSetup);
}

// write with confirmation for "halfCycle"
static void write_halfCycle(float aValue) {
  if ((aValue >= 1) && (aValue <= 60)) {
    EC_config.app.rollHalfCycle = (__uint16)(aValue * 1000);
    if (rollPosition > EC_config.app.rollHalfCycle)
      rollPosition = EC_config.app.rollHalfCycle;
    if (rollPositionSetup > EC_config.app.rollHalfCycle)
      rollPositionSetup = EC_config.app.rollHalfCycle;
    
    EC_save();
    signal_updateDouble(sHalfCycle, aValue, getUTCTime());
    mgt_writeAns(&client, sHalfCycle, erOk);
  }
  else
    mgt_writeAns(&client, sHalfCycle, erWriteFailed);

}

// write with confirmation for "scheduleData"
static void write_scheduleData(int aNumber, __uint8* aValue) {
  __uint16 length = (aValue[1] << 8) | aValue[0];

  int start = aNumber ? EC_config.app.schedulePtr[aNumber - 1] * 10 : 0;
  int startMove = EC_config.app.schedulePtr[aNumber] * 10;
  int shift = (length - 2) - (startMove - start);
  int sizeMove = EC_config.app.schedulePtr[1] * 10 - startMove;

  if (sizeMove < 0)
    sizeMove = -sizeMove;


  if ((EC_config.app.schedulePtr[1] * 10 + shift) > sizeof(EC_config.app.scheduleData)) {
    mgt_writeAns(&client, sScheduleData + aNumber, erWriteFailed);
    return;
  }

  for (int i = 0; i < 2; i++) {
    if (i < aNumber)
      continue;
    EC_config.app.schedulePtr[i] += shift / 10;
  }

  __int16 temp = (aValue[3] << 8) | aValue[2];
  EC_config.app.bias = (__int32)temp * 60;

  memmove(EC_config.app.scheduleData + startMove + shift, EC_config.app.scheduleData + startMove, sizeMove);
  memcpy(EC_config.app.scheduleData + start, aValue + 4, length - 2);

  int end = startMove + shift;
  byte canal = aNumber << 3;
  for (int i = start; i < end; i += 10) {
    EC_config.app.scheduleData[i] &= 0x07;
    EC_config.app.scheduleData[i] |= canal;
  }

  EC_save();
  signal_updateTime(sScheduleData + aNumber, getUTCTime());
  mgt_writeAns(&client, sScheduleData + aNumber, erOk); // confirmation

  sch_init(getUTCTime());
}

static void readScheduleData(int aNumber) {
  int begin = aNumber ? EC_config.app.schedulePtr[aNumber - 1] * 10 : 0;
  int end = EC_config.app.schedulePtr[aNumber] * 10;
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


// write with confirmation for "autoMode"
static void write_autoMode(bool aValue) {
  EC_config.app.mode = aValue ? 1 : 0;
  EC_save();

  TimeStamp t = getUTCTime();
  
  signal_updateInt(sAutoMode, aValue, t);
  mgt_writeAns(&client, sAutoMode, erOk); // confirmation

  if (sScriptMode->m_value.u.m_bool) {
    signal_updateInt(sScriptMode, false, t);
    mgt_send(&client, sScriptMode);
  }
}

// write with confirmation for "scriptMode"
static void write_scriptMode(bool aValue) {
  EC_config.app.mode = aValue ? 2 : 0;
  EC_save();

  TimeStamp t = getUTCTime();
  
  signal_updateInt(sScriptMode, aValue, t);
  mgt_writeAns(&client, sScriptMode, erOk); // confirmation

  if (sAutoMode->m_value.u.m_bool) {
    signal_updateInt(sAutoMode, false, t);
    mgt_send(&client, sAutoMode);
  }
}

// write with confirmation for "led"
static void write_led(bool aValue) {
  EC_config.app.led = aValue;
  EC_save();
  
  signal_updateInt(sLed, aValue, getUTCTime());
  mgt_writeAns(&client, sLed, erOk); // confirmation
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
    if (aSignal == sScheduleData)
      readScheduleData(0);
    else {
      signal_updateTime(aSignal, getUTCTime());
      mgt_readAns(&client, aSignal, erOk);
    }
    break;
  case opAttach:
    break;
  case opWrite:
    if (aSignal == sUp)
      write_up(aWriteValue->u.m_bool);
    else if (aSignal == sDown)
      write_down(aWriteValue->u.m_bool);
    else if (aSignal == sHalfCycle)
      write_halfCycle(aWriteValue->u.m_float);
    else if (aSignal == sScheduleData)
      write_scheduleData(0, aWriteValue->u.m_blob);
    else if (aSignal == sAutoMode)
      write_autoMode(aWriteValue->u.m_bool);
    else if (aSignal == sScriptMode)
      write_scriptMode(aWriteValue->u.m_bool);
    else if (aSignal == sScript)
      write_script(aWriteValue->u.m_blob);
    else if (aSignal == sDebug)
      write_debug(aWriteValue->u.m_blob);
    else if (aSignal == sLed)
      write_led(aWriteValue->u.m_bool);
    else if (aSignal == sUpdate)
      write_update(aWriteValue->u.m_bool);
    break;
  case opWriteAsync:
    if (aSignal == sSetup)
      writeAsync_sSetup(aWriteValue->u.m_int8);
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
  but_run(&but_up, t);
  but_run(&but_down, t);
  
  But_info info_up = but_get(&but_up);
  But_info info_down = but_get(&but_down);

  if (getMove()) {
    __uint32 dif = t - timeRelayOn;
    timeRelayOn = t;
    if (rollState == roll_UP) {
      rollPosition += dif;
      if (rollPosition >= rollPositionSetup) {
        setMove(false);
        if (rollPosition >= EC_config.app.rollHalfCycle) {
          rollPosition = EC_config.app.rollHalfCycle;
          rollState = roll_OPEN;
        }
        else
          rollState = roll_NONE;
      }
    }
    else {
      rollPosition -= dif;
      if (rollPosition <= rollPositionSetup) {
        setMove(false);
        if (rollPosition <= 0) {
          rollPosition = 0;
          rollState = roll_CLOSE;
        }
        else
          rollState = roll_NONE;
      }
    }

    if ((info_up == BUT_CLICK) || (info_down == BUT_CLICK)) { // прервать движение
      if (getMove()) {
        setMove(false);
        rollPositionSetup = rollPosition;
        rollState = roll_NONE;
      }       
    }  
    
  }
  else {
    if ( (__uint32)(t - timeRelayOn) < 1000) // 1000мс  пауза между открытием и закрытием
      return;
    
    if (info_up == BUT_LONG_DOWN) { // движение
      rollPositionSetup = EC_config.app.rollHalfCycle;
      rollOpen(t);
    }
    else if (info_down == BUT_LONG_DOWN) {
      rollPositionSetup = 0;
      rollClose(t);
    }
    else {
      __int32 dif = rollPositionSetup - rollPosition;
      if (dif > 100) // разница больше 100мс
        rollOpen(t);
      else if (dif < -100) // разница больше 100мс
        rollClose(t);
    }
  }

}

void setup() {
  // Последовательный порт для отладки
  Serial.begin(115200);
  debugLog(F("\n\nFree memory %d\n"), ESP.getFreeHeap());

  pinMode(PIN_DI, INPUT_PULLUP);

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

  struct DeviceConfig deviceConfig;
  deviceConfig.m_deviceId = EC_config.net.deviceId;
  deviceConfig.m_login = 0;
  deviceConfig.m_password = EC_config.net.key;
  deviceConfig.m_debugLog = debugLog;
  deviceConfig.m_handler = handler;
  deviceConfig.m_storeFields = client.m_storeFields;
  deviceConfig.m_regSize = COUNT_STORE;

  if (!mgt_init(&client, &deviceConfig, &mySocket))
    while(1);

  sDI = mgt_createSignal(&client, "DI", tpBool, SEC_LEV_READ | SIG_ACCESS_READ, STORE_MODE_CHANGE | STORE_UNIT_MIN | 1, 0);
  sUp = mgt_createSignal(&client, "up", tpBool, SEC_LEV_READ | SIG_ACCESS_READ | SIG_ACCESS_WRITE, STORE_MODE_CHANGE | STORE_UNIT_MIN | 1, 0);
  sDown = mgt_createSignal(&client, "down", tpBool, SEC_LEV_READ | SIG_ACCESS_READ | SIG_ACCESS_WRITE, STORE_MODE_CHANGE | STORE_UNIT_MIN | 1, 0);
  sSetup = mgt_createSignal(&client, "setup", tpInt8, SEC_LEV_READ | SIG_ACCESS_READ | SIG_ACCESS_ASYNC_WRITE, STORE_MODE_OFF, 0);
  sState = mgt_createSignal(&client, "state", tpUInt8, SEC_LEV_READ | SIG_ACCESS_READ, STORE_MODE_OFF, 0);
  sPosition = mgt_createSignal(&client, "position", tpInt8, SEC_LEV_READ | SIG_ACCESS_READ, STORE_MODE_OFF, 0);
  sHalfCycle = mgt_createSignal(&client, "halfCycle", tpFloat, SEC_LEV_READ | SIG_ACCESS_READ | SIG_ACCESS_WRITE, STORE_MODE_OFF, 0);
  sSchedule = mgt_createSignal(&client, "schedule", tpFloat, SEC_LEV_READ | SIG_ACCESS_READ, STORE_MODE_OFF, 0);
  sScheduleData = mgt_createSignal(&client, "scheduleData", tpBlob, SEC_LEV_READ | SIG_ACCESS_READ | SIG_ACCESS_WRITE, STORE_MODE_OFF, 0);
  sAutoMode = mgt_createSignal(&client, "autoMode", tpBool, SEC_LEV_READ | SIG_ACCESS_READ | SIG_ACCESS_WRITE, STORE_MODE_OFF, 0);
  sScriptMode = mgt_createSignal(&client, "scriptMode", tpBool, SEC_LEV_READ | SIG_ACCESS_READ | SIG_ACCESS_WRITE, STORE_MODE_OFF, 0);
  sScript = mgt_createSignal(&client, "script", tpBlob, SEC_LEV_READ | SIG_ACCESS_READ | SIG_ACCESS_WRITE, STORE_MODE_OFF, 0);
  sDebug = mgt_createSignal(&client, "debug", tpBlob, SEC_LEV_NO_ACCESS | SIG_ACCESS_READ | SIG_ACCESS_WRITE, STORE_MODE_OFF, 0);
  sLed = mgt_createSignal(&client, "led", tpBool, SEC_LEV_READ | SIG_ACCESS_READ | SIG_ACCESS_WRITE, STORE_MODE_OFF, 0);
  sIPAddress = mgt_createSignal(&client, "IPAddress", tpString, SEC_LEV_READ | SIG_ACCESS_READ, STORE_MODE_OFF, 0);
  sVersion = mgt_createSignal(&client, "version", tpString, SEC_LEV_READ | SIG_ACCESS_READ, STORE_MODE_OFF, 0);
  sUpdate = mgt_createSignal(&client, "update", tpBool, SEC_LEV_READ | SIG_ACCESS_READ | SIG_ACCESS_WRITE, STORE_MODE_OFF, 0);

  digitalWrite(PIN_RELAY, false); 
  digitalWrite(PIN_RELAY_2, false); 
  pinMode(PIN_RELAY, OUTPUT);
  pinMode(PIN_RELAY_2, OUTPUT);

  but_init(&but, PIN_BUTTON, 2000, true);
  but_init(&but_up, PIN_BUTTON_UP, 1200, false);
  but_init(&but_down, PIN_BUTTON_DOWN, 1200, false);

  signal_updateDouble(sHalfCycle, (float)EC_config.app.rollHalfCycle/1000, 0);
  signal_updateInt(sAutoMode, (EC_config.app.mode == 1), 0);
  signal_updateInt(sScriptMode, (EC_config.app.mode == 2), 0);
  signal_updateInt(sLed, EC_config.app.led, 0);
  signal_updateInt(sPosition, EC_config.app.position, 0);
  signal_updateInt(sSetup, EC_config.app.position, 0);
  presetPosition(EC_config.app.position);

  if (EC_config.app.position <= 0)
    rollState = roll_CLOSE;
  else if(EC_config.app.position >= 100)
    rollState = roll_OPEN;
  else  
    rollState = roll_NONE;
  
  signal_updatePtr(sIPAddress, localIp, 0);
  
  const char* ver = "Rolling Sonoff v1.9 29/VI/2020";
  signal_updatePtr(sVersion, ver, 0);

  signal_updatePtr(sScript, EC_config.app.script, 0);
  signal_updatePtr(sDebug, debugArr, 0);

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
struct Period _200_ms = { 200, 0 };
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

  bool DIDirty = false;
  bool upDirty = false;
  bool downDirty = false;
  bool setupDirty = false;
  bool stateDirty = false;
  bool positionDirty = false;
  bool scheduleDirty = false;

  bool flagEvent = periodEvent(&_1_min, t);

  bool DI = digitalRead(PIN_DI); // читаем цифровой вход
  if (flagEvent || (sDI->m_value.u.m_bool ^ DI)) {
      signal_updateInt(sDI, DI, t);
      DIDirty = true;
  }

  autoPosition = -128; 

  if (synchronization) {
    sch_run(t);
    if (sSchedule->m_value.u.m_float != canals[0]) {
      if ((sSchedule->m_value.u.m_float == sSchedule->m_value.u.m_float) || (canals[0] != -128)) {
        signal_updateDouble(sSchedule, (canals[0] == -128) ? NAN : canals[0], t);
        scheduleDirty = true;
      }
    }
    if (EC_config.app.mode == 1) // если работа по расписанию
      autoPosition = canals[0];
  }

  if (EC_config.app.mode == 2 || bk_debug) { // если работа по сценариию или отладка
    if (!bk_run()) // внутри может выствляться autoPosition
      EC_config.app.mode = 0;
  }

  if (autoPosition != -128) {
    setPosition(autoPosition);
    if (sSetup->m_value.u.m_int8 != autoPosition) {
      sSetup->m_value.u.m_int8 = autoPosition;
      setupDirty = true;
    }
  }

  bool isMove = (rollState == roll_UP);
  if (flagEvent || (sUp->m_value.u.m_bool ^ isMove)) {
    signal_updateInt(sUp, isMove, t);
    upDirty = true;
  }
  
  isMove = (rollState == roll_DOWN);
  if (flagEvent || (sDown->m_value.u.m_bool ^ isMove)) {
    signal_updateInt(sDown, isMove, t);
    downDirty = true;
  }

  if (sState->m_value.u.m_uint8 != rollState) {
    signal_updateInt(sState, rollState, t);
    stateDirty = true;
  }

  if (periodEvent(&_200_ms, t)) {
    __int8 pos = getPosition();
    if (sPosition->m_value.u.m_int8 != pos) { 
      signal_updateInt(sPosition, pos, t);
      positionDirty = true;
    }

    if (EC_config.app.position != pos) {
      if ( (__uint32)(ms - timeRelayOn) > 60000) { // если прошло больше 1 минуты после остановки  
        EC_config.app.position = pos;
        EC_save();
      }
    }

    if (!getMove()) {
      if (sSetup->m_value.u.m_int8 != pos) {
        if ( (__uint32)(ms - timeRelayOn) > 1000) { // 1000мс  пауза между открытием и закрытием
          signal_updateInt(sSetup, pos, t);
          setupDirty = true;
        }
      }    
    }
    
  }

  static bool toggleServer = false;

  MgtState mgtState = mgt_run(&client);
  if (mgtState == stConnected) {
    if (DIDirty)
      mgt_send(&client, sDI);
    if (upDirty)
      mgt_send(&client, sUp);
    if (downDirty)
      mgt_send(&client, sDown);
    if (setupDirty)
      mgt_send(&client, sSetup);
    if (stateDirty)
      mgt_send(&client, sState);
    if (positionDirty)
      mgt_send(&client, sPosition);
    if (scheduleDirty)
      mgt_send(&client, sSchedule);
  }
  else if (mgtState == stEstablished) {
      TimeStamp t = getUTCTime();
      sch_init(t);
      synchronization = true;

      // всё то, что может измениться
      signal_updateTime(sDI, t);
      mgt_send(&client, sDI);
      signal_updateTime(sUp, t);
      mgt_send(&client, sUp);
      signal_updateTime(sDown, t);
      mgt_send(&client, sDown);
      signal_updateTime(sSetup, t);
      mgt_send(&client, sSetup);
      signal_updateTime(sState, t);
      mgt_send(&client, sState);
      signal_updateTime(sPosition, t);
      mgt_send(&client, sPosition);
      signal_updateTime(sSchedule, t);
      mgt_send(&client, sSchedule);
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

__int32 getBias() {
  return EC_config.app.bias;
}

__uint8 getEventInfo(__uint8 aIndex) {
  if (aIndex < EC_config.app.schedulePtr[1]) {
    __uint8* ptr = EC_config.app.scheduleData + 10 * aIndex;
    return ptr[0];
  }
  else
    return 0x80;
}

__uint32 getStartEvent(__uint8 aIndex) {
  if (aIndex < EC_config.app.schedulePtr[1]) {
    __uint8* ptr = EC_config.app.scheduleData + 1 + 10 * aIndex;
    __uint32 time = (ptr[3] << 24) + (ptr[2] << 16) + (ptr[1] << 8) + ptr[0];
    return time;
  }
  else
    return 0;
}

__uint32 getStopEvent(__uint8 aIndex) {
  if (aIndex < EC_config.app.schedulePtr[1]) {
    __uint8* ptr = EC_config.app.scheduleData + 1 + 4 + 10 * aIndex;
    __uint32 time = (ptr[3] << 24) + (ptr[2] << 16) + (ptr[1] << 8) + ptr[0];
    return time;
  }
  else
    return 0;
}

__int8 getValueEvent(__uint8 aIndex) {
  if (aIndex < EC_config.app.schedulePtr[1]) {
    __int8* ptr = (__int8*)EC_config.app.scheduleData + 1 + 4 + 4 + 10 * aIndex;
    return ptr[0];
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

  struct Signal* s = sDI;
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
  if (!s) {
    mgt_attachSignal(&client, aName);
    return NAN;
  }

  if ((s == sSetup) && (autoPosition != -128))
      return autoPosition;

  if (s->m_value.m_time == -1)
      return NAN;

  if (aLifetime) {
    if (s > sUpdate) {
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
  if (s == sSetup) {
    if (aValue == aValue) {
      if (aValue < 0)
        aValue = 0;
      if (aValue > 100)
        aValue = 100;
      autoPosition = aValue;
    }
    else
      autoPosition = -128;
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
    default:
        f = NAN;
        break;
    }
    return f;
}

void bk_prints(const char* aStr) {
  if (bk_debug) {
    if (mgt_getState(&client) == stConnected) {
      char buf[256];
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
