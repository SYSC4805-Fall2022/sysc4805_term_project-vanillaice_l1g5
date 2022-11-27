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

    setup_sensor();
    updateSide_left();
}

void loop()
{
  if(getFlag_Left()){
    // printf("\tLine side: "); printf(getSide()); printf("\n");
    printf("Output: %d/n", getSide_Left());
    setFlag_Left(0);
  }
}