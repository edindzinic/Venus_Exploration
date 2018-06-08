void drop(){
  Serial.println("Driving to within 30cm of lab");
  bool closeToLab = false;
  int threshhold = 25;
  while(!closeToLab){
    driveForward(3);
    soundServo.write(160);
    delay(300);
    int measure1 = measureDist(PIN_SOUND_TOP);
    if(measure1 < threshhold){
      stopMotors();
      closeToLab = true;
      break;
    }
    
    soundServo.write(90);
    delay(300);
    int measure2 = measureDist(PIN_SOUND_TOP);
    if(measure2 < threshhold){
      stopMotors();
      closeToLab = true;
      break;
    }
    
    soundServo.write(20);
    delay(300);
    int measure3 = measureDist(PIN_SOUND_TOP);
    if(measure3 < threshhold){
      stopMotors();
      closeToLab = true;
      break;
    }
    
    soundServo.write(90);
    delay(300);
    measure2 = measureDist(PIN_SOUND_TOP);
    if(measure2 < threshhold){
      stopMotors();
      closeToLab = true;
      break;
    } 
  }
  stopMotors();
  Serial.println("Now close to lab");

  soundServo.write(180);
  delay(500);
  int minimalDist = measureDistmm(PIN_SOUND_TOP);
  delay(100);
  int angle = soundServo.read();
  for(int i = 180; i>0; i--){
    int dist = measureDistmm(PIN_SOUND_TOP);
    delay(30);
    if(dist<minimalDist){
      minimalDist=dist;
      angle = soundServo.read();
      Serial.println(angle);
    }
    soundServo.write(i);
  }
  Serial.print("minimal dist: "); Serial.println(minimalDist); 
  Serial.print("minimal angle: "); Serial.println(angle);

  int leftOrRight;
  if(angle > 90) {
    //Turn right
    turnDegrees(180-angle, 70);
    soundServo.write(180);
    leftOrRight = 1;
  } else {
    //Turn left
    turnDegrees(-angle, 70);
    soundServo.write(0);
    leftOrRight = -1;
  }
  delay(2000);
  driveForward(7);

  Serial.print("leftOrRight: "); Serial.println(leftOrRight);

  int originalDist = measureDistmm(PIN_SOUND_TOP);
  int curDist = originalDist;

  while(1){
    // drive parallel
    while(abs(curDist-originalDist) < 100){
      driveForward(70);
      curDist = measureDistmm(PIN_SOUND_TOP);
      Serial.print("curDist: "); Serial.println(curDist);
      // correct for not driving exactly parallel
      if(curDist-originalDist > 15) turnDegrees(-7*leftOrRight,70);
      if(curDist-originalDist < -15) turnDegrees(7*leftOrRight,70);
      delay(100);
    }
    
    // turn a corner
    stopMotors();
    Serial.println("Found corner");
    delay(1000);
    driveDistance(200,70);
    delay(1000);
    turnDegrees(-1*leftOrRight*90,70);
    delay(1000);
    driveDistance(originalDist+30,70);

    originalDist = measureDistmm(PIN_SOUND_TOP);
    curDist = originalDist;
    Serial.print("new originalDist: "); Serial.println(originalDist);
    
    if(originalDist>500){ // we've found the entrance, drive a little further
      driveDistance(120,70);
      break;
    }
    
  }

  // parralel to the entrance so now turn towards it
  turnDegrees(-1*leftOrRight*90,70);

  driveForward(70);
  int cliffDetect;
  do{ 
    cliffDetect = detectCliff(); 
  }while(cliffDetect != 0);
  
  switch(cliffDetect){
    case 1: // right wheel is on tape
      leftMotor.write(90);
      break;
    case 2: // left wheel is on tape
      rightMotor.write(96);
      break;
  }

  while(detectCliff() != 4){ }
  stopMotors();

  // we are now on the ramp, past the tape
  driveDistance(30,70);
  
  
  driveForward(20);
  while(detectCliff() != 4) {
    
    
  }
  stopMotors();
  grabber(true);
  delay(1000);
  driveDistance(-150, 20);
  grabber(false);
  driveBackwards(20);
  while(detectCliff() != 4) {
    
  }
  stopMotors();

  driveDistance(-20,70);
  turnDegrees(180,70);
  
  // switch state back to searh
  state = STATE_SEARCH;
}


