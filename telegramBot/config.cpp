/*
  Copyright © 2015, BVAgile. All rights reserved.
  Contacts: <bvagile@gmail.com>
*/

//#include "Types.h"
#include "config.h"
#include <EEPROM.h>

void debugLog(const __FlashStringHelper* aFormat, ...);
__uint32 crc32(__uint8* aBuf, __uint32 aLen, __uint32 aCrc);


unsigned char script[4006];

void loadScript() {
  script[0] = 0;
  script[1] = 0;
  script[2] = 0;

  // Инициализация файловой системы
  FSInfo fs_info;
  SPIFFS.begin();
  if (!SPIFFS.info(fs_info)) {
    if (!SPIFFS.format()) {
      SPIFFS.end();
      return;
    }
  }
  File f = SPIFFS.open("/f.bin", "r");

  if (!f) {
    SPIFFS.end();
    return;
  }

  int size = f.size();
  if ((size > (sizeof(script) - 4)) || (size < 5)) {
    SPIFFS.end();
    return;
  }
 
  int result = f.read(script + 2, size);
  SPIFFS.end();

  if (result != size) {
      script[0] = 0;
      script[1] = 0;
      script[2] = 0;
      return;
  }

  __uint32 crc = 0;
  memcpy(&crc, script + 2 + size - 4, 4);


  if (crc32(script + 2, size - 4, 0x03022020) == crc) {
    size -= 4;
    memcpy(script, &size, 2);
  }
  else {
    script[0] = 0;
    script[1] = 0;
    script[2] = 0;
  }
  
}

bool writeScript(__uint8* aData, __uint16 aSize) {
  if (aSize > (sizeof(script) - 6))
    return false;
  
  // Инициализация файловой системы
  FSInfo fs_info;
  SPIFFS.begin();
  if (!SPIFFS.info(fs_info)) {
    if (!SPIFFS.format()) {
      SPIFFS.end();
      return false;
    }
  }

  memcpy(script, &aSize, 2);
  memcpy(script + 2, aData, aSize);
  __uint32 crc = crc32(script + 2, aSize, 0x03022020);
  memcpy(script + 2 + aSize, &crc, 4);

  File f = SPIFFS.open("/f.bin", "w+");
  size_t result = f.write(script + 2, aSize + 4);

  SPIFFS.end();

  if (result != (aSize + 6))
    return false;
}



struct ECConfig EC_config;

// Инициализация EEPROM
void EC_begin(void) {
  size_t sz1 = sizeof(EC_config);
  EEPROM.begin(sz1);
  debugLog(F("EEPROM init. Size = %d\n"), (int)sz1);
}

// Устанавливаем сетевые настройки по умолчанию
static void net_default(void) {
  memset( &EC_config.net, 0, sizeof(EC_config.net));

  strcpy(EC_config.net.name, "Telegram Bot");
  strcpy(EC_config.net.password, "");
  strcpy(EC_config.net.ssid, "none");
  strcpy(EC_config.net.pass, "");

  EC_config.net.dhcp = true;
  EC_config.net.ip[0] = 192;
  EC_config.net.ip[1] = 168;
  EC_config.net.ip[2] = 1;
  EC_config.net.ip[3] = 4;
  EC_config.net.msk[0] = 255;
  EC_config.net.msk[1] = 255;
  EC_config.net.msk[2] = 255;
  EC_config.net.msk[3] = 0;
  EC_config.net.gw[0] = 192;
  EC_config.net.gw[1] = 168;
  EC_config.net.gw[2] = 1;
  EC_config.net.gw[3] = 1;

  strcpy(EC_config.net.host1, "mgt24.ru");
  strcpy(EC_config.net.host2, "");
  EC_config.net.deviceId = 0xffffffff;
  strcpy(EC_config.net.key, "");
}

// Устанавливаем настройки приложения по умолчанию
static void app_default(void) {
  strcpy(EC_config.app.token, "");
  EC_config.app.chatId = NAN;

  EC_config.app.scriptMode = 0; // ручной режим

  for (int i = 0; i < 4; i++) {
//    EC_config.app.script[i] = 0; // важно обнулить только первые три байта
    EC_config.app.romArr[i][0] = 0;
  }

  for (int i = 0; i < 5; i++)
    EC_config.app.stored[i] = 0;

  EC_config.app.bias = 0;
  EC_config.app.latitude = 0;
  EC_config.app.longitude = 0;
}

static uint32_t net_crc(void) {
  uint8_t* buf = (uint8_t*)&EC_config;
  int len = offsetof(ECConfig, netCrc);
  return crc32(buf, len, 0x03022020); // случайное число
}

static uint32_t app_crc(void) {
  uint8_t* buf = (uint8_t*)&EC_config + offsetof(ECConfig, app);
  int len = offsetof(ECConfig, appCrc) - offsetof(ECConfig, app);
  return crc32(buf, len, 0x03022020); // случайное число
}

// Сохраняем значение конфигурации в EEPROM
void EC_save(void) {
  EC_config.netCrc = net_crc();
  EC_config.appCrc = app_crc();

  uint8_t* newData = (uint8_t*)&EC_config;
  for  (int i = 0; i < (int)sizeof(EC_config); i++)
    EEPROM.write(i, newData[i]); // внутри ведётся контроль на реальное изменение данных для оптимизации "commit()"

  EEPROM.commit();
  debugLog(F("Save Config to EEPROM.\n"));
}

// Читаем конфигурацию из EEPROM в память
void EC_read(void) {
  uint8_t const* data = EEPROM.getConstDataPtr();
  memcpy(&EC_config, data, sizeof(EC_config));

  bool err = false;

  if (EC_config.netCrc == net_crc())
    debugLog(F("EEPROM Network is correct\n"));
  else {
    debugLog(F("EEPROM Network is not valid\n"));
    net_default();
    err = true;
  }

  if (EC_config.appCrc == app_crc())
    debugLog(F("EEPROM application is correct\n"));
  else {
    debugLog(F("EEPROM application is not valid\n"));
    app_default();
    err = true;
  }

  if (err)
    EC_save();
}

// Удалить все привязки к датчикам
void deleteSensor() {
  for (int i = 0; i < 4; i++)
    EC_config.app.romArr[i][0] = 0;
  EC_save();
}
