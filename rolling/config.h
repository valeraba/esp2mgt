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
  // длительность открытия шлагбаума в миллисекундах (опорное время)
  uint16_t rollUpCycle;
  // длительность закрытия шлагбаума в миллисекундах (используется только для вычисления коэффициента)
  uint16_t rollDownCycle;
   
  // режим работы: 0 - ручной, 1 - работа по расписанию, 2 - работа по сценарию
  uint8_t mode;


  int32_t bias;
  uint8_t scheduleData[100 * 10]; // расписание
  uint8_t schedulePtr[2];

  int8_t position;
  bool led;

  // скрипт
  uint8_t script[2000];
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

#endif
