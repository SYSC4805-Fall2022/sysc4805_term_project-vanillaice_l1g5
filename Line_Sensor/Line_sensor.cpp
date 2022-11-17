#include "Line_sensor.hpp"
#include "const.hpp"
#include <Arduino.h>

static void LeftSensorISR()
{
  currTime = millis();

  // If left side sensor triggered, flip curr state
  if ((uint32_t)(currTime - prevTime) > DEBOUNCER)
  {
    prevTime = currTime;
    leftLine = !leftLine;
    updateSide();
  }
}

void setup_sensor()
{
    // Left Line sensor
    pinMode(LineLeft, INPUT_PULLUP);
    attachInterrupt(LineLeft, LeftSensorISR, CHANGE);
};

/*
static void MidSensorISR()
{
  currTime = millis();

  // If middle sensor triggered, flip curr state
  if ((uint32_t)(currTime - prevTime) > DEBOUNCER)
  {
    prevTime = currTime;
    midLine = !midLine;
    updateSide();
  }
}

static void Line_sensor::RightSensorISR()
{
  currTime = millis();

  // If right side sensor triggered, flip curr state
  if ((uint32_t)(currTime - prevTime) > DEBOUNCER)
  {
    prevTime = currTime;
    rightLine = !rightLine;
    updateSide();
  }
}

*/

/**
 * Update side based on where the line is detected. Side is an element of state enum.
 *
 * Return: void
 */
void updateSide()
{
  if ((leftLine == LOW) && (midLine == HIGH) && (rightLine == LOW))
  {
    currSide = MIDDLE;
    return;
  }
  else if ((leftLine == HIGH) && (midLine == LOW) && (rightLine == LOW))
  {
    currSide = LEFT;
    return;
  }
  else if ((leftLine == LOW) && (midLine == LOW) && (rightLine == HIGH))
  {
    currSide = RIGHT;
    return;
  }
  else if ((leftLine == LOW) && (midLine == LOW) && (rightLine == LOW))
  {
    currSide = NONE;
    return;
  }
  else if ((leftLine == HIGH) && (midLine == HIGH) && (rightLine == HIGH))
  {
    currSide = FORWARD;
    return;
  }
}