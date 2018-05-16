void search(){
  bool found = false;
  long previousMillis = 0;
  int servoPos = 45;
  int servoDir = 0;
  driveForward(100);
  while(!found){
    // drive the robot until it has found the rock
    if(millis()-previousMillis >= 15) {
      if(servoPos == 45) servoDir = 0;
      if(servoPos == 135) servoDir = 1;
      if(servoDir == 0) {
        servoPos += 1; 
      } else if(servoDir == 1) {
        servoPos -= 1;
      }
      soundServo.write(servoPos);
      previousMillis = millis();
    }
    if(detectClif() == 1) { //detect black right
      stopMotors();
      turnDegrees(-random(30, 90), 100); //turn left
      driveForward(100);
    }
    if(detectClif() == 2) { //detect black left
      stopMotors();
      turnDegrees(random(30, 90), 100); //turn right
      driveForward(100);
    }
    if(detectClif() == 4) { //detect black on both
      stopMotors();
      driveDistance(-100,100);
      turnDegrees(90, 100); //turn right
      driveForward(100);
    }
    if(measureDist() < 20) { //object is detected within 20cm
      stopMotors();
      if(servoPos < 90) { //detected left, turn right
        turnDegrees(90-servoPos, 100); //turn right
      } else {
        turnDegrees(-(servoPos - 90), 100); //turn right
      }
      driveForward();
    }
    //if(stoneDetected()) found = true;
  }
}
