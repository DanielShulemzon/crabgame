#include "utils.h"
#include <stdio.h>
#include <stdlib.h>
#include <stdarg.h>


void Utils::serialPrintf(const char *format, ...) 
{
  static char buffer[128]; // good
  va_list args;
  
  va_start(args, format);
  vsnprintf(buffer, sizeof(buffer), format, args);
  va_end(args);
  
  Serial.print(buffer);
}

int Utils::getFsrNewton()
{
  int fsrReading = analogRead(fsrPin);
  int fsrVoltage = map(fsrReading, 0, 1023, 0, 5000);
  
  if (fsrVoltage == 0) return 0;  // No pressure detected
  
  // Use float to avoid integer division truncation
  float fsrResistance = (5000.0f - fsrVoltage) * 10000.0f / fsrVoltage;
  
  // Calculate conductance in micromhos
  float fsrConductance = 1000000.0f / fsrResistance;

  // Calculate force based on the conductance
  float fsrForce;
  if (fsrConductance <= 1000) {
    fsrForce = fsrConductance / 80.0f;
  } else {
    fsrForce = (fsrConductance - 1000.0f) / 30.0f;
  }

  return (int)fsrForce;  // Cast to int if you need integer return
}

float Ultrasonic::getDistanceCm() const
{
  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);

  long duration = pulseIn(echoPin, HIGH);
  return duration * 0.0343f / 2.0f; 
}

