//Misc.h
//Used for miscellaneous functions

#ifndef MISC_H
#define MISC_H

#include "Energia.h"

#include "values.h"

//Declarations
struct date difference(struct date a, struct date b);
int timeElapsedMs(struct date a, struct date b);
int timeElapsedS(struct date a, struct date b);
struct date futureTime(struct date a, int s);
void drawSettings();
void drawSetTimes();
void drawSetDate();
void updateDate();
struct date getDate();

//Get date
struct date getDate() {
  return currentDate;
}

//UpdateDate, updates date, called continuously
void updateDate() {
  currentDate.ms++;
  currentDate.second += currentDate.ms / 1000;
  currentDate.ms = currentDate.ms % 1000;
  currentDate.minute += currentDate.second / 60;
  currentDate.second = currentDate.second % 60;
  currentDate.hour += currentDate.minute / 60;
  currentDate.minute = currentDate.minute % 60;
  currentDate.day += currentDate.hour / 24;
  currentDate.hour = currentDate.hour % 24;
  currentDate.month += currentDate.day / month[currentDate.month - 1];
  currentDate.day = currentDate.day % month[currentDate.month - 1];
  currentDate.year += currentDate.month / 12;
  currentDate.month = currentDate.month % 12;
}

//Returns absolute value difference between 2 dates
struct date difference(struct date a, struct date b){
  struct date d;
  d.ms = abs(b.ms - a.ms);
  d.second = abs(b.second - a.second); 
  d.minute = abs(b.minute - a.minute);
  d.hour = abs(b.hour - a.hour);
  d.day = abs(b.day - a.day);
  d.month = abs(b.month - a.month);
  d.year = abs(b.year - a.year);
  return d;
}

//Returns time elapsed in ms
int timeElapsedMs(struct date a, struct date b) {
    return (b.ms - a.ms) + (b.second - a.second) * 1000 + (b.minute - a.minute) * 60 * 1000 + (b.hour - a.hour) * 60 * 60 * 1000 + (b.day - a.day) * 24 * 60 * 60 * 1000 + (b.month - a.month) * month[b.month - a.month - 1] * 24 * 60 * 60 * 1000 + (b.year - a.year) * (month[b.month - a.month - 1] == 29 ? 366 : 365) * 24 * 60 * 60 * 1000;
}

//Returns time elapsed in s
int timeElapsedS(struct date a, struct date b) {
    return timeElapsedMs(a, b) / 1000;
}

//Returns time s seconds in the future
struct date futureTime(struct date a, int s) {
  a.second += s;
  a.minute += a.second / 60;
  a.second = a.second % 60;
  a.hour += a.minute / 60;
  a.minute = a.minute % 60;
  a.day + a.hour / 24;
  a.hour = a.hour % 24;
  a.month += a.day / month[a.month - 1];
  a.day = a.day % month[a.month - 1];
  a.year += a.month / 12;
  a.month = a.month % 12;
  return a;
}

void drawSetDate() {

}

void drawSettings() {

}

void drawSetTimes() {

}

#endif // MISC_H

