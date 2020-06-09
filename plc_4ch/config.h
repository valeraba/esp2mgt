/*
Copyright © 2015, BVAgile. All rights reserved.
Contacts: <bvagile@gmail.com>
*/

#ifndef _config_H_
#define _config_H_
#include <ESP8266WiFi.h>

extern struct ECConfig EC_config;

struct NetConfig {
  // Параметры в режиме точки доступа
  char name[32]; 
  char password[32];
  // Параметры подключения в режиме клиента
  char ssid[32];
  char pass[32];
  bool dhcp;
  IPAddress ip;
  IPAddress msk;
  IPAddress gw;

  // Адреса MGT серверов
  char host1[48];   
  char host2[48];   
  // Идентификатор устройства
  uint32_t deviceId;
  // Ключ авторизации
  char key[32];  
};

struct AppConfig {
  bool scriptMode; // режим работы: 0 - ручной, 1 - работа по сценарию
  byte reverse[4]; // реверс реле  
  float stored[8]; // параметры общего назначения  

  byte romArr[4][8];

  int32_t bias;
  uint8_t scheduleData[100 * 9]; // расписание
  uint8_t schedulePtr[4];

  uint8_t script[2000]; // скрипт
};

struct ECConfig {
  NetConfig net;
  uint32_t netCrc;
  AppConfig app;
  uint32_t appCrc;
};


void EC_begin(void);
void EC_read(void);
void EC_save(void);

void deleteSensor();

#endif
