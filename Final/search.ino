void search(){
  bool found = false;
  long previousMillis = 0;
  int servoPos = 60;
  int servoDir = 0;
  driveForward(100);
  while(!found){
    // drive the robot until it has found the rock
    if(millis()-previousMillis >= 5) {
      if(servoPos == 60) servoDir = 0;
      if(servoPos == 120) servoDir = 1;
      if(servoDir == 0) {
        servoPos += 1; 
      } else if(servoDir == 1) {
        servoPos -= 1;
      }
      soundServo.write(servoPos);
      previousMillis = millis();
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
    if(measureDist() < 25) { //object is detected within 20cm
      stopMotors();
      if(servoPos < 90) { //detected left, turn right
        turnDegrees(-random(30, 90), 100); //turn right
      } else {
        turnDegrees(random(30, 90), 100); //turn left
      }
      driveForward(100);
    }
    //if(stoneDetected()) found = true;
  }
}

