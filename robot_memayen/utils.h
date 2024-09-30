#ifndef _UTILS_H
#define _UTILS_H

#include "globals.h"

void reset_motors();

void serial_printf(const char *format, ...);

void motors_setup();

void set_motors_speed(const uint8_t speed);

#endif