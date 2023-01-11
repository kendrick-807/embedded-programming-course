/*
 * Imutex.h
 *
 *  Created on: 2022年10月9日
 *      Author: kendrick807
 */
#ifndef IMUTEX_H_
#define IMUTEX_H_
class Imutex {
public:
Imutex();
~Imutex();
void lock();
void unlock();
private:
bool enable;
};
#endif
