#include "solarTime.h"

static float lat;
static float lon;
static int timezone;

static __uint8 lastDay = 0;
static __uint8 lastMonth = 0;

static float sunrise = NAN;
static float sunset = NAN;

void solarInit(float aLatitude, float aLongitude, int aTimezone) {
  lat = aLatitude / 57.295779513082322;
  lon = -aLongitude / 57.295779513082322;
  timezone = aTimezone;
}

float solarCompute(__uint8 aDay, __uint8 aMonth, bool aRs) {
    float y, decl, eqt, ha, lon, lat;
    __uint8 a;
    int seconds;


    if ((lastDay == aDay) && (lastMonth == aMonth)) {
      if (aRs)
        return sunrise;
      else
        return sunset;
    }
    
    lastDay = aDay;
    lastMonth = aMonth;
    
    aMonth--;
    aDay--;
//    lon = -longitude / 57.295779513082322;
//    lat = latitude / 57.295779513082322;


    //approximate hour;
    a = 6;
    if (aRs) a = 18;

    // approximate day of year
    y = aMonth * 30.4375 + aDay + a / 24.0; // 0... 365

    // compute fractional year
    y *= 1.718771839885e-02; // 0... 1

    // compute equation of time... .43068174
    eqt = 229.18 * (0.000075 + 0.001868 * cos(y) - 0.032077 * sin(y) - 0.014615 * cos(y * 2) - 0.040849 * sin(y * 2));

    // compute solar declination... -0.398272
    decl = 0.006918 - 0.399912 * cos(y) + 0.070257 * sin(y) - 0.006758 * cos(y * 2) + 0.000907 * sin(y * 2) - 0.002697 * cos(y * 3) + 0.00148 * sin(y * 3);

    //compute hour angle
    ha = (cos(1.585340737228125) / (cos(lat) * cos(decl)) - tan(lat) * tan(decl));

    if (fabs(ha) > 1.0) {// we're in the (ant)arctic and there is no rise(or set) today!
        return NAN;
    }

    ha = acos(ha);
    if (aRs == false) ha = -ha;

    // compute minutes from midnight
    seconds = 720 + 4 * (lon - ha) * 57.295779513082322 - eqt;

    seconds = seconds * 60 + timezone;
    seconds = seconds % 86400;
 
    if (aRs)
      sunrise = seconds;
    else
      sunset = seconds;


    return seconds;
}
