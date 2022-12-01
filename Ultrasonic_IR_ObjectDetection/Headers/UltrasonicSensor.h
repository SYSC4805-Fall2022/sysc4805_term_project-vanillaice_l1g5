#ifndef ULTRASONIC_H
#define ULTRASONIC_H
#include <HCSR04.h>

class UltrasonicSensor{
   public:
   UltrasonicSensor(int x, int y);
   float getDistCM();
   float getDistMM();
  
   private:
   HCSR04 *us;

};
#endif