#include "UltrasonicSensor.hpp"
#define ULTRASONIC_BOUND 11.000000

volatile boolean US_FLAG_1; //detection flag to be checked
volatile double US_OBJECT_DIST; //distance of object detected
UltrasonicSensor US1(1);

void watchdogSetup(){}; //setup watchdog

void setup()
{
  watchdogEnable(2000); //enable watchdog timer to check in 2 sec intervals
  US1.setupTimer(); //starting ultrasonic sensor  
}

void loop()
{
  watchdogReset();
  if (US_FLAG_1) //checking if flag is raised
  {
    US_FLAG_1 = 0;// Reset the flag,
    printf("Object Detected at \r %f cm \n", US1.getDistCM());
  }
  
}


void TC1_Handler()
{  
  printf("In the timer handler \n");
  uint32_t status = TC0->TC_CHANNEL[1].TC_SR; // Read status register, Clear status
  if (status & TC_SR_LDRAS)
  {                                           // If ISR is fired by LDRAS then ....

    US1.setCaptureCountA(TC0->TC_CHANNEL[1].TC_RA); // read TC_RA
    US_OBJECT_DIST = US1.convertCaptureCountA(US1.getCaptureCountA()); //converting to CM
    US1.setCaptureCountB(US_OBJECT_DIST);
    
    if (US_OBJECT_DIST < ULTRASONIC_BOUND){ //checking if object detected at less than 11 cm (threshold value)
       printf("Object detected at less than 11 cm \n");
       US_FLAG_1 = 1;// Inform the main loop of an update.
    }
  }
  while(true){}; //while true used to show watchdog timer does indeed reset the loop after 2 seconds
}
