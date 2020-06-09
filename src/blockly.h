/*
Copyright © 2015, BVAgile. All rights reserved.
Contacts: <bvagile@gmail.com>
*/

#ifndef _blockly_H_
#define _blockly_H_

#include "Types.h"

void bk_init(__uint8* aCode);
bool bk_run();
float bk_getSignal(char* aName, __uint16 aLifetime);
void bk_setSignal(char* aName, float aValue);
void bk_print(float aValue);
void bk_prints(const char* aStr);
#define bk_millis millis
#define bk_delayMicroseconds delayMicroseconds

extern bool bk_debug;

// установить точку останова
// если aIP == 0xffff, то сделать один шаг (ассемблерный)
void bk_break(__uint16 aIP);

// обратная функция останова
void bk_onBreak(__uint16 aIP);

#endif //_blockly_H_
