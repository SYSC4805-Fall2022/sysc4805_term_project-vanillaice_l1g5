bool side = True // True - right, False - left 

//it does alternating turns (not complete)

void setup() {
  // put your setup code here, to run once:

}

void loop() {
  // put your main code here, to run repeatedly:
  if (Line Detected){
    if (side){
      turnRight();
      moveForward(the short one);
      turnRight();
      side = False;
      break;
    }
    else {
      turnLeft();
      moveForward(the short one);
      turnLeft();
      side = True;
      break;
    }
  }
  else {
    moveForward();
  }

}
