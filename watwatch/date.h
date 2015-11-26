//Date.h
//Used for date functions

#ifndef DATE_H
#define DATE_H

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

#endif // DATE_H