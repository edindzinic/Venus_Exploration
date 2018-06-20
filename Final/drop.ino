void drop(){
  Serial.println("Driving to within 30cm of lab");
  bool closeToLab = false;
  int threshhold = 25;
  while(!closeToLab){
    driveForward(20);
    soundServo.write(160);
    delay(200);
    int measure1 = measureDist(PIN_SOUND_TOP);
    if(measure1 < threshhold){
      stopMotors();
      closeToLab = true;
      break;
    }
    
    soundServo.write(90);
    delay(200);
    int measure2 = measureDist(PIN_SOUND_TOP);
    if(measure2 < threshhold){
      stopMotors();
      closeToLab = true;
      break;
    }
    
    soundServo.write(20);
    delay(200);
    int measure3 = measureDist(PIN_SOUND_TOP);
    if(measure3 < threshhold){
      stopMotors();
      closeToLab = true;
      break;
    }
    
    soundServo.write(90);
    delay(200);
    measure2 = measureDist(PIN_SOUND_TOP);
    if(measure2 < threshhold){
      stopMotors();
      closeToLab = true;
      break;
    } 
  }
  stopMotors();
  Serial.println("Now close to lab");

  soundServo.write(160);
  delay(500);
  int minimalDist = measureDistmm(PIN_SOUND_TOP);
  delay(100);
  int angle = soundServo.read();
  for(int i = 160; i>0; i-=2){
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
  delay(1200);
  driveForward(7);

  Serial.print("leftOrRight: "); Serial.println(leftOrRight);

  int originalDist = measureDistmm(PIN_SOUND_TOP);
  int curDist = originalDist;

  while(1){
    // drive parallel
    while(1) {
      driveDistance(70,70);
      curDist = measureDistmm(PIN_SOUND_TOP);
      if(curDist-originalDist > 200) break;
      if(curDist-originalDist > 25) turn(-70*leftOrRight, 60);
      if(curDist-originalDist < -25) turn(70*leftOrRight, 60);
    }
    
    // turn a corner
    stopMotors();
    Serial.println("Found corner");
    driveDistance(120,70);
    turnDegrees(-1*leftOrRight*90,70);
    driveDistance(originalDist+30,70);

    originalDist = measureDistmm(PIN_SOUND_TOP);
    curDist = originalDist;
    Serial.print("new originalDist: "); Serial.println(originalDist);
    
    if(originalDist>500){ // we've found the entrance, drive a little further
      delay(200);
      driveDistance(-150, 70);
      driveForward(70);
      
      while(detectCliff()==0) { }
      stopMotors();
      break;
    }
  }
  
  switch(detectCliff()){
    case 1: // right wheel is on tape
      leftMotor.write(96);
      break;
    case 2: // left wheel is on tape
      rightMotor.write(84);
      break;
  }

  while(detectCliff() != 4){ }
  stopMotors();
  // we are now on the ramp, past the tape
  driveForward(70);
  while(detectCliff()==4){ }

  switch(detectCliff()){
    case 1: // right wheel is on tape
      rightMotor.write(84);
      break;
    case 2: // left wheel is on tape
      leftMotor.write(96);
      break;
  }

  while(detectCliff() != 0){ }
  stopMotors();
  
  driveForward(70);
  while(detectCliff() == 0){ }
  
  driveDistance(20,70);

  // parralel to the entrance so now turn towards it
  turnDegrees(-1*leftOrRight*90,70);
  
  driveDistance(200, 70);

  driveForward(70);
  long previousMillis = millis();
  while(detectCliff() != 4) { 
    if(millis()-previousMillis > 200) {
      if(detectCliff() == 1){
        stopMotors();
        turn(-70,40);
        driveForward(70);
      }
      if(detectCliff()== 2){
        stopMotors();
        turn(70,40);
        driveForward(70);
      }
      previousMillis = millis();
    }
  }
  stopMotors();
  Serial.print(detectCliff());
  driveDistance(-50, 70);
  driveForward(70);
  while(detectCliff() == 0);
  stopMotors();
  switch(detectCliff()){
    case 1: // right wheel is on tape
      leftMotor.write(96);
      break;
    case 2: // left wheel is on tape
      rightMotor.write(84);
      break;
  }

  while(detectCliff() != 4){ }
  stopMotors();
  grabber(true);
  delay(1000);
  grabber(false);
  delay(500);
  driveDistance(-40, 70);
  driveBackwards(70);
  while(detectCliff() != 4) {  }
  stopMotors();

  driveDistance(-400,70);
  turnDegrees(180,70);

  x = 0.0;
  y = 0.0;
  directionAngle = 0;
  
  // switch state back to searh
  state = STATE_SEARCH;
}


