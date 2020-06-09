/*
Copyright © 2015, BVAgile. All rights reserved.
Contacts: <bvagile@gmail.com>
*/

#include "Types.h"
#include <Wire.h>

#define DS1307_ID 0x68 

#define SECS_PER_MIN  ((__uint32)(60UL))
#define SECS_PER_HOUR ((__uint32)(3600UL))
#define SECS_PER_DAY  ((__uint32)(SECS_PER_HOUR * 24UL))
#define SECS_PER_YEAR ((__uint32)(SECS_PER_DAY * 365UL)) // TODO: ought to handle leap years

#define LEAP_YEAR(Y)     ( ((1970+(Y))>0) && !((1970+(Y))%4) && ( ((1970+(Y))%100) || !((1970+(Y))%400) ) )
static  const __uint8 monthDays[]={31,28,31,30,31,30,31,31,30,31,30,31}; // API starts months from 1, this array starts from 0


struct Time { 
  __uint8 Second; 
  __uint8 Minute; 
  __uint8 Hour; 
  __uint8 Wday;   // day of week, sunday is day 1
  __uint8 Day;
  __uint8 Month; 
  __uint8 Year;   // offset from 1970; 
}; 


static void breakTime(__uint32 time, Time &tm) {
// break the given time_t into time components
// this is a more compact version of the C library localtime function
// note that year is offset from 1970 !!!

  __uint8 year;
  __uint8 month, monthLength;
  unsigned long days;

  tm.Second = time % 60;
  time /= 60; // now it is minutes
  tm.Minute = time % 60;
  time /= 60; // now it is hours
  tm.Hour = time % 24;
  time /= 24; // now it is days
  tm.Wday = ((time + 4) % 7) + 1;  // Sunday is day 1 
  
  year = 0;  
  days = 0;
  while((unsigned)(days += (LEAP_YEAR(year) ? 366 : 365)) <= time) {
    year++;
  }
  tm.Year = year; // year is offset from 1970 
  
  days -= LEAP_YEAR(year) ? 366 : 365;
  time -= days; // now it is days in this year, starting at 0
  
  days = 0;
  month = 0;
  monthLength = 0;
  for (month = 0; month < 12; month++) {
    if (month == 1) { // february
      if (LEAP_YEAR(year)) {
        monthLength = 29;
      } else {
        monthLength = 28;
      }
    } else {
      monthLength = monthDays[month];
    }
    
    if (time >= monthLength) {
      time -= monthLength;
    } else {
        break;
    }
  }
  tm.Month = month + 1;  // jan is month 1  
  tm.Day = time + 1;     // day of month
}

static __uint32 makeTime(const Time &tm) {   
// assemble time elements into time_t 
// note year argument is offset from 1970 (see macros in time.h to convert to other formats)
// previous version used full four digit year (or digits since 2000),i.e. 2009 was 2009 or 9
  
  int i;
  __uint32 seconds;

  // seconds from 1970 till 1 jan 00:00:00 of the given year
  seconds= tm.Year*(SECS_PER_DAY * 365);
  for (i = 0; i < tm.Year; i++) {
    if (LEAP_YEAR(i)) {
      seconds +=  SECS_PER_DAY;   // add extra days for leap years
    }
  }
  
  // add days for this year, months start from 1
  for (i = 1; i < tm.Month; i++) {
    if ( (i == 2) && LEAP_YEAR(tm.Year)) { 
      seconds += SECS_PER_DAY * 29;
    } else {
      seconds += SECS_PER_DAY * monthDays[i-1];  //monthDay array starts from 0
    }
  }
  seconds += (tm.Day-1) * SECS_PER_DAY;
  seconds += tm.Hour * SECS_PER_HOUR;
  seconds += tm.Minute * SECS_PER_MIN;
  seconds += tm.Second;
  return seconds; 
}


// Convert Decimal to Binary Coded Decimal (BCD)
static __uint8 dec2bcd(__uint8 num)
{
  return ((num/10 * 16) + (num % 10));
}

// Convert Binary Coded Decimal (BCD) to Decimal
static __uint8 bcd2dec(__uint8 num)
{
  return ((num/16 * 10) + (num % 16));
}


bool setRealTime(TimeStamp aTime) {
  Time tm;
  breakTime((__uint32)(aTime / 1000), tm);
 
  Wire.beginTransmission(DS1307_ID); // transmit to ds1307
  Wire.write((uint8_t)0x00); // reset register pointer  
  Wire.write((uint8_t)0x80); // Stop the clock. The seconds will be written last
  Wire.write(dec2bcd(tm.Minute));
  Wire.write(dec2bcd(tm.Hour));      // sets 24 hour format
  Wire.write(dec2bcd(tm.Wday));   
  Wire.write(dec2bcd(tm.Day));
  Wire.write(dec2bcd(tm.Month));
  Wire.write(dec2bcd(tm.Year - 30)); 
  if (Wire.endTransmission() != 0)
    return false;
  Wire.beginTransmission(DS1307_ID); // transmit to ds1307
  Wire.write(0);      // register pointer 
  Wire.write(dec2bcd(tm.Second));
  if (Wire.endTransmission() != 0)
    return false;
}

TimeStamp getRealTime() {
  Wire.beginTransmission(DS1307_ID); // transmit to ds1307
  Wire.write(0);      // register pointer 
  if (Wire.endTransmission() != 0)
      return 0;
  delayMicroseconds(5); // не менее 4.7мкс

  //Прочитать содержимое DS1307:
  Wire.requestFrom(DS1307_ID, 7);    // request 7 bytes from ds1307
  if (Wire.available() < 7)
    return 0;

  __uint8 sec;
  Time tm;
  sec = Wire.read();
  if (sec & 0x80)
    return 0; // clock is halted 
  tm.Second = bcd2dec(sec & 0x7f);   
  tm.Minute = bcd2dec(Wire.read() );
  tm.Hour =   bcd2dec(Wire.read() & 0x3f);  // mask assumes 24hr clock
  tm.Wday = bcd2dec(Wire.read() );
  tm.Day = bcd2dec(Wire.read() );
  tm.Month = bcd2dec(Wire.read() );
  tm.Year = bcd2dec(Wire.read()) + 30;

  TimeStamp t = makeTime(tm);
  return t * 1000;
}
