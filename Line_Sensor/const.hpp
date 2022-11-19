#ifndef CONST_H
#define CONST_H
#include <Arduino.h>

// ISR Vars
  uint32_t currTime;
  uint32_t prevTime;
  const uint32_t DEBOUNCER = 250; // 250 ms between allowed interrupts

  // Pin definitions
  const int LineLeft = 51;  // Left Line Sensor on Pin 51
  const int LineRight = 52; // Right Line Sensor on Pin 52
  const int LineMid = 53;   // Middle Line Sensor on Pin 5

  // Sensor State Vars - Default start at low
  volatile int leftLine;
  volatile int midLine;
  volatile int rightLine;

#endif