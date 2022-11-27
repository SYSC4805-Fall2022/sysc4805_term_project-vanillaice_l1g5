#include "Motor_Control.h"
#include <Arduino.h>

/**
 * Setup Cytron Board
 */
void setupMotor()
{
    // Set pins as outputs
    pinMode(LSM_DIR, OUTPUT);
    pinMode(EN_PIN, OUTPUT);
    pinMode(RSM_DIR, OUTPUT);

    // Start Off
    digitalWrite(EN_PIN, MOT_DA);   // Disable Motors
    digitalWrite(RSM_DIR, DIR_FOR); // Set Right Motors to move forward
    digitalWrite(LSM_DIR, DIR_FOR); // Set Left Motors to move forward
}

/**
 * Stop Vehicle by setting the motor enable pin to LOW
 */
void stop()
{
    // Disable all motors
    digitalWrite(EN_PIN, MOT_DA);
    return;
}

/*
 * Move forward constantly
 */
void moveForward()
{
    digitalWrite(RSM_DIR, DIR_FOR); // Set Right Motors to move forward
    digitalWrite(LSM_DIR, DIR_FOR); // Set Left Motors to move forward

    // Enable all motors
    analogWrite(EN_PIN, MOT_EN);
    return;
}

/**
 * @brief Turn forward long enough to move into new sweep path. 
 * 
 * Time to move forward defined by forwardDelay in motor_Control.h
 * 
 */
void moveForwardTimed(){
    digitalWrite(RSM_DIR, DIR_FOR); // Set Right Motors to move forward
    digitalWrite(LSM_DIR, DIR_FOR); // Set Left Motors to move forward

    //Timing vars - local
    unsigned long start = millis();
    unsigned long end = start;

    // Enable all motors
    analogWrite(EN_PIN, MOT_EN);

    // Turn until forward move time has passed
    while (end - start < forwardDelay)
    {
        end = millis();
    }
    analogWrite(EN_PIN, MOT_DA);
    return;
}

/*
 * Move backwards constantly
 */
void moveBackward()
{
    digitalWrite(RSM_DIR, DIR_REV); // Set Right Motors to move in reverse
    digitalWrite(LSM_DIR, DIR_REV); // Set Left Motors to move in reverse

    // Enable all motors
    analogWrite(EN_PIN, MOT_EN);
    return;
}

/*
 * Turn vehicle right for a set amount of time
 */
void turnLeft()
{
    digitalWrite(RSM_DIR, DIR_REV); // Set Right Motors to move in reverse
    digitalWrite(LSM_DIR, DIR_FOR); // Set Left Motors to move forward

    //Timing vars - local
    unsigned long start = millis();
    unsigned long end = start;

    // Enable all motors, start turning
    analogWrite(EN_PIN, MOT_EN);

    // Turn until 90° time has passed
    while (end - start < leftDelay)
    {
        end = millis();
    }

    // Done turning
    stop();

    return;
}

/*
 * Turn vehicle right 90°
 */
void turnRight()
{
    digitalWrite(RSM_DIR, DIR_FOR); // Set Right Motors to move forward
    digitalWrite(LSM_DIR, DIR_REV); // Set Left Motors to move in reverse

    //Timing vars - local
    unsigned long start = millis();
    unsigned long end = start;

    // Enable all motors - start turning
    analogWrite(EN_PIN, MOT_EN);

    // Turn until 90° time has passed
    while (end - start < rightDelay)
    {
        end = millis();
    }

    // Done turning
    stop();

    return;
}