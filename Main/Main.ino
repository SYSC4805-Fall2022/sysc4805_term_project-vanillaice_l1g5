#include "Motor_Control.h"
#include "Line_sensor.hpp"
#include "UltrasonicSensor.h"
#include <DueTimer.h> // Add as reference to report

// Constants
#define ULTRASONIC_THRESH 15.0000000

// Globals
boolean turnSide = false;
volatile boolean US_FLAG_RIGHT; // detection flag to be checked
volatile boolean US_FLAG_LEFT;  // detection flag to be checked
volatile float US_DIST_RIGHT;
volatile float US_DIST_LEFT;
uint32_t turnTime;
volatile boolean turnCheck = true;

// Class instantiations
// Class HCSR04 - Ultrasonic Sensor (trig pin , echo pin)
UltrasonicSensor US1(4, 5);
UltrasonicSensor US2(6, 7);

// Setup
void setup()
{
  Serial.begin(115200);

  // Set up ultrasonic sensors
  Timer.getAvailable().attachInterrupt(UltrasonicHandler).start(60000); // Every 60 ms

  // Set up Line sensors
  setup_sensor();

  // Set up Motor
  setupMotor();
}

void loop()
{
  // Delete before demo
  // printf("Left Left : %d\n", analogRead(Left_LineLeft));
  // printf("Left Right : %d\n",analogRead(Left_LineRight));
  printf("Left Mid : %d\n", analogRead(Left_LineMid));
  // printf("Right Left : %d\n",analogRead(Right_LineLeft));
  printf("Right Right : %d\n", analogRead(Right_LineRight));
  printf("Right Mid : %d\n", analogRead(Right_LineMid));
  delay(200); // TODO: delete before demo, here so it doesn't print 400 times a second

  if (getLineFlag())
  {
    // Reset change flags
    setLineFlag(0);
    avoidLine();
    nonBlockWait(150);
  }
  // Avoid Object
  else if (US_FLAG_RIGHT || US_FLAG_LEFT)
  {
    avoidObject();
  }
  // Nothing found, move forward
  else
  {
    moveForward();
  }
}

void avoidLine()
{
  // Check if line is still there
  if (getSide_Right() > LINE_THRESHOLD || getSide_Left() > LINE_THRESHOLD)
  {

    // Stop if line found
    stop();
    nonBlockWait(150);

    if (turnSide)
    {
      // Turn right, move forward and turn right again
      turnRight();
      stop();
      nonBlockWait(150);

      moveForwardTimed();
      stop();
      nonBlockWait(150);

      turnRight();
      stop();
      nonBlockWait(150);

      turnSide = !turnSide;
    }
    else
    {
      // Turn right, move forward and turn right again
      turnLeft();
      stop();
      nonBlockWait(150);

      moveForwardTimed();
      stop();
      nonBlockWait(150);

      turnLeft();
      stop();
      nonBlockWait(150);

      turnSide = !turnSide;
    }
  }
  else
  {
    moveForward();
  }
}

void nonBlockWait(uint32_t delay)
{
  // Timing vars - local
  unsigned long start = millis();
  unsigned long end = start;

  // Turn until forward move time has passed
  while (end - start < delay)
  {
    end = millis();
  }
}

void UltrasonicHandler()
{
  US_DIST_RIGHT = US1.getDistCM();

  if (US_DIST_RIGHT < ULTRASONIC_THRESH && US_DIST_RIGHT > 0.0)
  {
    US_FLAG_RIGHT = 1;
    printf("object at %f on right \n", US_DIST_RIGHT);
  }
  US_DIST_LEFT = US2.getDistCM();

  if (US_DIST_LEFT < ULTRASONIC_THRESH && US_DIST_LEFT > 0.0)
  {
    US_FLAG_LEFT = 1;
    printf("object at %f on left \n", US_DIST_LEFT);
  }
}

void avoidObject()
{

  // object on right
  if (US_FLAG_RIGHT)
  { 
    printf("Seeing object on right\n");
    US_FLAG_RIGHT = 0;
    turnLeft(); // turn left to avoid
    stop();
    nonBlockWait(150);
    moveForward();
  }
  else if (US_FLAG_LEFT)
  { // object on left
    printf("Seeing object on left\n");
    US_FLAG_LEFT = 0;
    turnRight();
    stop();
    nonBlockWait(150);
    moveForward();
  }
}


// Here in case sensors magically start working
//   if (getSide_Right() > LINE_THRESHOLD || getSide_Left() > LINE_THRESHOLD)
//   {
//     stop();
//     if (turnSide)
//     {
//       // printf("Turning right\n");
//       turnRight();
//       stop();
//       nonBlockWait(150);

//       // Don't let other interrupts change the values while this is running
//       noInterrupts();
//       readLine();
//       interrupts();

//       if (getSide_Right() > LINE_THRESHOLD && getSide_Left() > LINE_THRESHOLD)
//       {
//         turnRight();
//         stop();
//         nonBlockWait(150);
//       }
//       else
//       {
//         // Check for obstacle
//         moveForwardTimed();
//         stop();
//         nonBlockWait(150);

//         turnRight();
//         stop();
//         nonBlockWait(150);

//         turnSide = false;
//       }
//     }
//     else
//     {
//       // printf("Turning left\n");
//       turnLeft();
//       if (!(getSide_Right() > LINE_THRESHOLD && getSide_Left() > LINE_THRESHOLD))
//       {
//         // check for obstacle
//         moveForwardTimed();
//         printf("Completed moveForwardTimed \n");
//         turnLeft();
//         turnSide = true;
//       }
//       else
//       {
//         printf("oop still more lines\n");
//         turnLeft();
//       }
//     }
//   }
//   else
//   {
//     moveForward();
//   }