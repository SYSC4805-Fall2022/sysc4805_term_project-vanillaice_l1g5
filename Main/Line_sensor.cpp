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

/**
 * Sensor setup function 
 * 
 * Set initial values, set defaults, attach interrupts, 
 * and define pin operations
 * 
*/
void setup_sensor() {

  // Left ssensor setup

  // Vars for debouncing
  currTime_Left = 0;
  prevTime_Left = 0;

  // Sensor State Vars - Default start at low
  left_midLine = LOW;
  changeFlag = 1;

  // Set Pins
  pinMode(Left_LineMid, INPUT);

  // Attach Interrupts to triggered pins on left side
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

  // Attach Interrupts to triggered pins on right side
  attachInterrupt(Right_LineMid, MidSensorISR_Right, CHANGE);
  attachInterrupt(Right_LineRight, RightSensorISR_Right, CHANGE);
}

/**
 * Interrupt handler for middle line sensor on the left side
 * 
 * If the line sensor triggers an interrupt, if at least 'debounce' time has passed,
 * the value read is stored, and a flag is set to inform the main loop of an update
 *
 */
static void MidSensorISR_Left() {
  // If middle side sensor triggered store read value

  // Check if enough time has passed and main loop has read last update
  currTime_Left = millis();
  if (((uint32_t)(currTime_Left - prevTime_Left) > DEBOUNCER) && !changeFlag) {
    prevTime_Left = currTime_Left;
    left_midLine = analogRead(Left_LineMid);
    changeFlag = 1;
  }
}

/**
 * Interrupt handler for middle line sensor on the right side
 * 
 * If the sensor triggers an interrupt, if at least 'debounce' time has passed,
 * the value read is stored, and a flag is set to inform the main loop of an update
 *
 */
static void MidSensorISR_Right() {
  // If middle sensor triggered, store read value

  // Check if enough time has passed and main loop has read last update
  currTime_Right = millis();
  if ((uint32_t)(currTime_Right - prevTime_Right) > DEBOUNCER && !changeFlag) {
    prevTime_Right = currTime_Right;
    right_midLine = analogRead(Right_LineMid);
    changeFlag = 1;
  }
}

/**
 * Interrupt handler for right line sensor on the right side 
 * 
 * If the line sensor triggers an interrupt, if at least 'debounce' time has passed,
 * the value read is stored, and a flag is set to inform the main loop of an update
 *
 */
static void RightSensorISR_Right() {
  // If right side sensor triggered store read value

  // Check if enough time has passed and main loop has read last update
  currTime_Right = millis();
  if ((uint32_t)(currTime_Right - prevTime_Right) > DEBOUNCER && !changeFlag) {
    prevTime_Right = currTime_Right;
    right_rightLine = analogRead(Right_LineRight);
    changeFlag = 1;
  }
}

/**
 * Used to read the line to get the most up to date sensor values. 
 * 
 * Useful when interrupt has not gone off, but a reading is required (after a correction perhaps)
 */ 
void readLine() {
  right_midLine = analogRead(Right_LineMid);
  left_midLine = analogRead(Left_LineMid);
  right_rightLine = analogRead(Right_LineRight);
}

/**
 * Return changeFlag
 * 
 * Used to poll for updates, helps main loop check for lines
*/
int getLineFlag() {
  return changeFlag;
}

/**
 * Used to set/reset the change flag from outside this module
 * 
 * @param flag Flag to be set. Should be 1 or 0 exclusively
*/
void setLineFlag(int flag) {
  changeFlag = flag;
}

/**
 * Return the highest line sensor reading, used to determine if a line was detected or not
*/
int getSide() {
  return max(max(right_midLine, right_rightLine), left_midLine);
}

/**
 * Set sensor variables to 0, used when main loop has read change
 *  but line sensor does not generate an interrupt to clear old values
*/
void resetSensorVals() {
  // Sensor State Vars set to 0
  left_midLine = 0;
  right_midLine = 0;
  right_rightLine = 0;
}

/**
 * DEPRECATED
 * 
 * Used to convert side enum to text for debugging and printing to console
 * 
*/
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