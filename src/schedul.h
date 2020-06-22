/*
Copyright © 2015, BVAgile. All rights reserved.
Contacts: <bvagile@gmail.com>
*/

/* Расписание дествительно только в ограниченном диапазоне с 1971 по 2099 год */

#ifndef _schedul_H_
#define _schedul_H_

#include "Types.h"

#define NUMBER_CANAL 4

// каналы
extern bool canals[NUMBER_CANAL];

// инициализация
// aTime - UTC время в миллисекундах
void sch_init(TimeStamp aTime);

// функцию вызывать как можно чаще
// aTime - UTC время в миллисекундах
void sch_run(TimeStamp aTime);

// получить смещение временной зоны в секундах
__int32 getBias();

// получить информацию о событии
// младшие три бита - периодичность события
// следующие четыре бита - номер канала  
// старший бит - использование события (0-используется)
__uint8 getEventInfo(__uint8 aIndex);

// получить относительное начальное время события (в секундах)
__uint32 getStartEvent(__uint8 aIndex);

// получить относительное конечное время события (в секундах)
__uint32 getStopEvent(__uint8 aIndex);


struct Time {
  __uint8 Second; // seconds after the minute (from 0)
  __uint8 Minute; // minutes after the hour (from 0)
  __uint8 Hour; // hour of the day (from 0)
  __uint8 Wday; // day of week, sunday is day 1
  __uint8 Day; // day of the month (from 1)
  __uint8 Month; // month of the year (from 1)
  __uint8 Year; // offset from 1970;
  __uint32 total_sec; // количество секунд с 1970года 1 января 00:00:00 (локальное время)
};

Time* sch_getTime();

#endif
