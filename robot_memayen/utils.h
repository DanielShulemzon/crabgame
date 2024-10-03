#ifndef _UTILS_H
#define _UTILS_H

#include "globals.h"

void resetMotors();

void motorsSetup();

void setMotorsSpeed(const uint8_t speed);

void serialPrintf(const char *format, ...);

#endif