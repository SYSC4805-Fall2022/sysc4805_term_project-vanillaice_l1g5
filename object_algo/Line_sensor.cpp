#include "Line_sensor.hpp"
#include "Motor_Control.h"
#include <Arduino.h>

// Global Vars

// Sensor State Vars - Default start at low
volatile int left_leftLine;
volatile int left_midLine;
volatile int left_rightLine;
int changeFlag_Left;

volatile int right_leftLine;
volatile int right_midLine;
volatile int right_rightLine;
int changeFlag_Right;

// Timer Vars
uint32_t currTime_Left;
uint32_t prevTime_Left;

uint32_t currTime_Right;
uint32_t prevTime_Right;

// Line State
enum lineSide currSide_left;
enum lineSide currSide_right;

void setup_sensor()
{
  // Vars for debouncing
  currTime_Left = 0;
  prevTime_Left = 0;
  currSide_left = NONE;

  // Sensor State Vars - Default start at low
  left_leftLine = LOW;
  left_midLine = LOW;
  left_rightLine = LOW;
  changeFlag_Left = 0;

  // Set Pins
  pinMode(Left_LineLeft, INPUT);
  pinMode(Left_LineMid, INPUT_PULLUP);
  pinMode(Left_LineRight, INPUT_PULLUP);

  // Attach Interrupts
  attachInterrupt(Left_LineLeft, LeftSensorISR_Left, CHANGE);
  attachInterrupt(Left_LineMid, MidSensorISR_Left, CHANGE);
  attachInterrupt(Left_LineRight, RightSensorISR_Left, CHANGE);


  // Right Sensor Setup
  // Vars for debouncing
  currTime_Right = 0;
  prevTime_Right = 0;
  currSide_right = NONE;

  // Sensor State Vars - Default start at low
  right_leftLine = LOW;
  right_midLine = LOW;
  right_rightLine = LOW;
  changeFlag_Right = 0;

  pinMode(Right_LineLeft, INPUT);
  pinMode(Right_LineMid, INPUT_PULLUP);
  pinMode(Right_LineRight, INPUT_PULLUP);

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
  if ((uint32_t)(currTime_Left - prevTime_Left) > DEBOUNCER && ~changeFlag_Left)
  {
    prevTime_Left = currTime_Left;
    left_leftLine = digitalRead(Left_LineLeft);
    printf("LeftSensorISR_Left\n");
    updateSide_left();
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
  if (((uint32_t)(currTime_Left - prevTime_Left) > DEBOUNCER) && ~changeFlag_Left)
  {
    prevTime_Left = currTime_Left;
    left_midLine = digitalRead(Left_LineMid);
    printf("MidSensorISR_Left\n");
    updateSide_left();
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
  if ((uint32_t)(currTime_Left - prevTime_Left) > DEBOUNCER && ~changeFlag_Left)
  {
    prevTime_Left = currTime_Left;
    left_rightLine = digitalRead(Left_LineRight);
    printf("RightSensorISR_Left\n");
    updateSide_left();
  }
}

int getFlag_Left()
{
  return changeFlag_Left;
}

void setFlag_Left(int flag)
{
  changeFlag_Left = flag;
}

lineSide getSide_Left()
{
  return currSide_left;
}

/**
 * Update side based on where the line is detected. Side is an element of state enum.
 *
 * Return: void
 */
void updateSide_left()
{
  setFlag_Left(1);
  if ((left_leftLine == 1) && (left_midLine == 1) && (left_rightLine == 1))
  {
    currSide_left = FORWARD;
    return;
  }
  else if (left_midLine == 1)
  {
    currSide_left = MIDDLE;
    return;
  }
  else if (left_leftLine == 1)
  {
    currSide_left = LEFT;
    return;
  }
  else if (left_rightLine == 1)
  {
    currSide_left = RIGHT;
    return;
  }
  else
  {
    currSide_left = NONE;
    return;
  }
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
  if ((uint32_t)(currTime_Right - prevTime_Right) > DEBOUNCER && ~changeFlag_Right)
  {
    prevTime_Right = currTime_Right;
    right_leftLine = digitalRead(Right_LineLeft);
    printf("LeftSensorISR_Right\n");
    updateSide_right();
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
  if ((uint32_t)(currTime_Right - prevTime_Right) > DEBOUNCER && ~changeFlag_Right)
  { 
    prevTime_Right = currTime_Right;
    right_midLine = digitalRead(Right_LineMid);
    updateSide_right();
    printf("MidSensorISR_Right\n");
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
  if ((uint32_t)(currTime_Right - prevTime_Right) > DEBOUNCER && ~changeFlag_Right)
  {
    prevTime_Right = currTime_Right;
    right_rightLine = digitalRead(Right_LineRight);
    printf("RightSensorISR_Right()\n");
    updateSide_right();
  }
}

/**
 * Update side based on where the line is detected. Side is an element of state enum.
 *
 * Return: void
 */
void updateSide_right()
{
  setFlag_Right(1);
  if ((right_leftLine == 1) && (right_midLine == 1) && (right_rightLine == 1))
  {
    currSide_right = FORWARD;
    return;
  }
  else if (right_midLine == 1)
  {
    currSide_right = MIDDLE;
    return;
  }
  else if (right_leftLine == 1)
  {
    currSide_right = LEFT;
    return;
  }
  else if (right_rightLine == 1)
  {
    currSide_right = RIGHT;
    return;
  }
  else 
  {
    currSide_right = NONE;
    return;
  }
}

int getFlag_Right()
{
  return changeFlag_Right;
}

void setFlag_Right(int flag)
{
  changeFlag_Right = flag;
}

lineSide getSide_Right()
{
  return currSide_right;
}