#include "utils.h"
#include <stdio.h>
#include <stdlib.h>
#include <stdarg.h>


void Utils::serialPrintf(const char *format, ...) 
{ // for debugging
  static char buffer[100]; // one threaded so whatever
  va_list args;
  
  va_start(args, format);
  vsnprintf(buffer, sizeof(buffer), format, args);
  va_end(args);
  Serial.print(buffer);
}

int Utils::getFsrNewton()
{
  static int fsrReading = 0;
  static int fsrVoltage = 0;
  static unsigned long fsrResistance = 0;
  static unsigned long fsrConductance = 0;
  
  fsrReading = analogRead(fsrPin);
  
  // Map the analog reading (0-1023) to voltage (0-5000mV)
  fsrVoltage = map(fsrReading, 0, 1023, 0, 5000);
  
  if (fsrVoltage == 0) {
    return 0;  // No pressure detected
  } else {
    // Calculate the FSR resistance based on the voltage
    fsrResistance = (5000 - fsrVoltage) * 10000 / fsrVoltage;
    
    // Calculate the conductance in micromhos (inverse of resistance)
    fsrConductance = 1000000 / fsrResistance;
    
    // Use the guide to approximate force
    long fsrForce;
    if (fsrConductance <= 1000) {
      fsrForce = fsrConductance / 80;
    } else {
      fsrForce = (fsrConductance - 1000) / 30;
    }
    
    return fsrForce;
  }
}
