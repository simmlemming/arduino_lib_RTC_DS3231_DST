# arduino_lib_RTC_DS3231_DST
Addition to **RTClib by JeeLabs http://news.jeelabs.org/code/** that takes care of Daylight Savings Time (DST) for Europe.
https://en.wikipedia.org/wiki/Summer_Time_in_Europe

TL;DR
*Winter* time is considered to be the *baseline*, and during *DST* period clock shows time that's 1 hour ahead of baseline.

Designed to be a drop-in replacement for *RTClib* (when working with *RS3231* sensors):

Code with *RTClib*
```c++
#include <RTClib.h>
RTC_DS3231 rtc;
```
Just replace these lines with
```c++
#include <RTC_DS3231_DST.h>
RTC_DS3231_DST rtc;
```
and the rest of the may remain untouched.
