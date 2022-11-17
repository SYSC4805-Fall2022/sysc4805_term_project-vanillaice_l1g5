/**
 * L1 G5 Vanilla Ice
 *
 * Line Sensor Handler
 *
 * Reads line sensor input to record current triggered line sides. The triggered highs
 * and lows are used to determine the side the line will be on. This info can be passed to
 * a central module to decide which way to turn.
 *
 */

#include "Line_sensor.hpp"
#include "const.hpp"
#include <avr/interrupt.h>
// #include "Line_sensor.cpp"


void setup()
{
    // Vars for debouncing
    currTime = 0;
    prevTime = 0;

    // Sensor State Vars - Default start at low
    leftLine = LOW;
    midLine = LOW;
    rightLine = LOW;
    Serial.begin(115200);

    // // Set pins as inputs
    // pinMode(line.LineLeft, INPUT_PULLUP);
    // pinMode(line.LineMid, INPUT_PULLUP);
    // pinMode(line.LineRight, INPUT_PULLUP);

    updateSide();
}

void loop()
{
}