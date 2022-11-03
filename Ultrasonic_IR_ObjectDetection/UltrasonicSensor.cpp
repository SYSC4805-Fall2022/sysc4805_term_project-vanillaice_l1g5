

//#include <HCSR04.h>
#include "Headers/UltrasonicSensor.h"

//constructor with trigger pin and echo pin
UltrasonicSensor::UltrasonicSensor(int x, int y){
   us = new HCSR04(x, y);
}

//return distance in cm
float UltrasonicSensor::getDistCM()
{
  return us->dist();
}

//return distance in mm
float UltrasonicSensor::getDistMM()
{
  return us->dist()*10;
}
