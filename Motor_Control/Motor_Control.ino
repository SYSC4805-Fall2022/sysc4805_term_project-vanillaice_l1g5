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

  moveForwardTimed();

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
}