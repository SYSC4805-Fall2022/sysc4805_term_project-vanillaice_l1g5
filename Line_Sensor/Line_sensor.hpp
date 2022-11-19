#ifndef LINE_SENSOR_H
#define LINE_SENSOR_H
#include <Arduino.h>

  // Functions
  void updateSide();
  void setup_sensor();
  void setup_timer();
  static void LeftSensorISR();
  static void MidSensorISR();
  static void RightSensorISR();
  int getFlag();
  void setFlag(int);

  // Data Structures

  // Line state enum
  enum lineSide {
    FORWARD,
    LEFT,
    MIDDLE,
    RIGHT,
    NONE,
  };

  const uint32_t DEBOUNCER = 250;  // 250 ms between allowed interrupts

  // Pin definitions
  const int LineLeft = 51;   // Left Line Sensor on Pin 51
  const int LineRight = 52;  // Right Line Sensor on Pin 52
  const int LineMid = 53;    // Middle Line Sensor on Pin 5

#endif