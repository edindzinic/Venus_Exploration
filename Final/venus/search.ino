void search(){
  bool found = false;
  int pos = 0;    // variable to store the servo position
  int cPos;       // current position
  int gPos = 120;       // goal position
  int tDelay = 50; // delay between moves, gives appearance of smooth motion
  long myservo_movetime = 0; // next time in millis servo next moves
  driveForward(40);
  while(!found){
    // drive the robot until it has found the rock
    cPos = soundServo.read();
    if (cPos <= 60) gPos = 120;
    if (cPos >= 120) gPos = 60;
    if (cPos != gPos && millis() >= myservo_movetime) {
      if (cPos < gPos) soundServo.write(cPos+10);
      if (cPos > gPos) soundServo.write(cPos-10);
      //if (cPos == gPos) // nothing
      myservo_movetime = millis() + tDelay;
    }
    if(detectCliff() == 1) { //detect black right
      stopMotors();
      driveDistance(-50,100);      
      turnDegrees(-random(30, 90), 100); //turn left
      driveForward(100);
    }
    if(detectCliff() == 2) { //detect black left
      stopMotors();
      driveDistance(-50,100);      
      turnDegrees(random(30, 90), 100); //turn right
      driveForward(100);
    }
    if(detectCliff() == 4) { //detect black on both
      stopMotors();
      driveDistance(-100,100);
      turnDegrees(90, 100); //turn right
      driveForward(100);
    }
    if(measureDist(PIN_SOUND_TOP) < 25) { //object is detected within 20cm
      stopMotors();
      if(cPos < 90) { //detected left, turn right
        turnDegrees(-random(30, 90), 20); //turn right
      } else {
        turnDegrees(random(30, 90), 20); //turn left
      }
      driveForward(20);
    }
    delay(1); //Ultrasonic inacuracies
    if(stoneDetected() != 0) found = true;
  }
  stopMotors();
  state = STATE_GRAB;
}

