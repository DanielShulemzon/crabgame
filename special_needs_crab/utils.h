#pragma once

#include "globals.h"

namespace Utils {
  void serialPrintf(const char *format, ...);

  int getFsrNewton();

  bool matchingDistance(const double read1, const double read2);

  void testPixyUltrasonicError();
}
