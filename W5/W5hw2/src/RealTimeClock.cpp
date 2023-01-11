/*
 * RealTimeClock.cpp
 *
 *  Created on: 2022年10月9日
 *      Author: kendrick807
 */

#include <mutex>
#include "Imutex.h"
#include "RealTimeClock.h"
// Get current time

RealTimeClock::RealTimeClock(int ticksPerSecond) : ticks_per_sec(ticksPerSecond){
	tm set_time;
	this->hour = set_time.tm_hour;
	this->min = set_time.tm_min;
	this->sec = set_time.tm_sec;
	set_time.tm_sec = 35;
	set_time.tm_min = 58;
	set_time.tm_hour = 23;
	set_time.tm_mday = 1;
	set_time.tm_mon = 0;
	set_time.tm_year = 100;
	this->currentTime = mktime(&set_time);

}


RealTimeClock::~RealTimeClock() {}
RealTimeClock::RealTimeClock(int ticksPerSecond, time_t currentTime) : currentTime(currentTime), ticks_per_sec(ticksPerSecond) {
	tm *set_time = localtime(&currentTime);
	this->hour = set_time->tm_hour;
	this->min = set_time->tm_min;
	this->sec = set_time->tm_sec;
}
RealTimeClock::RealTimeClock(int ticksPerSecond, tm now) : ticks_per_sec(ticksPerSecond) {
	this->hour = now.tm_hour;
	this->min = now.tm_min;
	this->sec = now.tm_sec;
	this->currentTime = mktime(&now);
}

void RealTimeClock::gettime(tm *now){
std::lock_guard<Imutex> lock(guard);
now->tm_hour = this->hour;
now->tm_min = this->min;
now->tm_sec =   this->sec;
// do same for seconds, years, months
// you may not do any kind of processing or printing here
// all processi ng must be done outside the critical section (outside this function)
// Interrupts are enabled/restored at the end by lock_guard destructor
}
void RealTimeClock::tick(){
	std::lock_guard<Imutex> lock(guard);
		this->passed_tick++;

	if(this->passed_tick >= this->ticks_per_sec){
		this->currentTime++;
		this->passed_tick = 0;
	    time_t test_time = this->currentTime;
		tm *temp_time = localtime(&(test_time));
		this->hour = temp_time->tm_hour;
		this->min = temp_time->tm_min;
		this->sec = temp_time->tm_sec;
	}

}


