/*
 * RealTimeClock.h
 *
 *  Created on: 2022年10月9日
 *      Author: kendrick807
 */

#ifndef REALTIMECLOCK_H_
#define REALTIMECLOCK_H_
#include "Imutex.h"
#include <ctime>

class RealTimeClock {
public:
// You must also provide a copnstructor variant with systick rate and current time
RealTimeClock(int ticksPerSecond);
virtual ~RealTimeClock();
void gettime(tm *now);
RealTimeClock(int ticksPerSecond, tm now);
RealTimeClock(int ticksPerSecond, time_t currentTime);
void tick();

private:
Imutex guard;
volatile time_t currentTime;
volatile int hour;
volatile int min;
volatile int sec;
volatile int ticks_per_sec;
volatile int passed_tick;
};



#endif /* REALTIMECLOCK_H_ */
