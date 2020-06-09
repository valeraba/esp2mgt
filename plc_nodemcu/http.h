/*
Copyright © 2015, BVAgile. All rights reserved.
Contacts: <bvagile@gmail.com>
*/


#ifndef _http_H_
#define _http_H_

#include <ESP8266WebServer.h>

extern bool isAP;
extern bool relay_on;

void WiFi_begin(void);
void HTTP_begin(void);
void HTTP_loop();

extern char localIp[16];

#endif
