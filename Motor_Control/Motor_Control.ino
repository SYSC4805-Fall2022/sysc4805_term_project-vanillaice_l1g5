#include "Motor_Control.h"
#include "Line_sensor.hpp"
boolean side = true;

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

  // moveForwardTimed();

  // stop();
  // delay(500);

  // turnLeft();
  // delay(leftDelay);

  // stop();
  // delay(3000);

  // turnRight();
  // delay(rightDelay);

  // stop();
  // delay(3000);

  //new code
  if (getSide_Left == FORWARD && getSide_Right == FORWARD){
    if (side){
      turnRight(); 
      if ((getSide_Left != FORWARD) && (getSide_Right != FORWARD)){
        //check for obstacle
        moveForwardTimed();
        turnRight();
        side = false;
        break;
      }
      else {
        turnRight();
        break;
      }
    }
    else {
      turnLeft();
      if (getSide_Left != FORWARD && getSide_Right != FORWARD){
        //check for obstacle
        moveForwardTimed(); 
        turnLeft();
        side = true;
        break;
      }
      else{
        turnLeft(); 
        break;
      }
    }
  }
  else {
    //check for obstacle 
    moveForward();
  }

}