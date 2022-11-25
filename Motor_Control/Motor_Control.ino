#include "Motor_Control.h"

// Setup
void setup(){
    setupMotor();
}

// Loop

void loop(){

    moveForward();
    delay(forwardDelay);

    stop();
    delay(3000);
}