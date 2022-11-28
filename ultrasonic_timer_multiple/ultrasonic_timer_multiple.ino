#include "UltrasonicSensor.h"
#include <DueTimer.h>
#define ULTRASONIC_THRESH 11.0000000


//HCSR04 hc(4, 5); //initialisation class HCSR04 (trig pin , echo pin)
UltrasonicSensor US1(4, 5);
UltrasonicSensor US2(6, 7);

volatile boolean US_FLAG_RIGHT; //detection flag to be checked
volatile boolean US_FLAG_LEFT; //detection flag to be checked

void UltrasonicHandler(){
  if (US1.getDistCM() < ULTRASONIC_THRESH){
    US_FLAG_RIGHT = 1;
  }
  if (US2.getDistCM() < ULTRASONIC_THRESH){
    US_FLAG_LEFT = 1;
  }
}

void setup()
{
  Serial.begin(9600);
  Timer.getAvailable().attachInterrupt(UltrasonicHandler).start(60000); // Every 1000 micro sec
}

void loop()
{
    if(US_FLAG_RIGHT){
      US_FLAG_RIGHT = 0;
      printf("Object Detected on right side at %f cm \n", US1.getDistCM());
    }
    if(US_FLAG_LEFT){
      US_FLAG_LEFT = 0;
      printf("Object Detected on left side at %f cm \n", US2.getDistCM());
    }
}