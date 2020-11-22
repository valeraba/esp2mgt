/*
Copyright © 2015, BVAgile. All rights reserved.
Contacts: <bvagile@gmail.com>
*/

#include "MgtClient.h"
#include <Arduino.h>
#include <ESP8266WiFi.h>

//static __uint8 txBuf[TX_BUF_SIZE * 2]; // буфер используется, когда внутренний буфер сокета переполнен
static __uint8 txBuf[TX_BUF_SIZE + 2048]; // буфер используется, когда внутренний буфер сокета переполнен
static __uint16 txInd = 0;


void debugLog(const __FlashStringHelper* aFormat, ...);
bool isWiFiConnected();

extern const char* WIFI_SSID;
extern const char* WIFI_PASSWORD;
//extern bool script_lock;


TimeStamp shiftTime;

WiFiClient socket;
bool isConnected = false;

static __uint32 op_start_time = 0; // начало отправки
static __uint32 m_timeLastActivity = 0; // время последней активности на сокете

TimeStamp getUTCTime() {
  static TimeStamp delta = 0;
  static __uint32 prev = 0;
  __uint32 curr = millis();
  if (prev > curr)
    delta += 0xffffffffUL;
  prev = curr;
  return delta + curr + shiftTime;
}

void sleepms(__uint32 aMilliseconds) {
  delay(aMilliseconds);
}

static bool socket_open(const char* aHost, __uint16 aPort) {
  if (WiFi.status() != WL_CONNECTED)
  //if (!isWiFiConnected())
    return false;
  debugLog(F("socket open, host: %s, port: %i\n"), aHost, aPort);

  //script_lock = false;
  if (!socket.connect(aHost, aPort)) {
    //script_lock = true;
    debugLog(F("socket connection failed\n"));
    return false;
  }
  //script_lock = true;
  
  txInd = 0;
  isConnected = true;
  socket.setNoDelay(true);
  m_timeLastActivity = millis();
  return true;
}

static void socket_close() {
  if (isConnected) {
    socket.stop();
    isConnected = false;
    debugLog(F("socket close\n"));
  }
}

static bool socket_send(const void* aBuf, __uint16 aSize) {
  const __uint8* data = (const __uint8*)aBuf;
  //script_lock = false;

  __uint16 len;
  if (aSize) {
    len = sizeof(txBuf) - txInd;
    if (len > aSize)
      len = aSize;
    memcpy(txBuf + txInd, data, len);
    aSize -= len;
    data += len;
    txInd += len;
  }

  while (txInd) {
    if (!socket.connected()) {
      debugLog(F("socket send error\n"));
      socket_close();
      //script_lock = true;
      return false;
    }
    __uint32 availableSize = socket.availableForWrite();
    if (!availableSize) { // если запись не возможна 
      if ((__uint32)(millis() - op_start_time) > 5000) {
        debugLog(F("socket send wait error\n"));
        socket_close();
        //script_lock = true;
        return false;          
      }            
      if (aSize) { // если входной буфер ещё не освободили       
        delay(10);
        continue;
      }
      //script_lock = true;
      return true; // остатки передадим позже
    }
    if (availableSize > txInd)
      availableSize = txInd;
    
    int writtenSize = socket.write(txBuf + 0, availableSize);
    delay(1); // лечит реконекты в роллетах (магия)
    if (writtenSize <= 0) {
      debugLog(F("socket send error\n"));
      socket_close();
      //script_lock = true;
      return false;
    }
    op_start_time = millis();
    m_timeLastActivity = op_start_time;
    
    txInd -= writtenSize;
    memmove(txBuf, txBuf + writtenSize, txInd);

    len = sizeof(txBuf) - txInd;
    if (len > aSize)
      len = aSize;
    memcpy(txBuf + txInd, data, len);
    aSize -= len;
    data += len;
    txInd += len;
  }
  //script_lock = true;
  return true;
}


static int socket_receive(void* aBuf, __uint16 aSize) {
  delay(1); // лечит реконекты в роллетах (магия)
  int readSize = socket.available();
  if (readSize) {
    if (readSize > aSize)
      readSize = aSize;
    socket.read((__uint8*)aBuf, readSize);
    m_timeLastActivity = millis();
    return readSize;
  }
  else {
    if (txInd) { // если в TX буфере остались данные
      if (!socket_send(0, 0))
        return -1;
    }
    else {
      __uint32 t = millis();
      if ((__uint32)(t - m_timeLastActivity) > 40000) { // 40 секунд
        debugLog(F("socket connection timeout\n"));
        socket_close();
        return -1; 
      }
    }
  }

  if (!socket.connected()) {
    debugLog(F("socket connection abort\n"));
    socket_close();
    return -1;
  }
  return 0;
}


static void socket_shutdown() {
}

static bool socket_isTxBusy() {
//  return (txInd >= (sizeof(txBuf) / 2));
  return (txInd >= TX_BUF_SIZE);
}

static bool socket_isConnected() {
  return true;
}

struct PortableSocket mySocket = {
  socket_open,
  socket_receive,
  socket_send,
  socket_shutdown,
  socket_close,
  socket_isTxBusy,
  socket_isConnected
};
