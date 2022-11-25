#include "Line_sensor.hpp"
#include <Arduino.h>

// Global Vars

// Sensor State Vars - Default start at low
volatile int leftLine;
volatile int midLine;
volatile int rightLine;
int changeFlag;

// Timer Vars
uint32_t currTime;
uint32_t prevTime;

// Line State
enum lineSide currSide;

void setup_sensor() {
  // Vars for debouncing
  currTime = 0;
  prevTime = 0;
  currSide = NONE;

  // Sensor State Vars - Default start at low
  leftLine = LOW;
  midLine = LOW;
  rightLine = LOW;
  changeFlag = 0;


  // Set Pins
  pinMode(LineLeft, INPUT_PULLUP);
  pinMode(LineMid, INPUT_PULLUP);
  pinMode(LineRight, INPUT_PULLUP);

  // Attach Interrupts
  attachInterrupt(LineLeft, LeftSensorISR, CHANGE);
  attachInterrupt(LineMid, MidSensorISR, CHANGE);
  attachInterrupt(LineRight, RightSensorISR, CHANGE);
}

/**
 * Interrupt handler for right line sensor
 * 
*/
static void LeftSensorISR() {
  currTime = millis();

  // If left side sensor triggered, flip curr state
  if ((uint32_t)(currTime - prevTime) > DEBOUNCER) {
    prevTime = currTime;
    leftLine = digitalRead(LineLeft);
    updateSide();
  }
}

/**
 * Interrupt handler for middle line sensor
 * 
*/
static void MidSensorISR() {
  currTime = millis();
  // If middle sensor triggered, flip curr state
  if ((uint32_t)(currTime - prevTime) > DEBOUNCER) {
    prevTime = currTime;
    midLine = digitalRead(LineMid);
    updateSide();
  }
}

/**
 * Interrupt handler for right line sensor
 * 
*/
static void RightSensorISR() {
  currTime = millis();

  // If right side sensor triggered, flip curr state
  if ((uint32_t)(currTime - prevTime) > DEBOUNCER) {
    prevTime = currTime;
    rightLine = digitalRead(LineRight);
    updateSide();
  }
}

/**
 * Update side based on where the line is detected. Side is an element of state enum.
 *
 * Return: void
 */
void updateSide() {
  setFlag(1);
  // printf("Midline: %d\t", midLine);
  // printf("Leftline: %d\t", leftLine);
  // printf("Rightline: %d\t", rightLine);
  if ((leftLine == 1) && (midLine == 1) && (rightLine == 1)) {
    currSide = FORWARD;
    return;
  } else if ((leftLine == 0) && (midLine == 1) && (rightLine == 0)) {
    currSide = MIDDLE;
    // printf("\n\nSide: %d\n\n", currSide);
    return;
  } else if ((leftLine == 1) && (midLine == 0) && (rightLine == 0)) {
    currSide = LEFT;
    return;
  } else if ((leftLine == 0) && (midLine == 0) && (rightLine == 1)) {
    currSide = RIGHT;
    return;
  } else if ((leftLine == 0) && (midLine == 0) && (rightLine == 0)) {
    currSide = NONE;
    return;
  }
}

int getFlag() {
  return changeFlag;
}

void setFlag(int flag) {
  changeFlag = flag;
}

const char* getSide() {
  const char* output = "";

  printf("Current Side: %d\n", currSide);
  switch (currSide) {
    case FORWARD:
      output = "Forward";
      break;
    case LEFT:
      output = "Left";
      break;
    case MIDDLE:
      output = "Right";
      break;
    case RIGHT:
      output = "Right";
      break;
    case NONE:
      output = "No Line";
      break;
    default: output = "";
  }

  return output;
}