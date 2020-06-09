/*
Copyright © 2015, BVAgile. All rights reserved.
Contacts: <bvagile@gmail.com>
*/

#include "Types.h"
#include "config.h"
#include <EEPROM.h>

void debugLog(const __FlashStringHelper* aFormat, ...);
__uint32 crc32(__uint8* aBuf, __uint32 aLen, __uint32 aCrc);

struct ECConfig EC_config;

// Инициализация EEPROM
void EC_begin(void){
   size_t sz1 = sizeof(EC_config);
   EEPROM.begin(sz1);   
   debugLog(F("EEPROM init. Size = %d\n"),(int)sz1);
}

// Устанавливаем сетевые настройки по умолчанию
static void net_default(void) {
  memset( &EC_config.net, 0, sizeof(EC_config.net));
  
  strcpy(EC_config.net.name, "PLC 8285");
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
  for (int i = 0; i < 17; i++)
    EC_config.app.regMode[i] = 0;
  for (int i = 0; i < 9; i++)
    EC_config.app.DIOMode[i] = 0;

  EC_config.app.scriptMode = 0; // ручной режим

  EC_config.app.bias = 0;

  for (int i = 0; i < 4; i++) {
    EC_config.app.schedulePtr[i] = 0;
    EC_config.app.script[i] = 0; // важно обнулить только первые три байта
    EC_config.app.romArr[i][0] = 0;
  }


  for (int i = 0; i < 8; i++)
    EC_config.app.stored[i] = 0;
}

static uint32_t net_crc(void){
  uint8_t* buf = (uint8_t*)&EC_config; 
  int len = offsetof(ECConfig, netCrc);
  return crc32(buf, len, 0x02062020); // случайное число
}

static uint32_t app_crc(void){
  uint8_t* buf = (uint8_t*)&EC_config + offsetof(ECConfig, app);
  int len = offsetof(ECConfig, appCrc) - offsetof(ECConfig, app);
  return crc32(buf, len, 0x02062020); // случайное число
}

// Сохраняем значение конфигурации в EEPROM
void EC_save(void){
  EC_config.netCrc = net_crc();
  EC_config.appCrc = app_crc();

  uint8_t* newData = (uint8_t*)&EC_config;
  for  (int i = 0; i < sizeof(EC_config); i++)
    EEPROM.write(i, newData[i]); // внутри ведётся контроль на реальное изменение данных для оптимизации "commit()"
   
  EEPROM.commit();     
  debugLog(F("Save Config to EEPROM.\n"));   
}

// Читаем конфигурацию из EEPROM в память
void EC_read(void){
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
  for (int i = 0; i < 4; i++) {
    EC_config.app.romArr[i][0] = 0;
//    EC_config.app.script[i] = 0; // важно обнулить только первые три байта
  }
  EC_save();
}
