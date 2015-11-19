//Misc.h
//Used for miscellaneous functions
//Please edit with an actual text editor

#ifndef MISC_H
#define MISC_H

#include "track.h"
#include "watch.h"
#include "Energia.h"
#include "socket.h"

//Receives input
void miscInput(iint input, int selected) {
	switch(input) {
		case SWITCH_A:
			//TODO: Switch A
			break;
		case SWITCH_B:
			//TODO: Switch B
			break;
		case BUTTON_A:
			//TODO: Button A
			break;
		case BUTTON_B:
			//TODO: Button B
			break;
		case POT:
			//TODO: Smoke Weed
			break;
		default:
			//SUM TING WONG
			//REALLY WONG
			//REALLY REALLY WONG
			//REALLY REALLY REALLY WONG
			//RILEY WONG
			break;
	}
}

struct date {
  int year;
  int month;
  int day;
  int hour;
  int minute;
  int second;
  int ms;
};

//Hard coded begin date
struct date startDate = {2015, 10, 29, 18, 9, 45, 0};

//Current date
struct date currentDate = startDate;

//Hard coded day of month
int month[] = {31, (startDate.year % 4 == 0 && startDate.year % 100 != 0) || startDate.year % 400 == 0 ? 29 : 28, 31, 30, 31, 30, 31, 31, 30 ,31, 30, 31};

//Get current date based on program runtime
struct date getDate() {
  currentDate.ms += millis();
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
  
  return currentDate;
}

//Get time elapsed in date format
struct date getTimeElapsed(struct date a, struct date b) {
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
  struct date d = getTimeElapsed(a, b);
  
  return d.ms + d.second * 1000 + d.minute * 60 * 1000 + d.hour * 60 * 60 * 1000 + d.day * 24 * 60 * 60 * 1000 + d.month * month[d.month-1] * 24 * 60 * 60 * 1000 + d.year * (month[d.month-1] == 29 ? 366 : 365) * 24 * 60 * 60 * 1000;
}

//Returns time elapsed in s
int timeElapsedS(struct date a, struct date b) {
  struct date d = getTimeElapsed(a, b);
  
  return d.ms / 1000 + d.second + d.minute * 60 + d.hour * 60 * 60 + d.day * 24 * 60 * 60 + d.month * month[d.month-1] * 24 * 60 * 60 + d.year * (month[d.month-1] == 29 ? 366 : 365) * 24 * 60 * 60;
}

//Returns time s seconds in the future
struct date futureTime(struct date a, int s) {
  a.second += s;
  a.minute += a.second / 60;
  a.second = a.second % 60;

  //TODO rest going to bed today
  //TODO Do tomorrow
  return a;
}

#endif // MISC_H
