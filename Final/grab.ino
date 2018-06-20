void grab(){
  delay(1000);
  turnDegrees(50,20);
  rightMotor.write(93 - 2);
  leftMotor.write(93 - 2);
  int distance = measureDist(PIN_SOUND_BOTTOM);
  while(distance > 15) {
    delay(10);
    distance = measureDist(PIN_SOUND_BOTTOM);
    delay(10);
  }
  stopMotors();
  delay(1000);
  grabber(true);
  driveDistance((distance)*10 + 60,10);
  grabber(false);
  delay(1000);
  if(!digitalRead(PIN_GRAB_DETECT)) {
    grabbingServo.write(100);
    driveDistance(-100, 10);
    turnDegrees(-70,20);
    state = STATE_SEARCH;
  } else {
    state = STATE_FINDLAB;
  }
}

