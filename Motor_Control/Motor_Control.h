#ifndef MOTOR_CONTROL_H
#define MOTOR_CONTROL_H
#include <Arduino.h>

const uint32_t DEBOUNCER = 250; //Debouncer value default: 250 ms

// Motor Pin Layout
const int LSM_DIR = 44; // Left side motors - Direction Pin
const int RSM_DIR = 45; // Right side motors - Direction Pin
const int EN_PIN = 46;  // Left side motors - Enable Pin

// Motor Control Variables
const int DIR_FOR = 0; // Set Direction to forward
const int DIR_REV = 1; // Set Direction to reverse
const int MOT_EN = 204;  // Motor Enable
const int MOT_DA = 0;  // Motor Disable

const int rightDelay = 625;
const int leftDelay = 700;
const int forwardDelay = 500;

// Functions
void setupMotor();
void stop();
void moveForward();
void stop();
void turnLeft();
void turnRight();

#endif