void grab(){
  delay(500);
  turnDegrees(40,20);
  delay(2000);
  counter2 = 0;

  long turnTimer = millis();

  // now turn slowly towards rock
  rightMotor.write(90 - 2);
  leftMotor.write(90 - 2);
  int distance = measureDist(PIN_SOUND_BOTTOM);
  while(distance > 15) {
    delay(10);
    distance = measureDist(PIN_SOUND_BOTTOM);
    delay(10);
    if(millis() - turnTimer > 2200){
      state = STATE_SEARCH;
//      turn(2,2200+700);
      stopMotors();
      int turnCounter = counter2;
      counter2 = 0;
      rightMotor.write(90 + 2);
      leftMotor.write(90 + 2);
      while(counter2 < turnCounter){}
      stopMotors();
      return;
    }
  }

//  int timeTurned = millis()-turnTimer;
 
  stopMotors();
  int turnCounter = counter2+1;
  rightMotor.write(90+2);
  leftMotor.write(90+2);
  while(counter2 < turnCounter){}
  stopMotors();

  turnCounter = counter2 - 1;

  grabber(true);
  driveDistance((distance)*10 + 60,10);
  grabber(false);
  delay(1000);
  driveDistance(-(distance*10 + 60), 10);
//  turn(2,timeTurned-200+700);

  counter2 = 0;
  rightMotor.write(90 + 2);
  leftMotor.write(90 + 2);
  while(counter2 < turnCounter){}
  stopMotors();
  
  if(!digitalRead(PIN_GRAB_DETECT)) {
    grabbingServo.write(100);
    state = STATE_SEARCH;
  } else {
    state = STATE_FINDLAB;
  }
}

