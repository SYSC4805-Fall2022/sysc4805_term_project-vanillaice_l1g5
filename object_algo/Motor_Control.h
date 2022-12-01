#ifndef MOTOR_CONTROL_H
#define MOTOR_CONTROL_H
#include <Arduino.h>

const uint32_t DEBOUNCER = 625; // Debouncer value default: 250 ms

// Motor Pin Layout
const int LSM_DIR = 44; // Left side motors - Direction Pin
const int RSM_DIR = 45; // Right side motors - Direction Pin
const int EN_PIN = 10;  // Left and right side motors - Enable Pin

// Motor Control Variables
const int DIR_FOR = 0;  // Set Direction to forward - fwd low due to cytron wiring
const int DIR_REV = 1;  // Set Direction to reverse - rev high due to cytron wiring
const int MOT_EN = 185; // Motor Enable - 204/255 = 80% duty cycle
const int MOT_DA = 0;   // Motor Disable

const int rightDelay = 1100;   // Time take to turn right 90°
const int leftDelay = 800;    // Time take to turn left 90°
const int forwardDelay = 800; // Time taken to move forward into new sweep path

// Functions
void setupMotor();
void stop();
void moveForward();
void moveForwardTimed();
void stop();
void turnLeft();
void turnRight();

#endif