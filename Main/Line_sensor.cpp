#include "Line_sensor.hpp"
#include "Motor_Control.h"
#include <Arduino.h>

// Global Vars
volatile int changeFlag;

// Sensor State Vars
volatile int left_midLine;
volatile int right_midLine;
volatile int right_rightLine;

// Timer Vars
uint32_t currTime_Left;
uint32_t prevTime_Left;

uint32_t currTime_Right;
uint32_t prevTime_Right;


void setup_sensor() {
  // Vars for debouncing
  currTime_Left = 0;
  prevTime_Left = 0;

  // Sensor State Vars - Default start at low
  left_midLine = LOW;
  changeFlag = 1;

  // Set Pins
  pinMode(Left_LineMid, INPUT);

  // Attach Interrupts
  attachInterrupt(Left_LineMid, MidSensorISR_Left, CHANGE);


  // Right Sensor Setup
  // Vars for debouncing
  currTime_Right = 0;
  prevTime_Right = 0;

  // Sensor State Vars - Default start at low
  right_midLine = LOW;
  right_rightLine = LOW;

  pinMode(Right_LineMid, INPUT);
  pinMode(Right_LineRight, INPUT);

  // Attach Interrupts
  attachInterrupt(Right_LineMid, MidSensorISR_Right, CHANGE);
  attachInterrupt(Right_LineRight, RightSensorISR_Right, CHANGE);
}

/**
 * Interrupt handler for middle line sensor
 *
 */
static void MidSensorISR_Left() {
  currTime_Left = millis();
  // If middle sensor triggered, flip curr state
  if (((uint32_t)(currTime_Left - prevTime_Left) > DEBOUNCER) && !changeFlag) {
    prevTime_Left = currTime_Left;
    left_midLine = analogRead(Left_LineMid);
    changeFlag = 1;
  }
}

/**
 * Interrupt handler for middle line sensor
 *
 */
static void MidSensorISR_Right() {
  currTime_Right = millis();
  // If middle sensor triggered, flip curr state
  if ((uint32_t)(currTime_Right - prevTime_Right) > DEBOUNCER && !changeFlag) {
    prevTime_Right = currTime_Right;
    right_midLine = analogRead(Right_LineMid);
    changeFlag = 1;
  }
}

/**
 * Interrupt handler for right line sensor
 *
 */
static void RightSensorISR_Right() {
  currTime_Right = millis();
  // If right side sensor triggered, flip curr state
  if ((uint32_t)(currTime_Right - prevTime_Right) > DEBOUNCER && !changeFlag) {
    prevTime_Right = currTime_Right;
    right_rightLine = analogRead(Right_LineRight);
    changeFlag = 1;
  }
}

void readLine() {
  right_midLine = analogRead(Right_LineMid);
  left_midLine = analogRead(Left_LineMid);
  right_rightLine = analogRead(Right_LineRight);
}

int getLineFlag() {
  return changeFlag;
}

void setLineFlag(int flag) {
  changeFlag = flag;
}

int getSide() {
  return max(max(right_midLine, right_rightLine), left_midLine);
}

void resetSensorVals() {
  // Sensor State Vars
  left_midLine = 0;
  right_midLine = 0;
  right_rightLine = 0;
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