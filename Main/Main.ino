#include "Motor_Control.h"
#include "Line_sensor.hpp"
#include "UltrasonicSensor.h"
#include <DueTimer.h>  // Add as reference to report

// Globals
boolean turnSide = false;
volatile boolean US_FLAG_RIGHT;  // detection flag to be checked
volatile boolean US_FLAG_LEFT;   // detection flag to be checked
volatile float US_DIST_RIGHT;    //right ultrasonic value
volatile float US_DIST_LEFT;     //left ultrasoncic
uint32_t turnTime;
volatile boolean turnCheck = true;

// Class instantiations
// Class HCSR04 - Ultrasonic Sensor (trig pin , echo pin)
UltrasonicSensor US1(4, 5);  //left ultrasonic sensor
UltrasonicSensor US2(6, 7);  //right ultrasonic sensor

// Setup
void setup() {
  Serial.begin(115200);

  // Set up ultrasonic sensors
  Timer.getAvailable().attachInterrupt(UltrasonicHandler).start(60000);  // Every 60 ms, check ultrasonic sensors

  // Set up Line sensors
  setup_sensor();

  // Set up Motor
  setupMotor();
}

void loop() {
  if (getLineFlag()) {  // Check if line detected
    // Reset change flags
    setLineFlag(0);
    avoidLine();  // Perform line avoidance subroutine
    nonBlockWait(150);
  } else {
    moveForward();  // Line not detected, move forward
  }
  // Avoid Object
  if (US_FLAG_RIGHT || US_FLAG_LEFT) {
    avoidObject();  // Perform object avoidance subroutine
    nonBlockWait(150);
  }
  // Nothing found, move forward
  else {
    moveForward();
  }
}

/*
* Line avoidance subroutine, will turn right if last time turned left and vice versa
* Intially will turn right, then flip bool value for turnSide
*/
void avoidLine() {
  // Check if line is still there
  if (getSide() > LINE_THRESHOLD) {

    // Stop if line found
    stop();
    nonBlockWait(150);
    moveBackwardTimed();  // Move backward to ensure robot stays within bounds

    if (turnSide) {
      // Turn right, move forward for set distance and turn right again
      turnRight();
      stop();
      nonBlockWait(150);

      moveForwardTimed();
      stop();
      nonBlockWait(150);

      turnRight();
      stop();
      nonBlockWait(150);

      resetSensorVals();

      turnSide = !turnSide;

      return;  //Return to main loop
    } else {
      // Turn right, move forward for set distance and turn right again
      turnLeft();
      stop();
      nonBlockWait(150);

      moveForwardTimed();
      stop();
      nonBlockWait(150);

      turnLeft();
      stop();
      nonBlockWait(150);

      resetSensorVals();

      turnSide = !turnSide;  // Flip bool value to turn different side next function call
      return;                //Return to main loop
    }
  } else {
    moveForward();  // Handled line avoidance, move forward
  }
}

/*
* Nonblocking wait, used for allowing delays that can be interrupted
*/
void nonBlockWait(uint32_t delay) {
  // Timing vars - local
  unsigned long start = millis();
  unsigned long end = start;

  // Turn until forward move time has passed
  while (end - start < delay) {
    end = millis();
  }
}

/*
* Called by timer everything 60 ms, updates distances of objects seen by Ultrasonic Sensors
* Sets flag if distance is less than defined threshold value
*/
void UltrasonicHandler() {
  US_DIST_RIGHT = US2.getDistCM();  // Read from right Ultrasonic Sensor

  // Check if distance less than threshold, greater than 0, and flag has been reset
  if (US_DIST_RIGHT < ULTRASONIC_THRESH && US_DIST_RIGHT > 0.0 && !US_FLAG_RIGHT) {
    US_FLAG_RIGHT = 1;
  }
  US_DIST_LEFT = US1.getDistCM();  //Read from left Ultrasonic Sensor

  // Check if distance less than threshold, greater than 0, and flag has been reset
  if (US_DIST_LEFT < ULTRASONIC_THRESH && US_DIST_LEFT > 0.0 && !US_FLAG_LEFT) {
    US_FLAG_LEFT = 1;
  }
}

/*
* Object avoidance subroutine, called by main loop
* If object seen on right, turn left, move forward for a set distance, reset flag, return to main loop
* If object seen on left, turn right, move forward for a set distance, reset flag, return to main loop
*/
void avoidObject() {

  // object on right
  if (US_FLAG_RIGHT) {
    stop();
    nonBlockWait(150);

    turnLeft();  // turn left to avoid
    stop();
    nonBlockWait(150);

    moveForwardTimed();
    US_FLAG_RIGHT = 0;

    return;
  } else if (US_FLAG_LEFT) {  // object on left
    turnRight();
    stop();
    nonBlockWait(150);
    moveForwardTimed();
    US_FLAG_LEFT = 0;

    return;
  }
}