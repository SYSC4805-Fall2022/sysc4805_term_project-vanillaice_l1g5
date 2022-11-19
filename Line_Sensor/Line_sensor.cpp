#include "Line_sensor.hpp"
#include <Arduino.h>

// Global Vars

// Sensor State Vars - Default start at low
volatile int leftLine;
volatile int midLine;
volatile int rightLine;
int changeFlag;

// Timer Vars
uint32_t currTime;
uint32_t prevTime;

// Line State
enum lineSide currSide;

void setup_timer(){
  PMC->PMC_PCER0 |= PMC_PCER0_PID29;                        // TC2 instance ID 
  TC0->TC_CHANNEL[2].TC_CMR = TC_CMR_TCCLKS_TIMER_CLOCK2    // capture mode, MCK/2, horloge sur front montant
                              | TC_CMR_ABETRG               // TIOA1 utilisé en déclencheur
                              | TC_CMR_LDRA_FALLING         // Chargement RA sur front montant
                              | TC_CMR_LDRB_RISING;         // Chargement RB sur front descendant
  TC0->TC_CHANNEL[2].TC_IER |= TC_IER_LDRAS | TC_IER_LDRBS; // interruption sur chargement de RA ou RB
  TC0->TC_CHANNEL[2].TC_CCR = TC_CCR_SWTRG | TC_CCR_CLKEN;  // Déclenchement logiciel et clock enable (start)
  NVIC_EnableIRQ(TC2_IRQn);
}

void setup_sensor()
{
    printf("Setup Sensor");
    // Vars for debouncing
    currTime = 0;
    prevTime = 0;

    // Sensor State Vars - Default start at low
    leftLine = LOW;
    midLine = LOW;
    rightLine = LOW;
    changeFlag = 0;

    // Set Pins
    pinMode(LineLeft, INPUT_PULLUP);
    pinMode(LineMid, INPUT_PULLUP);
    pinMode(LineRight, INPUT_PULLUP);

    // Attach Interrupts
    attachInterrupt(LineLeft, LeftSensorISR, CHANGE);
    attachInterrupt(LineMid, MidSensorISR, CHANGE);
    attachInterrupt(LineRight, RightSensorISR, CHANGE);
}

/**
 * Interrupt handler for right line sensor
 * 
*/
static void LeftSensorISR()
{
  printf("Left ISR");
  currTime = millis();

  // If left side sensor triggered, flip curr state
  if ((uint32_t)(currTime - prevTime) > DEBOUNCER)
  {
    prevTime = currTime;
    leftLine = !leftLine;
    updateSide();
  }
}

/**
 * Interrupt handler for middle line sensor
 * 
*/
static void MidSensorISR()
{
  currTime = millis();

  // If middle sensor triggered, flip curr state
  if ((uint32_t)(currTime - prevTime) > DEBOUNCER)
  {
    prevTime = currTime;
    midLine = !midLine;
    updateSide();
  }
}

/**
 * Interrupt handler for right line sensor
 * 
*/
static void RightSensorISR()
{
  currTime = millis();

  // If right side sensor triggered, flip curr state
  if ((uint32_t)(currTime - prevTime) > DEBOUNCER)
  {
    prevTime = currTime;
    rightLine = !rightLine;
    updateSide();
  }
}

/**
 * Update side based on where the line is detected. Side is an element of state enum.
 *
 * Return: void
 */
void updateSide()
{
  printf("Update Side");
  setFlag(1);
  if ((leftLine == HIGH) && (midLine == HIGH) && (rightLine == HIGH))
  {
    currSide = FORWARD;
    return;
  }
  else if ((leftLine == LOW) && (midLine == HIGH) && (rightLine == LOW))
  {
    currSide = MIDDLE;
    return;
  }
  else if ((leftLine == HIGH) && (midLine == LOW) && (rightLine == LOW))
  {
    currSide = LEFT;
    return;
  }
  else if ((leftLine == LOW) && (midLine == LOW) && (rightLine == HIGH))
  {
    currSide = RIGHT;
    return;
  }
  else if ((leftLine == LOW) && (midLine == LOW) && (rightLine == LOW))
  {
    currSide = NONE;
    return;
  }
}

int getFlag(){
  return changeFlag;
}

void setFlag(int flag){
  changeFlag = flag;
}