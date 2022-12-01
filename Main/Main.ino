#include "Motor_Control.h"
#include "Line_sensor.hpp"
boolean turnSide = false;

int test = 0;

// Setup
void setup()
{
  Serial.begin(115200);

  // Set up Line sensors
  setup_sensor();

  // Set up Motor
  setupMotor();
}

void loop()
{
  // printf("Left Left : %d\n", analogRead(Left_LineLeft));
  // printf("Left Right : %d\n",analogRead(Left_LineRight));
  printf("Left Mid : %d\n", analogRead(Left_LineMid));
  // printf("Right Left : %d\n",analogRead(Right_LineLeft));
  printf("Right Right : %d\n", analogRead(Right_LineRight));
  printf("Right Mid : %d\n", analogRead(Right_LineMid));
  delay(200);
  if (getLineFlag())
  {
    // Reset change flags
    setLineFlag(0);
    avoidLine();
    nonBlockWait(300);
  }
}

void avoidLine()
{
  if (getSide_Right() > LINE_THRESHOLD || getSide_Left() > LINE_THRESHOLD)
  {

    stop();
    nonBlockWait(150);

    if (turnSide)
    {
      turnRight();
      stop();
      nonBlockWait(150);

      moveForwardTimed();
      stop();
      nonBlockWait(150);

      turnRight();
      stop();
      nonBlockWait(150);

      turnSide != turnSide;
    }
    else
    {
      turnLeft();
      stop();
      nonBlockWait(150);

      moveForwardTimed();
      stop();
      nonBlockWait(150);

      turnLeft();
      stop();
      nonBlockWait(150);

      turnSide != turnSide;
    }
  }
  else
  {
    moveForward();
  }

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
