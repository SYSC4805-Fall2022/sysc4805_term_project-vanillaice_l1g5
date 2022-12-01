#ifndef LINE_SENSOR_H
#define LINE_SENSOR_H
#include <Arduino.h>

// Constants 

// Pin definitions
const int Left_LineLeft = A6;   // Left Line Sensor on Pin 51
const int Left_LineRight = A7;  // Right Line Sensor on Pin 52
const int Left_LineMid = A5;    // Middle Line Sensor on Pin 53

const int Right_LineLeft = A9; 
const int Right_LineRight = A11;
const int Right_LineMid = A10;

const int LINE_THRESHOLD = 900; // Threshold for line sensor analog read diff between dark and light

// Line state enum
enum lineSide {
  NONE,
  LEFT,
  MIDDLE,
  RIGHT,
  FORWARD,
};

// Common Functions
void setup_sensor();
void readLine();
char *currSideText(lineSide);
void setLineFlag(int);
int getLineFlag();
void resetSensorVals();

// Left sensor Functions
static void MidSensorISR_Left();
int getSide();

// Right sensor functions
static void MidSensorISR_Right();
static void RightSensorISR_Right();



#endif