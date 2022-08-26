/*
Copyright © 2015, BVAgile. All rights reserved.
Contacts: <bvagile@gmail.com>
*/

#include "Telegram.h"
#include "Types.h"

void debugLog(const __FlashStringHelper* aFormat, ...);

TelegramBot::TelegramBot(const char* aToken, UpdateChartId aUpdateChartId, const char* aHost, uint16_t aPort) {
  m_token = aToken;
  m_host = aHost;
  m_port = aPort;
  updateChartId = aUpdateChartId;
}


double findChatId(const char* aStr) {
  const char* p = 0;
  while (aStr) {
    aStr = strstr(aStr, "\"chat\":{\"id\":");
    if (aStr) {
      aStr += 13;
      p = aStr;
    }
  }
  if (!p) {
    return NAN;
  }
  return atof(p);
}

__int32 lastMessageId = LONG_MIN;

__int32 findMessageId(const char* aStr) {
  const char* p = 0;
  while (aStr) {
    aStr = strstr(aStr, "\"message_id\":");
    if (aStr) {
      aStr += 13;
      p = aStr;
    }
  }
  if (!p) {
    return LONG_MIN;
  }
  return atol(p);
}

size_t TelegramBot::readPayload(char* aBuf, size_t aSize) {
  int len;
  while (client.connected()) {
    len = client.readBytesUntil('\n', aBuf, aSize);

    if (len == 1) {
      aBuf[0] = '\n';
      break;
    }
    if (len == 0) {
      aBuf[0] = 0;
      return 0;
    }
  }

  delay(10);
  len = client.available();
  if (len) {
    if (len > (aSize - 1))
      len = (aSize - 1);
    client.readBytes(aBuf, len);
  }
  aBuf[len] = 0;

  return len;
}



bool TelegramBot::getUpdates() {
  if (!m_token[0])
    return false;

  if (!client.connected()) {
    if (!client.connect(m_host, m_port)) {
      debugLog(F("Telegram connection failed\n"));
      return false;
    }
  }

  client.print("GET /bot");
  client.print(m_token);
  client.println("/getUpdates?offset=-1 HTTP/1.1");
  client.print("Host: ");
  if (m_port == 80)
    client.println(m_host);
  else {
    client.print(m_host);
    client.print(":");
    client.println(m_port);
  }
  client.println();
  client.flush();

  char buf[2048];

  int len = readPayload(buf, sizeof(buf));

  client.stop();

  if (!len)
    return false;

  if (!strstr(buf, "\"text\":\"/start\""))
    return false;
  double id = findChatId(buf);
  if (id != id)
    return false;

  updateChartId(id);
  return true;
}

String urlencode(String str)
{
  String encodedString = "";
  char c;
  char code0;
  char code1;
  //char code2;

  int len = str.length();
  
  for (int i = 0; i < len; i++) {
    c = str.charAt(i);
    if (c == ' ') {
      encodedString += '+';
    } else if (c == '\\') {
      i++;
      if (i < len) {
        c = str.charAt(i);
        if (c == 'n')
          encodedString += "%0A";
        else if (c == 't')
          encodedString += "%09";
        else if (c == '\\')
          encodedString += "%5C";     
      }     
    } else if (isalnum(c)) {
      encodedString += c;
    } else {
      code1 = (c & 0xf) + '0';
      if ((c & 0xf) > 9) {
        code1 = (c & 0xf) - 10 + 'A';
      }
      c = (c >> 4) & 0xf;
      code0 = c + '0';
      if (c > 9) {
        code0 = c - 10 + 'A';
      }
      //code2 = '\0';
      encodedString += '%';
      encodedString += code0;
      encodedString += code1;
      //encodedString+=code2;
    }
    yield();
  }
  return encodedString;
}


bool TelegramBot::sendMessage(const char* aMsg) {
  bool flagDelete = aMsg[0] == 0;
  
  if (flagDelete && (lastMessageId == LONG_MIN))
    return false;
  
  
  if (!m_token[0])
    return false;

  char buf[2048];

  double chatId = updateChartId(NAN);

  if (chatId != chatId)
    return false;

  if (!client.connected()) {
    if (!client.connect(m_host, m_port)) {
      debugLog(F("Telegram connection failed_2\n"));
      return false;
    }
  }

  client.print("GET /bot");
  client.print(m_token);
  if (flagDelete)
    client.print("/deleteMessage?chat_id=");
  else  
    client.print("/sendMessage?chat_id=");
  //client.print(chatId, 0);
  char s[20];
  sprintf(s, "%.0f", chatId);
  client.print(s);
  //Serial.println(s);

  if (flagDelete) {
    client.print("&message_id=");
    sprintf(s, "%li", lastMessageId);
    client.print(s);   
  }
  else {
    client.print("&text=");
    client.print(urlencode(aMsg));
  }
  client.println(" HTTP/1.1");
  client.print("Host: ");
  if (m_port == 80)
    client.println(m_host);
  else {
    client.print(m_host);
    client.print(":");
    client.println(m_port);
  }
  client.println();
  client.flush();

  int len = readPayload(buf, sizeof(buf));

  client.stop();

  if (flagDelete) {
    lastMessageId = LONG_MIN;
    return true;
  }
  
  
  if (len) {
    lastMessageId = findMessageId(buf);
    return true;
  }
  else {
    lastMessageId = LONG_MIN;
    return false;
  }
}
