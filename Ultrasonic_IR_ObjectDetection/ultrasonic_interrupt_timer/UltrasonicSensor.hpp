#ifndef ULTRASONIC_H
#define ULTRASONIC_H
#include "Arduino.h"

class UltrasonicSensor{
   public:
   UltrasonicSensor(int id);
   void setupTimer();
   float getDistCM();
   int getCaptureFlag();
   void resetCaptureFlag();
   uint32_t getCaptureCountA();
   void setCaptureCountA(uint32_t val);
   float setCaptureCountB(float val);
   double convertCaptureCountA(volatile uint32_t temp);
   int id_code;
};

#endif