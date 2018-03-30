#include "RTC_DS3231_DST.h"

bool RTC_DS3231_DST::is_dst_period(DateTime date) {
  // DST period begins at 02:00 on last Sunday of March
  // and ends at 03:00 on last Sunday of October
  DateTime dst_begin = find_last_sunday_of(date.year(), 3, 2, 0);
  DateTime dst_end = find_last_sunday_of(date.year(), 10, 3, 0);

  return dst_end > date && date > dst_begin;
}

DateTime RTC_DS3231_DST::find_last_sunday_of(int y, int m, int h, int minute) {
  int d = 31; // Works for March and October, because they have 31 days.
  
  DateTime last_sunday;
  do {
    last_sunday = DateTime(y, m, d--, h, minute, 0);
  } while (last_sunday.dayOfTheWeek() != 0);

  return last_sunday;
}

DateTime RTC_DS3231_DST::now() {
  // RTC stores non DST time, we just add 1 hour to value returned from
  // this function when it's DST period.
  DateTime n = RTC_DS3231::now();
  
  if (!is_dst_period(n)) {
  	return n;
  }
  
  DateTime now_dst = DateTime(n.year(), n.month(), n.day(), n.hour()+1, n.minute(), n.second());
  return now_dst;
}

void RTC_DS3231_DST::adjust(const DateTime &date) {
  // RTC stores non DST time, need to substract 1 hour from given date
  // before setting it to RTC when it's DST period.
  DateTime date_dst = date;

  if (is_dst_period(date)) {
    date_dst = DateTime(date.year(), date.month(), date.day(), date.hour()-1, date.minute(), date.second());
  }

  RTC_DS3231::adjust(date_dst);
}

bool operator>(const DateTime &left, const DateTime &right) {
  return left.secondstime() > right.secondstime();
}

void print(DateTime date) {
  Serial.print(date.year());
  Serial.print("/");
  Serial.print(date.month());
  Serial.print("/");
  Serial.print(date.day());
  
  Serial.print(" ");
  Serial.print(date.hour());
  Serial.print(":");
  Serial.print(date.minute());
  Serial.print(":");
  Serial.println(date.second());
}
