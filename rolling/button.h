/*
Copyright © 2015, BVAgile. All rights reserved.
Contacts: <bvagile@gmail.com>
*/

#ifndef _button_H_
#define _button_H_

#include "Types.h"

enum But_info {
  BUT_NONE, // кнопка не нажата
  BUT_CLICK, // клик (при чтении сбрасывается в BUT_NONE)
  BUT_DOWN, // кнопка нажата
  BUT_LONG_DOWN // длительное нажатие (при чтении сбрасывается в BUT_DOWN)
};

struct But_ctx {
  int pin;
  uint16_t timeLongDown; 
  uint8_t sampless;
  char idx;
  bool prevState;
  uint8_t flag;
  uint32_t changeTime; // время изменения состояния
  But_info butInfo;
  bool invert;
};

void but_init(But_ctx* aBut, int aPin, uint16_t aTimeLongDown, bool aInvert);
void but_run(But_ctx* aBut, uint32_t aTime); // запускать циклически раз в 10 - 25 мс
But_info but_get(But_ctx* aBut); // чтение состояния кнопки

#endif //_button_H_
