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


#endif
