#ifndef LINE_SENSOR_H
#define LINE_SENSOR_H
#include <Arduino.h>

// Left sensor Functions
void updateSide_left();
void setup_sensor();
static void LeftSensorISR_Left();
static void MidSensorISR_Left();
static void RightSensorISR_Left();
int getFlag_Left();
void setFlag_Left(int);
int getSide_Left();

// Right sensor functions
static void LeftSensorISR_Right();
static void MidSensorISR_Right();
static void RightSensorISR_Right();
void updateSide_right();
int getFlag_Right();
void setFlag_Right(int flag);
int getSide_Right();

// Data Structures

// Line state enum
enum lineSide {
  NONE,
  LEFT,
  MIDDLE,
  RIGHT,
  FORWARD,
};

// const uint32_t DEBOUNCER = 250;  // 250 ms between allowed interrupts

// Pin definitions
const int Left_LineLeft = 51;   // Left Line Sensor on Pin 51
const int Left_LineRight = 52;  // Right Line Sensor on Pin 52
const int Left_LineMid = 53;    // Middle Line Sensor on Pin 53

const int Right_LineLeft = 48; 
const int Right_LineRight = 49;
const int Right_LineMid = 50;

#endif