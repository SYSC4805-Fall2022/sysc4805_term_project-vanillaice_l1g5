#include "Motor_Control.h"
#include "Line_sensor.hpp"

// Setup
void setup() {
  Serial.begin(115200);

  //Set up Line sensors
  setup_sensor();
  updateSide_left();
  updateSide_right();

  // Set up Motor
  setupMotor();
}

// Loop

void loop() {

  moveForward();
  delay(forwardDelay);

  stop();
  delay(500);

  turnLeft();
  delay(leftDelay);

  stop();
  delay(3000);

  turnRight();
  delay(rightDelay);

  stop();
  delay(3000);

  // // put your main code here, to run repeatedly:
  // if (getSide_Left() != NONE) {
  //   turnRight();
  //   moveForward(the short one);
  //   turnRight();
  //   side = False;
  //   break;

  // }

  // else if (getSide_Right() != NONE) {
  //   turnLeft();
  //   moveForward(the short one);
  //   turnLeft();
  //   side = True;
  //   break;
  // }
}