/*
Copyright © 2015, BVAgile. All rights reserved.
Contacts: <bvagile@gmail.com>
*/

#ifndef Telegram_h
#define Telegram_h

#include <Arduino.h>
#include <ESP8266WiFi.h>
#include <WiFiClientSecure.h>

typedef double (*UpdateChartId)(double aChatId);

class TelegramBot {
public:
	TelegramBot(const char* aToken, UpdateChartId aUpdateChartId, const char* aHost, uint16_t aPort);
	bool sendMessage(const char* aMsg);
	bool getUpdates();
  const char* m_host;
private:
	const char* m_token;
	//const char* m_host;
	uint16_t m_port;
	UpdateChartId updateChartId;
	//WiFiClientSecure client;
	WiFiClient client;

	size_t readPayload(char* aBuf, size_t aSize);
};

#endif
