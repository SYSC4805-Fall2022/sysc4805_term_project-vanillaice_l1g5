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

// ISR Vars
uint32_t currTime = 0;
uint32_t prevTime = 0;
uint32_t DEBOUNCER = 250;           // 250 ms between allowed interrupts 

// Pin definitions
const int LineLeft = 51;            // Left Line Sensor on Pin 51
const int LineRight = 52;           // Right Line Sensor on Pin 52
const int LineMid = 53;             // Middle Line Sensor on Pin 5

// Sensor State Vars - Default start at low
volatile int leftLine = LOW;
volatile int midLine = LOW;
volatile int rightLine = LOW;

// Line state enum
enum lineSide {
  LEFT, 
  MIDDLE,
  RIGHT,
  NONE,
};

// Line State
enum lineSide currSide; 

void setup()
{
    Serial.begin(115200);

    // Set pins as inputs
    pinMode(LineLeft, INPUT_PULLUP);
    pinMode(LineMid, INPUT_PULLUP);
    pinMode(LineRight, INPUT_PULLUP);

    updateSide();

    attachInterrupt(digitalPinToInterrupt(LineLeft), LeftSensorISR, CHANGE);
    attachInterrupt(digitalPinToInterrupt(LineMid), MidSensorISR, CHANGE);
    attachInterrupt(digitalPinToInterrupt(LineRight), RightSensorISR, CHANGE);
}

void loop()
{}

void LeftSensorISR()
{
    currTime = millis();

    // If left side sensor triggered, flip curr state
    if ((uint32_t)(currTime - prevTime) > DEBOUNCER)
    {
        prevTime = currTime;  
        leftLine = !leftLine;
        updateSide();
    }
}

void MidSensorISR()
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

void RightSensorISR()
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
void updateSide(){
    if ((leftLine == LOW) && (midLine == HIGH) && (rightLine == LOW)){
      currSide = MIDDLE;
      return;
    }
    else if ((leftLine == HIGH) && (midLine == LOW) && (rightLine == LOW)){
      currSide = LEFT;
      return;
    }
    else if ((leftLine == LOW) && (midLine == LOW) && (rightLine == HIGH)){
      currSide = RIGHT;
      return;
    }
    else if ((leftLine == LOW) && (midLine == LOW) && (rightLine == LOW)){
      currSide = NONE;
      return;
    }
}
