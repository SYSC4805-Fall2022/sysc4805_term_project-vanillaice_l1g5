#include "Motor_Control.h"
#include "Line_sensor.hpp"
boolean turnSide = false;

// Setup
void setup() {
  Serial.begin(115200);

  // Set up Line sensors
  setup_sensor();
  updateSide_left();
  updateSide_right();

  // Set up Motor
  setupMotor();
}

// Loop
// void loop(){
//   turnRight();
//   delay(500);

//   stop();
//   delay(500);
// }


void loop() {

  // if (getFlag_Left())
  //   printf("Flag left\n");

  // if (getFlag_Right())
  // printf("Flag right\n");

  if (getFlag_Left() || getFlag_Right()) {
    printf("Left Sensor: ");
    printf(currSideText(getSide_Left()));
    printf("\t Right Sensor: ");
    printf(currSideText(getSide_Right()));
    printf("\n");

    // Reset change flags
    setFlag_Left(0);
    setFlag_Right(0);

    if (getSide_Right() != NONE && getSide_Left() != NONE) {
      printf("Line detected! Turning!\n");
      if (turnSide) {
        printf("Turning right\n");
        turnRight();
        if (getSide_Right() != NONE && getSide_Left() != NONE) {  //getSide_Left() == NONE && getSide_Right() == NONE
          printf("oop more lines \n");
          turnRight();
        } else {
          // Check for obstacle
          moveForwardTimed();
          printf("Completed moveForwardTimed \n");
          turnRight();

          turnSide = false;
        }
      } else {
        // printf("Turning left\n");
        turnLeft();
        if (!(getSide_Right() != NONE && getSide_Left() != NONE)) {  //== NONE
          // check for obstacle
          moveForwardTimed();
          // printf("Completed moveForwardTimed \n");
          turnLeft();
          turnSide = true;
        } else {
          // printf("oop still more lines\n");
          turnLeft();
        }
      }
    }
  } else {
    // check for obstacle
    moveForward();
    // stop();  // For testing reasons only
  }
  delay(300);
}

char *currSideText(lineSide side) {
  char *output = "";

  switch (side) {
    case NONE:
      output = "None";
      break;
    case LEFT:
      output = "Left";
      break;
    case MIDDLE:
      output = "Mid";
      break;
    case RIGHT:
      output = "Right";
      break;
    case FORWARD:
      output = "Forward";
      break;
  }

  return output;
}