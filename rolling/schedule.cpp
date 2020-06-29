/*
Copyright © 2015, BVAgile. All rights reserved.
Contacts: <bvagile@gmail.com>
*/

#include "schedule.h"
#include "string.h"

//#define LEAP_YEAR(Y)     ( ((1970+(Y))>0) && !((1970+(Y))%4) && ( ((1970+(Y))%100) || !((1970+(Y))%400) ) )
#define LEAP_YEAR(Y)     ( !((1970+(Y))%4) )

enum Periodicity { perMinute = 0, perHour = 1, perDay = 2, perWday = 3, perMonth = 4, perYear = 5, perOnce = 6, perNone = 7 };

static  const __uint8 monthDays[] = { 31,28,31,30,31,30,31,31,30,31,30,31 }; // API starts months from 1, this array starts from 0
static __uint32 base[7]; // Minute, Hour, Day, Week, Month, Year, Once
static TimeStamp last_time = 0; // UTC в миллисекундах

__int8 canals[NUMBER_CANAL];


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

static struct Time tm;

// aTime - локальное время в секундах
static void set_time(__uint32 time) {
	__uint8 year, month, monthLength;
	unsigned long days;

	tm.total_sec = time;
	tm.Second = time % 60;
	base[perMinute] = time - tm.Second;
	time /= 60; // now it is minutes
	tm.Minute = time % 60;
	base[perHour] = base[perMinute] - tm.Minute * 60;
	time /= 60; // now it is hours
	tm.Hour = time % 24;
	base[perDay] = base[perHour] - ((__uint32)tm.Hour * 60 * 60);

	time /= 24; // now it is days
	tm.Wday = ((time + 3) % 7);  // понедельник это 0 
	base[perWday] = base[perDay] - ((__uint32)tm.Wday * 60 * 60 * 24);

	year = 0;
	days = 0;
	while ((unsigned)(days += (LEAP_YEAR(year) ? 366 : 365)) <= time) {
		year++;
	}
	tm.Year = year; // year is offset from 1970 

	days -= LEAP_YEAR(year) ? 366 : 365;
	time -= days; // now it is days in this year, starting at 0

	base[perYear] = base[perDay] - (time * 60 * 60 * 24);

	days = 0;
	month = 0;
	monthLength = 0;
	for (month = 0; month < 12; month++) {
		if (month == 1) { // february
			if (LEAP_YEAR(year))
				monthLength = 29;
			else
				monthLength = 28;
		}
		else
			monthLength = monthDays[month];

		if (time >= monthLength)
			time -= monthLength;
		else
			break;
	}
	tm.Month = month + 1;  // jan is month 1  
	tm.Day = time + 1;     // day of month

	base[perMonth] = base[perDay] - (time * 60 * 60 * 24);

	if (month < 3)
		base[perYear] -= 26438400; // база начинается с 1 марта
	else
	{
		base[perYear] += 5097600;
		if (LEAP_YEAR(year))
			base[perYear] += 86400; // прибавить сутки
	}
	base[perOnce] = 0;
}



// запускаем каждую секунду
// aTime - локальное время в секундах
static bool go_time(__uint32 aTime) {
	if (++tm.total_sec != aTime) {
		set_time(aTime);
		return false;
	}

	if (++tm.Second > 59) {
		tm.Second = 0;
		base[perMinute] = tm.total_sec; // если 0 секунд, то сменить базу ежеминутных событий
		if (++tm.Minute > 59) {
			tm.Minute = 0;
			base[perHour] = tm.total_sec; // если 0 минут, то сменить базу ежечасных событий
			if (++tm.Hour > 23) {
				tm.Hour = 0;
				base[perDay] = tm.total_sec; // если 0 часов, то сменить базу ежедневных событий
				if (++tm.Wday > 6) {
					tm.Wday = 0;
					base[perWday] = tm.total_sec; // если Понедельник, то сменить базу еженедельных событий
				}
				char maxDays = monthDays[tm.Month - 1];
				if ((!((tm.Year + 2) & 3)) && (tm.Month == 2)) // если февраль високосного года
					maxDays++;
				if (++tm.Day > maxDays) {
					tm.Day = 1;
					base[perMonth] = tm.total_sec; // если 1 число, то сменить базу ежемесячных событий
					if (++tm.Month > 12) {
						tm.Month = 1;
						tm.Year++;
					}
					else
						if (tm.Month == 3) // если Март то сменить базу ежегодных событий
							base[perYear] = tm.total_sec;
				}
			}
		}
	}
	return true;
}

void sch_init(TimeStamp aTime) {
	aTime = aTime / 1000 - getBias();
	set_time((__uint32)aTime);
}


void sch_run(TimeStamp aTime) {
	if ((last_time <= aTime) && (aTime < (last_time + 1000))) // если не наступила новая секунда и время не откатилось назад
		return;

	if ((aTime < 31536000000) || (aTime > 4102444800000)) // 1 января 1971 - 1 января 2100
		return;

	TimeStamp t = aTime / 1000; // переведём в секунды
	last_time = t * 1000; // сохраним последнее время

	t -= getBias(); // переведём в локальное время

	if (!go_time((__uint32)t)) // если время увеличилось НЕ на одну на секунду
		set_time((__uint32)t);


	//---------------------------------
	bool prev_active[NUMBER_CANAL];
	__uint8 prev_periods[NUMBER_CANAL];

	memset(prev_active, false, NUMBER_CANAL);
	memset(prev_periods, 0, NUMBER_CANAL);
	memset(canals, -128, NUMBER_CANAL);

	for (unsigned char i = 0; i < 255; i++) {
		__uint8 eventInfo = getEventInfo(i);
		if (eventInfo & 0x80)
			break;

		__uint8 canal = eventInfo >> 3;

		if ((prev_active[canal] == true) || (eventInfo >= prev_periods[canal])) {
			__int64 current_base = base[eventInfo & 0x07];
			__uint32 start = getStartEvent(i);
			__uint32 stop = getStopEvent(i);
			bool reverse = false;

			if (stop < start) { // если время перевёрнуто
				__uint32 temp = start;
				start = stop;
				stop = temp;
				reverse = true;
			}

			bool active = (tm.total_sec >= (current_base + start)) && (tm.total_sec < (current_base + stop));
			if (active) // Если текущее событие активно - канал устанавливается, и программа ищет следующее по порядку событие.
				canals[canal] = reverse ? -128 : getValueEvent(i);
			else {
				if (eventInfo < prev_periods[canal]) // Если текущее событие неактивно - канал очищается в том случае, если предыдущее
					canals[canal] = -128;             // событие было с большей периодичностью. Далее программа ищет следующее событие,
													   // с периодичностью равной или большей периодичности текущего события.
			}                                          // Если такого события не находиться, программа выходит из алгоритма.
			prev_active[canal] = active;
			prev_periods[canal] = eventInfo;
		}
	}
}

/*
void sch_run(TimeStamp aTime) {
	if ((last_time <= aTime) && (aTime < (last_time + 1000))) // если не наступила новая секунда и время не откатилось назад
		return;

	if ((aTime < 31536000000) || (aTime > 4102444800000)) // 1 января 1971 - 1 января 2100
		return;

	TimeStamp t = aTime / 1000; // переведём в секунды
	last_time = t * 1000; // сохраним последнее время

	t -= getBias(); // переведём в локальное время

	if (!go_time((__uint32)t)) // если время увеличилось НЕ на одну на секунду
		set_time((__uint32)t);


	//---------------------------------
	char flags[NUMBER_CANAL];
	char old_periods[NUMBER_CANAL];

	memset(flags, 0, NUMBER_CANAL);
	memset(old_periods, 0, NUMBER_CANAL);
	memset(canals, false, NUMBER_CANAL);

	for (unsigned char i = 0; i < 255; i++) {
		unsigned char eventInfo = getEventInfo(i);
		if (eventInfo & 0x80)
			break;

		//----------------------------------
		bool state;
		bool non_reverse = true;
		__int64 current_base;
		__uint32 start;
		__uint32 stop;

		current_base = base[eventInfo & 0x07];

		start = getStartEvent(i);
		stop = getStopEvent(i);

		if (stop < start) {
			__uint32 temp = start;
			start = stop;
			stop = temp;
			non_reverse = false; // время перевёрнуто
		}

		state = ((tm.total_sec >= (current_base + start)) && (tm.total_sec < (current_base + stop))) ? true : false;

		//----------------------------------


		__uint8 canal = eventInfo >> 3;

		if ((flags[canal] == true) || (eventInfo >= old_periods[canal])) {
			if (state) {      // Если текущее событие активно - канал устанавливается, и программа ищет следующее по порядку событие.
				flags[canal] = non_reverse;  // Если такого события не находиться, программа выходит из алгоритма
				canals[canal] = non_reverse;
			}
			else {
				flags[canal] = false;
				if (eventInfo < old_periods[canal]) // Если текущее событие неактивно - канал очищается в том случае, если предыдущее
					canals[canal] = false;             // событие было с большей периодичностью. Далее программа ищет следующее событие,
													   // с периодичностью равной или большей периодичности текущего события.
			}                                          // Если такого события не находиться, программа выходит из алгоритма.
			old_periods[canal] = eventInfo;
		}
	}
}
*/
