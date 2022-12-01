#include "UltrasonicSensor.h"
#include "Motor_Control.h"
#include <DueTimer.h>
#define ULTRASONIC_THRESH 15.0000000

//initialisation class HCSR04 (trig pin , echo pin)
UltrasonicSensor US1(4, 5);
UltrasonicSensor US2(6, 7);

volatile boolean US_FLAG_RIGHT;  //detection flag to be checked
volatile boolean US_FLAG_LEFT;   //detection flag to be checked
volatile float US_DIST_RIGHT;
volatile float US_DIST_LEFT;
uint32_t turnTime;
volatile boolean turnCheck = true;


void UltrasonicHandler() {
  US_DIST_RIGHT = US1.getDistCM();

  if (US_DIST_RIGHT < ULTRASONIC_THRESH && US_DIST_RIGHT > 0.0) {
    US_FLAG_RIGHT = 1;
    printf("object at %f on right \n", US_DIST_RIGHT);
  }
  US_DIST_LEFT = US2.getDistCM();

  if (US_DIST_LEFT < ULTRASONIC_THRESH && US_DIST_LEFT > 0.0) {
    US_FLAG_LEFT = 1;
    printf("object at %f on left \n", US_DIST_LEFT);
  }
}

void setup() {
  // put your setup code here, to run once:
  Serial.begin(115200);                                                  // Serial.begin(9600);
  Timer.getAvailable().attachInterrupt(UltrasonicHandler).start(60000);  // Every 60 ms
  // Set up Motor
  setupMotor();
}

void loop() {
  // if (){

  // }
  while (true) {
    if (!US_FLAG_RIGHT && !US_FLAG_LEFT) {  //no object, go forward
      moveForward();
    } else if (US_FLAG_RIGHT) {  //object on right
      printf("Seeing object on right\n");
      US_FLAG_RIGHT = 0;
      turnLeft();          //turn left to avoid
      moveForwardTimed();  //move forward a bit
      turnRight();         //turn right to get back on track
      if (US_FLAG_RIGHT) {
        US_FLAG_RIGHT = 0;
        break;
      }
      moveForward();
      turnTime = millis();
      turnCheck = true;
      while (turnCheck) {
        printf("Doing a turncheck \n");
        if ((millis() - turnTime) > 500) {
          turnRight();
          if (!US_FLAG_RIGHT && !US_FLAG_LEFT) {
            turnCheck = false;
            moveForwardTimed();
            turnLeft();
            moveForward();
            break;
          } else {
            turnLeft();
            turnTime = millis();
            moveForward();
          }
        }
      }

    } else if (US_FLAG_LEFT) {  //object on left
      printf("Seeing object on left\n");
      US_FLAG_LEFT = 0;
      turnRight();
      moveForwardTimed();
      turnLeft();
      if (US_FLAG_LEFT) {
        US_FLAG_LEFT = 0;
        break;
      }
      moveForward();
      turnTime = millis();
      turnCheck = true;
      while (turnCheck) {
        printf("Doing a turncheck \n");
        if ((millis() - turnTime) > 500) {
          turnLeft();
          if (!US_FLAG_RIGHT && !US_FLAG_LEFT) {
            turnCheck = false;
            moveForwardTimed();
            turnRight();
            moveForward();
            break;
          } else {
            turnRight();
            turnTime = millis();
            moveForward();
          }
        }
      }
    }
    //delay(300);
  }
}


// void objectDetected(boolean flagRight, boolean flagLeft) {
// }
