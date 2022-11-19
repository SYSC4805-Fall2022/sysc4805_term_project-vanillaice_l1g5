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

void setup()
{
    Serial.begin(115200);

    printf("Setup");
    setup_sensor();
    updateSide();
}

void loop()
{
  // printf("Loop\n");
  if(getFlag()){
    printf("Line side: %d", getFlag());
    setFlag(0);
  }
}