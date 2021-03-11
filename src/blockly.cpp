/*
Copyright © 2015, BVAgile. All rights reserved.
Contacts: <bvagile@gmail.com>
*/

#include "blockly.h"

#include <string.h>
#include <math.h>

#define MAX_STACK 1000
#define MAX_DELAY_MS 1000ul

static __uint8* code;
static __uint8 stack[MAX_STACK];
static __uint16 IP; // указатель на код
static __uint16 SP; // указатель на стек
static __uint16 SP_Base;
static __uint16 arg_Base;

static __uint32 pause;
static __uint32 startTime;

static __uint8 error;
static bool loopEnter;
static bool done;

bool bk_debug = false;
static bool isBreak;
static __uint16 breakpoint;

static inline __uint16 getUint16(__uint8* s) {
  __uint16 r = s[0];
  *((__uint8*)(&r) + 1) = s[1];
  return r;
}


static inline void setUint16(__uint8* d, __uint16 s) {
  d[0] = *((__uint8*)(&s) + 0);
  d[1] = *((__uint8*)(&s) + 1);
}

static inline void copy32(void* d, void* s) {
  ((__uint8*)d)[0] = ((__uint8*)s)[0];
  ((__uint8*)d)[1] = ((__uint8*)s)[1];
  ((__uint8*)d)[2] = ((__uint8*)s)[2];
  ((__uint8*)d)[3] = ((__uint8*)s)[3];
}

static inline float getFloat32(__uint8* s) {
  float r;
  copy32(&r, s);
  return r;
}

static void Shift() {
  __int8 v = code[IP];
  SP += v * 4;
  IP++;
}

static void Ldi() {
  if (SP < 4) {
    error = 1;
    return;
  }
  SP -= 4;
  copy32(stack + SP, code + IP);
  IP += 4;
}

static void Ld_str() {
  if (SP < 4) {
    error = 1;
    return;
  }
  SP -= 4;

  __uint16 adr = getUint16(code + IP);
  setUint16(stack + SP, adr);
  setUint16(stack + SP + 2, 0xffaa);
  IP += 2;
}

static void Ld() {
  if (SP < 4) {
    error = 1;
    return;
  }
  SP -= 4;
  __uint16 adr = MAX_STACK - getUint16(code + IP);
  copy32(stack + SP, stack + adr);
  IP += 2;
}

static void St() {
  __uint16 adr = MAX_STACK - getUint16(code + IP);
  copy32(stack + adr, stack + SP);
  SP += 4;
  IP += 2;
}

static void Ld_arg() {
  if (SP < 4) {
    error = 1;
    return;
  }
  SP -= 4;
  __uint16 adr = arg_Base - getUint16(code + IP);
  copy32(stack + SP, stack + adr);
  IP += 2;
}

static void St_arg() {
  __uint16 adr = arg_Base - getUint16(code + IP);
  copy32(stack + adr, stack + SP);
  SP += 4;
  IP += 2;
}

static void Loop() {
  if (SP < 4) {
    error = 1;
    return;
  }
  SP -= 4;
  copy32(stack + SP, code + IP);
  IP += 4;
  loopEnter = true;
}

static void Repeat() {
  float v = getFloat32(stack + SP + 4);
  if (v < 1) {
    IP = getUint16(stack + SP + 2);
    SP += 4;
  }
  else {
    v--;
    copy32(stack + SP + 4, &v);
  }
}



static void _for(__uint16 aBase) {
  __uint16 adr = aBase - getUint16(code + IP);
  float v;
  float to = getFloat32(stack + SP + 8);
  float by = getFloat32(stack + SP + 4);

  if (loopEnter) {
    loopEnter = false;
    v = getFloat32(stack + SP + 12);
    if (by < 0)
      by = -by;
    if (v > to)
      by = -by;
    copy32(stack + SP + 4, &by);


    if (by == 0) {
      to = v;
      copy32(stack + SP + 8, &to);
    }
  }
  else {
    v = getFloat32(stack + adr);
    v += by;
  }

  copy32(stack + adr, &v);

  bool exit;

  if (by < 0)
    exit = (v < to);
  else
    exit = (v > to);

  if (exit) {
    IP = getUint16(stack + SP + 2);
    SP += 4;
  }
  else
    IP += 2;
}

static void For() {
  _for(MAX_STACK);
}

static void For_arg() {
  _for(arg_Base);
}

static void Continue() {
  IP = getUint16(stack + SP);
}

static void Break() {
  IP = getUint16(stack + SP + 2);
  SP += 4;
}

static void Je() {
  float v = getFloat32(stack + SP);
  SP += 4;
  if (!v)
    IP = getUint16(code + IP);
  else
    IP += 2;
}

static void Jne() {
  float v = getFloat32(stack + SP);
  SP += 4;
  if (v)
    IP = getUint16(code + IP);
  else
    IP += 2;
}

static void Jmp() {
  IP = getUint16(code + IP);
}

static void Call() {
  if (SP < 5) {
    error = 1;
    return;
  }
  SP -= 5;

  setUint16(stack + SP + 3, IP + 3); // IP возрата
  setUint16(stack + SP + 1, SP_Base); // SP_Base
  __uint8 n = code[IP + 2];
  SP_Base = SP;
  arg_Base = SP_Base + 5 + n * 4;
  stack[SP] = n; // количество аргументов
  IP = getUint16(code + IP);
}

static void Ret() {
  bool isReturn = false;
  float ret;
  if (SP_Base != SP) {
    ret = getFloat32(stack + SP);
    SP += 4;
    isReturn = true;
  }
  __uint8 n = stack[SP];

  SP_Base = getUint16(stack + SP + 1);
  IP = getUint16(stack + SP + 3);

  SP += n * 4 + 5;
  if (isReturn) {
    SP -= 4;
    copy32(stack + SP, &ret);
  }

  n = stack[SP_Base];
  arg_Base = SP_Base + 5 + n * 4;
}

static void Add() {
  float v = getFloat32(stack + SP + 4);
  float v2 = getFloat32(stack + SP);
  v += v2;
  copy32(stack + SP + 4, &v);
  SP += 4;
}

static void Sub() {
  float v = getFloat32(stack + SP + 4);
  float v2 = getFloat32(stack + SP);
  v -= v2;
  copy32(stack + SP + 4, &v);
  SP += 4;
}

static void Mul() {
  float v = getFloat32(stack + SP + 4);
  float v2 = getFloat32(stack + SP);
  v *= v2;
  copy32(stack + SP + 4, &v);
  SP += 4;
}

static void Div() {
  float v = getFloat32(stack + SP + 4);
  float v2 = getFloat32(stack + SP);
  v /= v2;
  copy32(stack + SP + 4, &v);
  SP += 4;
}

static void Pow() {
  float v = getFloat32(stack + SP + 4);
  float v2 = getFloat32(stack + SP);
  v = (float)pow(v, v2);
  copy32(stack + SP + 4, &v);
  SP += 4;
}

static void Eq() {
  float v = getFloat32(stack + SP + 4);
  float v2 = getFloat32(stack + SP);
  v = (v == v2) ? (float)1 : 0;
  copy32(stack + SP + 4, &v);
  SP += 4;
}

static void Neq() {
  float v = getFloat32(stack + SP + 4);
  float v2 = getFloat32(stack + SP);
  v = (v != v2) ? (float)1 : 0;
  copy32(stack + SP + 4, &v);
  SP += 4;
}

static void Lt() {
  float v = getFloat32(stack + SP + 4);
  float v2 = getFloat32(stack + SP);
  v = (v < v2) ? (float)1 : 0;
  copy32(stack + SP + 4, &v);
  SP += 4;
}

static void Lte() {
  float v = getFloat32(stack + SP + 4);
  float v2 = getFloat32(stack + SP);
  v = (v <= v2) ? (float)1 : 0;
  copy32(stack + SP + 4, &v);
  SP += 4;
}

static void Gt() {
  float v = getFloat32(stack + SP + 4);
  float v2 = getFloat32(stack + SP);
  v = (v > v2) ? (float)1 : 0;
  copy32(stack + SP + 4, &v);
  SP += 4;
}

static void Gte() {
  float v = getFloat32(stack + SP + 4);
  float v2 = getFloat32(stack + SP);
  v = (v >= v2) ? (float)1 : 0;
  copy32(stack + SP + 4, &v);
  SP += 4;
}

static void And() {
  float v = getFloat32(stack + SP + 4);
  float v2 = getFloat32(stack + SP);
  v = (v && v2) ? (float)1 : 0;
  copy32(stack + SP + 4, &v);
  SP += 4;
}

static void Or() {
  float v = getFloat32(stack + SP + 4);
  float v2 = getFloat32(stack + SP);
  v = (v || v2) ? (float)1 : 0;
  copy32(stack + SP + 4, &v);
  SP += 4;
}

static void Not() {
  float v = getFloat32(stack + SP);
  v = !v;
  copy32(stack + SP, &v);
}

static void Print() {
  __uint8* p = stack + SP;
  if ((p[2] == 0xaa) && (p[3] == 0xff)) {
    __uint16 adr = getUint16(p);
    const char* str = (char*)code + adr;
    bk_prints(str);
  }
  else {
    float v = getFloat32(p);
    bk_print(v);
  }
  SP += 4;
}

static void S_get() {
  if (SP < 4) {
    error = 1;
    return;
  }
  SP -= 4;

  __uint16 adr = getUint16(code + IP);
  char* name = (char*)code + adr;
  __int16 lifetime = (__int16)getUint16(code + IP + 2);

  IP += 4;

  float f = bk_getSignal(name, lifetime);
  copy32(stack + SP, &f);
}

static void S_set() {
  __uint16 adr = getUint16(code + IP);
  char* name = (char*)code + adr;

  __uint8* p = stack + SP;
  SP += 4;
  if ((p[2] == 0xaa) && (p[3] == 0xff)) {
    __uint16 adr = getUint16(p);
    char* str = (char*)code + adr;
	bk_setSignal(name, str);
  }
  else {
    float v = getFloat32(p);
    bk_setSignal(name, v);
  }

  IP += 2;
}

#ifdef ESP8266
// Ldi 0.001 + Delay = 7.73 mks
// Ldi 0 + Delay = 6.36 mks
static void Delay() {
  float v = getFloat32(stack + SP);
  SP += 4;
  if (v > MAX_DELAY_MS) {
    startTime = bk_millis();
    pause = v;
  }
  else
    bk_delayMicroseconds(v * 1000);
}
#else
static void Delay() {
  __uint32 t = bk_millis();
  __uint32 v = (__uint32)getFloat32(stack + SP);
  SP += 4;
  if (v > MAX_DELAY_MS) {
    startTime = t;
    pause = v;
  }
  else
    while ((__uint32)(bk_millis() - t) < v);
}
#endif

static void Pause() {
  startTime = bk_millis();
  pause = (__uint32)getFloat32(stack + SP);
  SP += 4;
}

static void Time() {
    if (SP < 4) {
        error = 1;
        return;
    }
    SP -= 4;

    __uint8 op = *(code + IP++);

    float f = bk_getTime(op);
    copy32(stack + SP, &f);
}


typedef void(*FuncCmd)();
static FuncCmd cmdTable[] = { 0, Shift, // выход и сдвиг SP
Ldi, Ld_str, Ld, St, Ld_arg, St_arg, // загрузка и выгрузка
Add, Sub, Mul, Div, Pow, // арифметика
And, Or, Not, // логика
Eq, Neq, Lt, Lte, Gt, Gte, // сравнение
Je, Jne, Jmp, Call, Ret, // переходы и функции
Loop, Repeat, For, For_arg, Continue, Break, // циклы
Print, S_get, S_set, // дополнительные
Delay, Pause, Time // время
};

void bk_init(__uint8* aCode) {
  code = aCode;
  done = true;
}

bool bk_run() {
  if (bk_debug && isBreak) {
    if (pause) {
      if ((__uint32)(bk_millis() - startTime) >= pause) {
        pause = 0;
        bk_onBreak(IP);
      }
    }
    return true;
  }

  if (done) {
    IP = 0;
    SP = MAX_STACK;
    SP_Base = SP;
    loopEnter = false;
    done = false;
    pause = 0;
    error = false;
  }
  else {
    if ((__uint32)(bk_millis() - startTime) < pause)
      return true;
    pause = 0;
  }

#ifdef ESP8266
  __uint32 t = micros();
#else
  __uint32 t = bk_millis();
#endif

  while (1) {
    __uint8 cmd = code[IP++];
    if (cmd == 0) {
      done = true;
      if (bk_debug) {
        if ((breakpoint == 0xffff) || (breakpoint == 0)) {
          isBreak = true;
          bk_onBreak(0);
        }
      }
      break;
    }
    if (cmd > 38) {
      error = true;
      isBreak = true;
      bk_prints("Code error!");
      break;
    }
    cmdTable[cmd]();
    if (error) {
      isBreak = true;
      bk_prints("Stack overflow!");
      break;
    }
    if (bk_debug) {
      if ((breakpoint == 0xffff) || (IP == breakpoint)) {
        isBreak = true;
        if (!pause)
          bk_onBreak(IP);
        break;
      }
    }
    if (pause)
      break;

#ifdef ESP8266
    if ((__uint32)(micros() - t) > 1000000ul)
#else
    if ((__uint32)(bk_millis() - t) > MAX_DELAY_MS)
#endif    
      break; // отложим выполнение скрипта
  }

  if (error) {
    done = true;
    return false;
  }

  return true;
}



bool bk_run_interrupt(__uint32 aTime) {
    if (done) {
        IP = 0;
        SP = MAX_STACK;
        SP_Base = SP;
        loopEnter = false;
        done = false;
        pause = 0;
        error = false;
    }
    else {
        if ((__uint32)(aTime - startTime) < pause)
            return true;
        pause = 0;
    }


    __uint8 cmd = code[IP++];
    if (cmd == 0)
        done = true;
    else if (cmd > 38)
        error = true;
    else
        cmdTable[cmd]();


    if (error) {
        done = true;
        return false;
    }

    return true;
}


void bk_break(__uint16 aPoint) {
  breakpoint = aPoint;
  isBreak = false;
  pause = 0;
}
