#ifndef LINE_SENSOR_H
#define LINE_SENSOR_H
#include <Arduino.h>

// Constructor
Line_sensor();

// Functions
// static void LeftSensorISR();
// static void MidSensorISR();
// static void RightSensorISR();
void updateSide();

// Data Structures
// Line state enum
enum lineSide
{
  FORWARD,
  LEFT,
  MIDDLE,
  RIGHT,
  NONE,
};

// Global Vars
// Line State
enum lineSide currSide;

#endif