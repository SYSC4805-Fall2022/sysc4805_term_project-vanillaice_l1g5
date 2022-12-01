#include "Motor_Control.h"
#include "Line_sensor.hpp"
#include "UltrasonicSensor.h"
#include <DueTimer.h>  // Add as reference to report

// Globals
boolean turnSide = false;
volatile boolean US_FLAG_RIGHT;  // detection flag to be checked
volatile boolean US_FLAG_LEFT;   // detection flag to be checked
volatile float US_DIST_RIGHT;
volatile float US_DIST_LEFT;
uint32_t turnTime;
volatile boolean turnCheck = true;

// Class instantiations
// Class HCSR04 - Ultrasonic Sensor (trig pin , echo pin)
UltrasonicSensor US1(4, 5);
UltrasonicSensor US2(6, 7);

// Setup
void setup() {
  Serial.begin(115200);

  // Set up ultrasonic sensors
  Timer.getAvailable().attachInterrupt(UltrasonicHandler).start(60000); // Every 60 ms

  // Set up Line sensors
  setup_sensor();

  // Set up Motor
  setupMotor();
}

void loop() {
  if (getLineFlag()) {
    // Reset change flags
    setLineFlag(0);
    avoidLine();
    nonBlockWait(150);
  }
  else {
    moveForward();
  }
  // Avoid Object
  if (US_FLAG_RIGHT || US_FLAG_LEFT)
  {
    avoidObject();
    nonBlockWait(150);
  }
  // Nothing found, move forward
  else {
    moveForward();
  }
}

void avoidLine() {
  // Check if line is still there
  if (getSide() > LINE_THRESHOLD) {

    // Stop if line found
    stop();
    nonBlockWait(150);
    moveBackwardTimed();

    if (turnSide) {
      // Turn right, move forward and turn right again
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

      return;
    } else {
      // Turn right, move forward and turn right again
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

      turnSide = !turnSide;
      return;
    }
  } else {
    moveForward();
  }
}

void nonBlockWait(uint32_t delay) {
  // Timing vars - local
  unsigned long start = millis();
  unsigned long end = start;

  // Turn until forward move time has passed
  while (end - start < delay) {
    end = millis();
  }
}

void UltrasonicHandler() {
  US_DIST_RIGHT = US2.getDistCM();

  if (US_DIST_RIGHT < ULTRASONIC_THRESH && US_DIST_RIGHT > 0.0 && !US_FLAG_RIGHT) {
    US_FLAG_RIGHT = 1;
  }
  US_DIST_LEFT = US1.getDistCM();

  if (US_DIST_LEFT < ULTRASONIC_THRESH && US_DIST_LEFT > 0.0 && !US_FLAG_LEFT) {
    US_FLAG_LEFT = 1;
  }
}

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