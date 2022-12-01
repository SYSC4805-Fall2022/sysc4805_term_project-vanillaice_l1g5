#include "Line_sensor.hpp"
#include "Motor_Control.h"
#include <Arduino.h>

// Global Vars

// Sensor State Vars - Default start at low
volatile int left_leftLine;
volatile int left_midLine;
volatile int left_rightLine;
volatile int changeFlag;

volatile int right_leftLine;
volatile int right_midLine;
volatile int right_rightLine;

// Timer Vars
uint32_t currTime_Left;
uint32_t prevTime_Left;

uint32_t currTime_Right;
uint32_t prevTime_Right;


void setup_sensor()
{
  // Vars for debouncing
  currTime_Left = 0;
  prevTime_Left = 0;

  // Sensor State Vars - Default start at low
  left_leftLine = LOW;
  left_midLine = LOW;
  left_rightLine = LOW;
  changeFlag = 1;

  // Set Pins
  pinMode(Left_LineLeft, INPUT);
  pinMode(Left_LineMid, INPUT);
  pinMode(Left_LineRight, INPUT);

  // Attach Interrupts
  attachInterrupt(Left_LineLeft, LeftSensorISR_Left, CHANGE);
  attachInterrupt(Left_LineMid, MidSensorISR_Left, CHANGE);
  attachInterrupt(Left_LineRight, RightSensorISR_Left, CHANGE);


  // Right Sensor Setup
  // Vars for debouncing
  currTime_Right = 0;
  prevTime_Right = 0;

  // Sensor State Vars - Default start at low
  right_leftLine = LOW;
  right_midLine = LOW;
  right_rightLine = LOW;

  pinMode(Right_LineLeft, INPUT);
  pinMode(Right_LineMid, INPUT);
  pinMode(Right_LineRight, INPUT);

  // Attach Interrupts
  attachInterrupt(Right_LineLeft, LeftSensorISR_Right, CHANGE);
  attachInterrupt(Right_LineMid, MidSensorISR_Right, CHANGE);
  attachInterrupt(Right_LineRight, RightSensorISR_Right, CHANGE);
}

/**
 * Interrupt handler for right line sensor
 *
 */
static void LeftSensorISR_Left()
{
  currTime_Left = millis();

  // If left side sensor triggered, flip curr state
  if ((uint32_t)(currTime_Left - prevTime_Left) > DEBOUNCER && !changeFlag)
  {
    prevTime_Left = currTime_Left;
    left_leftLine = analogRead(Left_LineLeft);
    printf("Left Left val %d\n", left_leftLine);
    changeFlag = 1;
  }
}

/**
 * Interrupt handler for middle line sensor
 *
 */
static void MidSensorISR_Left()
{
  currTime_Left = millis();
  // If middle sensor triggered, flip curr state
  if (((uint32_t)(currTime_Left - prevTime_Left) > DEBOUNCER) && !changeFlag)
  {
    prevTime_Left = currTime_Left;
    left_midLine = analogRead(Left_LineMid);
    printf("Left Mid val %d\n", left_midLine);
    changeFlag = 1;
  }
}

/**
 * Interrupt handler for right line sensor
 *
 */
static void RightSensorISR_Left()
{
  currTime_Left = millis();

  // If right side sensor triggered, flip curr state
  if ((uint32_t)(currTime_Left - prevTime_Left) > DEBOUNCER && !changeFlag)
  {
    prevTime_Left = currTime_Left;
    left_rightLine = analogRead(Left_LineRight);
    printf("Left Right val %d\n", left_rightLine);
    changeFlag = 1;
  }
}

int getSide_Left(){
  return left_midLine;
}



// Right Side Line Sensor

/**
 * Interrupt handler for right line sensor
 *
 */
static void LeftSensorISR_Right()
{
  currTime_Right = millis();
  // If left side sensor triggered, flip curr state
  if ((uint32_t)(currTime_Right - prevTime_Right) > DEBOUNCER && !changeFlag)
  {
    prevTime_Right = currTime_Right;
    right_leftLine = analogRead(Right_LineLeft);
    printf("Right Left val %d\n", right_leftLine);
    changeFlag = 1;
  }
}

/**
 * Interrupt handler for middle line sensor
 *
 */
static void MidSensorISR_Right()
{
  currTime_Right = millis();
  // If middle sensor triggered, flip curr state
  if ((uint32_t)(currTime_Right - prevTime_Right) > DEBOUNCER && !changeFlag)
  { 
    prevTime_Right = currTime_Right;
    right_midLine = analogRead(Right_LineMid);
    changeFlag = 1;
    printf("Right Mid val %d\n", right_midLine);
  }
}

/**
 * Interrupt handler for right line sensor
 *
 */
static void RightSensorISR_Right()
{
  currTime_Right = millis();
  // If right side sensor triggered, flip curr state
  if ((uint32_t)(currTime_Right - prevTime_Right) > DEBOUNCER && !changeFlag)
  {
    prevTime_Right = currTime_Right;
    right_rightLine = analogRead(Right_LineRight);
    printf("Right Right val %d\n", right_rightLine);
    changeFlag = 1;
  }
}

void readLine(){
  right_midLine = analogRead(Right_LineMid);
  left_midLine = analogRead(Left_LineMid);
  right_rightLine = analogRead(Right_LineRight);
}

int getLineFlag()
{
  return changeFlag;
}

void setLineFlag(int flag)
{
  changeFlag = flag;
}

int getSide_Right(){
  return max(right_midLine, right_rightLine);
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