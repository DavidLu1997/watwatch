#include "date.h"
#include "values.h"

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
	currentDate.hour = currentDate.hour % 24;
}

//Returns absolute value difference between 2 dates
struct date difference(struct date a, struct date b){
	struct date d;
	d.ms = abs(b.ms - a.ms);
	d.second = abs(b.second - a.second); 
	d.minute = abs(b.minute - a.minute);
	d.hour = abs(b.hour - a.hour);
	return d;
}

//Returns time elapsed in ms
int timeElapsedMs(struct date a, struct date b) {
    return (b.ms - a.ms) + (b.second - a.second) * 1000 + (b.minute - a.minute) * 60 * 1000 + (b.hour - a.hour) * 60 * 60 * 1000;
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
	a.hour = a.hour % 24;
	return a;
}

void drawSetDate() {

}

void drawSettings() {

}

void drawSetTimes() {

}