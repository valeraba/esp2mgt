/**
* Прошивка SONOFF TH10/16
* Copyright (C) 2016 Алексей Шихарбеев
* http://samopal.pro
*/


#ifndef WS_HTTP_h
#define WS_HTTP_h

#include <ESP8266WebServer.h>

extern bool isAP;
extern bool relay_on;

#define PIN_RELAY    12

void WiFi_begin(void);
void HTTP_begin(void);
void HTTP_loop();

extern char localIp[16];

#endif
