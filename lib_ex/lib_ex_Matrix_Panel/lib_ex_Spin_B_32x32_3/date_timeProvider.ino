//
//      FILE: lib_ex_Spin_B_32x32_3/date_timeProvider.ino
//    AUTHOR: Thomas Walloschke
//   VERSION: 0.3.2
//   PURPOSE: 32x32 LED Matrix Application (16x8x8 MC) - Date and Time Provider (ALPHA VERSION!) - Spinning Clock 
//      DATE: 2016-03-05
//   CONTACT: artkeller(at)gmx.de
// COPYRIGHT: © 2016 Thomas Walloschke
//   LICENSE: The MIT License (MIT)
//            Permission is hereby granted, free of charge, to any person obtaining a copy of this software and 
//            associated documentation files (the “Software”), to deal in the Software without restriction, including 
//            without limitation the rights to use, copy, modify, merge, publish, distribute, sublicense, and/or sell 
//            copies of the Software, and to permit persons to whom the Software is furnished to do so, subject to the 
//            following conditions:
//
//            The above copyright notice and this permission notice shall be included in all copies or substantial 
//            portions of the Software.
//
//            THE SOFTWARE IS PROVIDED “AS IS”, WITHOUT WARRANTY OF ANY KIND, EXPRESS OR IMPLIED, INCLUDING BUT NOT 
//            LIMITED TO THE WARRANTIES OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. 
//            IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, 
//            WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE  
//            SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.

//////////////////////////////////////////////////////////////////////////////////////////

#include "config.h"

// -- Date&Time structures
#include <Time.h>                     // cf. https://github.com/PaulStoffregen/Time

// -- RTC
#ifdef RTC_SYNC
#include <Wire.h>                     
#include <DS1307RTC.h>                // cf. https://github.com/PaulStoffregen/DS1307RTC
#endif

// -- Time elements
tmElements_t    tm;                   // global time_t structure

// -- Magic timestamps (Hack)
//    These magic variables are not initialized during reset.
//    They will be used to sync "recent-time" over "reset-borders".
//    The internal "time_t" variable can be setup in dependence on  
//    their values.
#if ARDUINO <= 10607
time_t          magicReboot   __attribute__ ((section (".noinit")));
time_t          magicTime     __attribute__ ((section (".noinit")));
#else
#error "Arduino IDE unknown - Magic timestamp may be wrong - Recent compiler section '.noinit' not evaluated!"
#endif

// -- Time Delay Corrections (IN CASE OF NO RTC SUPPORT)
//    During setup() "the compiler's time" may be used to preset the time_t variable
//    Sample input is: __DATE__ = "Sun 28 2016" and __TIME__ = "12:34:56"
//    After first load of "the compiler's time" there happens a "load-delay".
//    After reset there will a small "reset-delay".
//    We will try to adjust this time losses by setting empirically determined adjustment values.
//    ATTN: Time setting is done as an approximation and time is not "correct" in any way.
#define loadDelayTime    12
#define resetDelayTime    3

// Prototypes
#ifdef DEBUG_DATE_TIME_PROVIDER
void printTime(char * idString, time_t time);
#endif

////////////////////////////////////
//
// DateTime related functions
//

void setupTimeProvider() {

#if defined(DEBUG_DATE_TIME_PROVIDER) || defined(DEBUG)
  Serial.begin(115200);
#endif

  // -- Check time_t timeStatus
  //    (timeNotSet, timeNeedsSync, timeSet)
  timeStatus_t timestatus = timeStatus();

#ifdef DEBUG_DATE_TIME_PROVIDER
  // time_t
  timestatus == timeSet         ? Serial.println(F("  time_t: set is valid"))                         // valid time
  : timestatus == timeNotSet    ? Serial.println(F("  time_t: unset - setting required"))             // invalid time
  : timestatus == timeNeedsSync ? Serial.println(F("  time_t: unsynced - serving required"))          // Attention - time_t unsynced
  :                               Serial.println(F("  time_t: status unknown - should not happen"));  // should not happen
#endif

#ifdef DEBUG_DATE_TIME_PROVIDER
  printTime("now boot\t", now());
  printTime("magicReboot\t", magicReboot);
  printTime("magicTime\t", magicTime);
#endif

  // -- Set date and time
  if ( timestatus == timeNotSet ) {

#ifdef RTC_SYNC
    // RTC ONBOARD? RTC SET?
    if (RTC.chipPresent()) {

      tmElements_t _tm;          // local time_t structure
      if (RTC.read(_tm)) {

#ifdef DEBUG_DATE_TIME_PROVIDER
        Serial.println(F("  RTC: set is valid"));
#endif // DEBUG_DATE_TIME_PROVIDER
        // SET time_h by RTC ...

#ifdef DEBUG_DATE_TIME_PROVIDER
        printTime("now adjusted\t", now());
        Serial.println(F("  time_t: autosetting to RTC"));
#endif // DEBUG_DATE_TIME_PROVIDER
      } else {

        // SET RTC!
        Serial.println(F("The DS1307 is stopped.  Please run the SetTime"));
      }
      
#else // NO RTC_SYNC
    if (0) {
#endif // RTC_SYNC

    } else

      // -- Verify compilation-time (valid: 1.1.1970 .. 7.2.2106)
      if (getDate(__DATE__) && getTime(__TIME__)) {

#ifdef DEBUG_DATE_TIME_PROVIDER
        printTime("tm datetime\t", makeTime(tm));
#endif // DEBUG_DATE_TIME_PROVIDER

        // -- Verify magicReboot and magicTime
        if (magicReboot == makeTime(tm) and magicTime >= magicReboot ) {

          // -- Reset detected
          setTime(magicTime);                           // take magicTime to init time_h

#ifdef DEBUG_DATE_TIME_PROVIDER
          printTime("now\t\t", now());
#endif // DEBUG_DATE_TIME_PROVIDER

          adjustTime(resetDelayTime);                   // adjust time_t by reset-delay-time

#ifdef DEBUG_DATE_TIME_PROVIDER
          printTime("now adjusted\t", now());
          Serial.println(F("  time_t: autosetting from magicTime after compilation DATE and TIME start"));
#endif // DEBUG_DATE_TIME_PROVIDER
        }
        else {

          // -- Valid timestamp detected
          setTime( tm.Hour,                             // set time_t to compilation-time
                   tm.Minute,
                   tm.Second,
                   tm.Day,
                   tm.Month,
                   tmYearToCalendar(tm.Year)
                 );

          magicReboot = makeTime(tm);                   // init magicReboot with compilation

#ifdef DEBUG_DATE_TIME_PROVIDER
          printTime("now setup\t", now());
#endif // DEBUG_DATE_TIME_PROVIDER

          adjustTime(loadDelayTime);                    // adjust time_t by load-delay-time

#ifdef DEBUG_DATE_TIME_PROVIDER
          printTime("now adjusted\t", now());
          Serial.println(F("  time_t: autosetting from compilation DATE and TIME"));
#endif // DEBUG_DATE_TIME_PROVIDER
        }
      }
      else {
        if (magicReboot == SECS_YR_2000 and magicTime >= magicReboot ) {

          // -- Reset detected
          setTime(magicTime);                           // take magicTime to init time_h

#ifdef DEBUG_DATE_TIME_PROVIDER
          printTime("now setup\t", now());
#endif // DEBUG_DATE_TIME_PROVIDER

          adjustTime(3);                                // adjust time_t by reset-delay-time

#ifdef DEBUG_DATE_TIME_PROVIDER
          printTime("now adjusted\t", now());
          Serial.println(F("  time_t: autosetting from magicTime after millenium start"));
#endif // DEBUG_DATE_TIME_PROVIDER
        } else {

          // -- Coldtstart detected
          setTime(SECS_YR_2000);                        // oterwise no idea what time it is - set to millenium to be on the safe side

          magicReboot = SECS_YR_2000;

#ifdef DEBUG_DATE_TIME_PROVIDER
          printTime("now setup\t", now());
#endif // DEBUG_DATE_TIME_PROVIDER

          adjustTime(0);                                // adjust time_t by load-delay-time

#ifdef DEBUG_DATE_TIME_PROVIDER
          printTime("now adjusted\t", now());
          Serial.println(F("  time_t: autosetting to millenium start"));
#endif // DEBUG_DATE_TIME_PROVIDER
        }
      }
  }
}

long syncMagicTime() {
  return magicTime = now();
}

bool getTime(const char *str)
{
  int Hour, Min, Sec;

  if (sscanf(str, "%d:%d:%d", &Hour, &Min, &Sec) != 3) return false;
  tm.Hour = Hour;
  tm.Minute = Min;
  tm.Second = Sec;
  return true;
}

bool getDate(const char *str)
{
  char Month[12];
  int Day, Year;
  uint8_t monthIndex;

  if (sscanf(str, "%s %d %d", Month, &Day, &Year) != 3) return false;
  for (monthIndex = 0; monthIndex <= 12; monthIndex++) {
    if (strcmp(Month, monthShortStr(monthIndex)) == 0) break;
  }
  if (monthIndex > 12) return false;
  tm.Day = Day;
  tm.Month = monthIndex;
  tm.Year = CalendarYrToTm(Year);
  return true;
}

#ifdef DEBUG_DATE_TIME_PROVIDER
void printDigits(int number) {
  if (number >= 0 && number < 10) {
    Serial.write('0');
  }
  Serial.print(number);
}
#endif // DEBUG_DATE_TIME_PROVIDER

#ifdef DEBUG_DATE_TIME_PROVIDER
void printTime(char * idString, time_t time) {

  tmElements_t    tm;   // local to secure the global tm object
  breakTime(time, tm);

  Serial.print(idString);

  // display timeStatus timeNotSet, timeNeedsSync, timeSet
  timeStatus_t timestatus = timeStatus();
  timestatus == timeSet         ? Serial.print("+ ")    // valid time
  : timestatus == timeNotSet    ? Serial.print("- ")    // invalid time
  : timestatus == timeNeedsSync ? Serial.print("! ")    // Attention - time_t unsynced
  :                               Serial.print("? ")  ; // should not happen

#if 0
  // print Stage
  Stage == 0   ? Serial.print("time_t: ")
  : Stage == 1 ? Serial.print("RTC:    ")
  : Stage == 2 ? Serial.print("DCF77:  ")
  :              Serial.print("?:      "); // should not happen
#endif // 0

  Serial.print("Time = ");
  printDigits(tm.Hour);
  Serial.write(':');
  printDigits(tm.Minute);
  Serial.write(':');
  printDigits(tm.Second);
  Serial.print(", Date (DD.MM.YYYY) = ");
  printDigits(tm.Day);
  Serial.write('.');
  printDigits(tm.Month);
  Serial.write('.');
  printDigits(tmYearToCalendar(tm.Year));

#ifdef RTC_SYNC
  Serial.print("(");
  timeStatus_t RTCstatus_v = RTCStatus();
  RTCstatus_v == timeSet         ? Serial.write('+')      // valid time
  : RTCstatus_v == timeNotSet    ? Serial.write('-')      // invalid time
  : RTCstatus_v == timeNeedsSync ? Serial.write('!')      // Attention - RTC unsynced
  :                                Serial.write('?')  ;   // should not happen
  Serial.print(")");
#endif // RTC_SYNC

  Serial.println();
}
#endif // DEBUG_DATE_TIME_PROVIDER

#ifdef RTC_SYNC
timeStatus_t RTCStatus() {
  tmElements_t _tm_;

  if (RTC.read(_tm_)) {
    return timeSet;
  } else {
    if (RTC.chipPresent()) {
      return timeNotSet;
    } else {
      return (timeStatus_t)(1);
    }
  }
}

#endif // RTC_SYNC

//////////////////////////////////////////////////////////////////////////////////////////

/* end-of-inotab-file */

