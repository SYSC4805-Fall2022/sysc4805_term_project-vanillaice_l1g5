#include "UltrasonicSensor.h"
#include <DueTimer.h>
#define ULTRASONIC_THRESH 15.0000000

//initialisation class HCSR04 (trig pin , echo pin)
UltrasonicSensor US1(4, 5);
UltrasonicSensor US2(6, 7);

volatile boolean US_FLAG_RIGHT; //detection flag to be checked
volatile boolean US_FLAG_LEFT; //detection flag to be checked
volatile float US_DIST_RIGHT;
volatile float US_DIST_LEFT;

void UltrasonicHandler(){
  US_DIST_RIGHT = US1.getDistCM();
  if (US_DIST_RIGHT < ULTRASONIC_THRESH){
    US_FLAG_RIGHT = 1;
  }
  US_DIST_LEFT = US2.getDistCM();
  if (US_DIST_LEFT < ULTRASONIC_THRESH){
    US_FLAG_LEFT = 1;
  }
}

void setup()
{
  Serial.begin(9600);
  Timer.getAvailable().attachInterrupt(UltrasonicHandler).start(60000); // Every 60 ms
}

void loop()
{
    if(US_FLAG_RIGHT){
      US_FLAG_RIGHT = 0;
      printf("Object Detected on right side at %f cm \n", US_DIST_RIGHT);
    }
    if(US_FLAG_LEFT){
      US_FLAG_LEFT = 0;
      printf("Object Detected on left side at %f cm \n", US_DIST_LEFT);
    }
}