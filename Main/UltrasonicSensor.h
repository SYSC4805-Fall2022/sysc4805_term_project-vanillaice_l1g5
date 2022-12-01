#ifndef ULTRASONIC_H
#define ULTRASONIC_H
#include <HCSR04.h> // Add as reference to report

// Constants
#define ULTRASONIC_THRESH 20.00

class UltrasonicSensor{
   public:
   UltrasonicSensor(int x, int y);
   float getDistCM();
   float getDistMM();
  
   private:
   HCSR04 *us;

};
#endif