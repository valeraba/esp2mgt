/*
Copyright © 2015, BVAgile. All rights reserved.
Contacts: <bvagile@gmail.com>
*/

#include "arduino.h"
#include "button.h"

void but_init(But_ctx* aBut, int aPin, uint16_t aTimeLongDown) {
  pinMode(aPin, INPUT_PULLUP);
  aBut->pin = aPin;
  aBut->timeLongDown = aTimeLongDown;
  aBut->sampless = 0;
  aBut->idx = 0;
  aBut->prevState = false;
  aBut->flag = 0;
  aBut->changeTime = 0; // время изменения состояния
  aBut->butInfo = BUT_NONE;
}

void but_run(But_ctx* aBut, uint32_t aTime) {
  bool state = !digitalRead(aBut->pin);
  if (state)
    aBut->sampless |= 1 << aBut->idx;
  else
    aBut->sampless &= ~(1 << aBut->idx);

  aBut->idx = (aBut->idx + 1) & 0x03;

  if (aBut->prevState != state) {
    aBut->prevState = state;
    aBut->changeTime = aTime;
  }
  else if (aBut->sampless == 0x0f) { // если кнопка нажата
    if (aBut->butInfo == BUT_NONE) {
      aBut->butInfo = BUT_DOWN;
      aBut->flag = 0;
    }
    if (aBut->flag == 0) {
      if ((uint32_t)(aTime - aBut->changeTime) > aBut->timeLongDown) // если нажата более определённого времени
        aBut->flag = 3;
    }      
  }
  else if (aBut->sampless == 0) { // если кнопка отпущена
    if (aBut->butInfo == BUT_DOWN) {
      aBut->butInfo = BUT_NONE;
      if (aBut->flag == 0) // если не было длинного нажатия
        aBut->flag = 2;
      else
        aBut->flag = 1;
    }  
    if (aBut->flag == 2) {
      if ((uint32_t)(aTime - aBut->changeTime) > 1000) // если отпущена более 1 сек назад
        aBut->flag = 1;
    }
  }
}

But_info but_get(But_ctx* aBut) {
  if (aBut->flag == 2) {
    aBut->flag = 1;
    return BUT_CLICK;  
  }
  if (aBut->flag == 3) {
    aBut->flag = 1;
    return BUT_LONG_DOWN;
  } 
  return aBut->butInfo; 
}
