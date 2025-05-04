#include "PixyCamera.h"
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

  return (int)fsrForce;
}


bool Utils::matchingDistance(const double read1, const double read2)
{
  static uint8_t diff = 5;
  return abs(read1 - read2) >= diff;
}

void Utils::testPixyUltrasonicError()
{
  double ultrasonicDist, pixyDist;
  while (true)
  {
    ultrasonicDist = frontUltrasonic.getDistanceFromRobot();

    pixy.ccc.getBlocks();
    if (pixy.ccc.numBlocks)
    {
      pixyDist = PixyCamera::getDistanceFromRobot(&pixy.ccc.blocks[0]);
      Serial.print("front ultrasonic shows: ");
      Serial.print(ultrasonicDist);
      Serial.print(", pixy shows: ");
      Serial.print(pixyDist);
      Serial.print(", error: ");
      Serial.println(ultrasonicDist - pixyDist);
      delay(1000);
    } else {
      Serial.print("front ultrasonic shows: ");
      Serial.print(ultrasonicDist);
      Serial.println(", pixy did not find any blocks.");
      delay(1000);
      continue;
    }
  }

}

double Ultrasonic::getDistanceFromSensor() const
{
  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);

  long duration = pulseIn(echoPin, HIGH);
  return duration * SPEED_OF_SOUND_CM_PER_US / 2.0; 
}

double Ultrasonic::getDistanceFromRobot() const
{
  return getDistanceFromSensor() - ULTRASONIC_DIST_FROM_ROBOT;
}

void Ultrasonic::setup() const
{
  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);
}

void Ultrasonic::test() const
{
  while (true)
  {
    double dist = getDistanceFromRobot();
    Serial.print("Ultrasonic sensor shows: ");
    Serial.println(dist);
    delay(100);
  }
}
