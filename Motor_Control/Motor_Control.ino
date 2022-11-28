#include "Motor_Control.h"
#include "Line_sensor.hpp"
boolean side = true;

// Setup
void setup()
{
  Serial.begin(115200);

  // Set up Line sensors
  setup_sensor();
  updateSide_left();
  updateSide_right();

  // Set up Motor
  setupMotor();
}

// Loop

void loop()
{

  if (getFlag_Left() || getFlag_Right())
  {
    printf("Left Sensor: ");
    printf(currSideText(getSide_Left()));
    printf("\t Right Sensor: ");
    printf(currSideText(getSide_Right()));
    printf("\n");

    // Reset change flags
    setFlag_Left(0);
    setFlag_Right(0);

    if (getSide_Right() != NONE && getSide_Left() != NONE)
    {
      printf("Line detected! Turning!");
      if (side)
      {
        printf("Turning right");
        turnRight();
        if ( getSide_Left() == NONE && getSide_Right() == NONE)
        {
          // Check for obstacle
          moveForwardTimed();
          turnRight();

          side = false;
        }
        else
        {
          printf("oop more lines");
          turnRight();
        }
      }
      else
      {
        printf("Turning left");
        turnLeft();
        if ( getSide_Left() == NONE && getSide_Right() == NONE)
        {
          // check for obstacle
          moveForwardTimed();
          turnLeft();
          side = true;
        }
        else
        {
          printf("oop still more lines");
          turnLeft();
        }
      }
    }
  }
  else
  {
    // check for obstacle
    //  moveForward();
    stop(); // For testing reasons only
  }
  delay(300);
}

char *currSideText(lineSide side)
{
  char *output = "";

  switch (side)
  {
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