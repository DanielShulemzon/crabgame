#include "utils.h"
#include <stdio.h>
#include <stdarg.h>


void serialPrintf(const char *format, ...) { // for debugging
  static char buffer[100];
  va_list args;
  va_start(args, format);
  vsnprintf(buffer, sizeof(buffer), format, args);
  va_end(args);
  Serial.print(buffer);
}


