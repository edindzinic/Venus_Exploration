void grabber(bool state){
  //True is open, false is close
  if(state){
    grabbingServo.write(180);
  }else{
    grabbingServo.write(0);
  }
}

void stopMotors() {
  rightMotor.write(90);
  leftMotor.write(90);

  if(driving) {
    if(direction2) {
      //Forward
      updatePositionForwards(counter2);
    } else {
      //Backwards
      updatePositionBackwards(counter2);
    }
  }
}

void driveBackwards(int speed1) {
  counter2 = 0;
  direction2 = false;
  driving = true;
  
  rightMotor.write(90 + speed1);
  leftMotor.write(90 - speed1);
}

void driveForward(int speed1) {
  counter2 = 0;
  direction2 = true;
  driving = true;
  
  rightMotor.write(90 - speed1);
  leftMotor.write(90 + speed1);
}

void turnDegrees_old(int degrees1, int turningSpeed1) {
  int counter = 0;
  float degreesdivided = abs(degrees1/90.0);
  int stops = round(degreesdivided * 26); 

  rightMotor.attach(PIN_MOTOR_RIGHT);
  leftMotor.attach(PIN_MOTOR_LEFT);
  
  if(degrees1 < 0) {
    rightMotor.write(90 - turningSpeed1);
    leftMotor.write(90 - turningSpeed1);
  } else {
    rightMotor.write(90 + turningSpeed1);
    leftMotor.write(90 + turningSpeed1);
  }
  
  while(counter != stops) {
    if(digitalRead(PIN_ENCODER_LEFT) !=  prevState) {
      counter += 1;
      prevState = digitalRead(PIN_ENCODER_LEFT);
    }
  }

  stopMotors();
}

void turnDegrees(int degrees1, int turningSpeed1) {
  driving = false;
  stopMotors();
  int stops = abs(degrees1 * 25 / 90);

  updateAngle(degrees1);

  rightMotor.attach(PIN_MOTOR_RIGHT);
  leftMotor.attach(PIN_MOTOR_LEFT);

  if(degrees1 < 0) {
    rightMotor.write(90 - turningSpeed1);
    leftMotor.write(90 - turningSpeed1);
  } else {
    rightMotor.write(90 + turningSpeed1);
    leftMotor.write(90 + turningSpeed1);
  }
  
  counter2 = 0;
  while(counter2 < stops) {
  }
  
  stopMotors();
}

void turn(int turningSpeed1, int time1) {
  rightMotor.write(90 + turningSpeed1);
  leftMotor.write(90 + turningSpeed1);
  delay(time1);
  stopMotors();
}

void driveDistance_old(int dist, int speed1) {
  int counter = 0;
  float distDivided = abs(dist/215.0);
  int stops = floor(distDivided * 64);
  
  if(dist < 0) {
    driveBackwards(speed1);
  } else {
    driveForward(speed1);
  }

  int prevState = digitalRead(PIN_ENCODER_LEFT);
  while(counter != stops) {
    if(digitalRead(PIN_ENCODER_LEFT) !=  prevState) {
      counter += 1;
      prevState = digitalRead(PIN_ENCODER_LEFT);
    }
  }
  
  stopMotors();
}

void driveStops(int stops, int speed1) {  
  if(stops < 0) {
    driveBackwards(speed1);
  } else {
    driveForward(speed1);
  }

  counter2 = 0;

  while(counter2 < abs(stops)) {
  }
    
  stopMotors();
}

void driveDistance(int dist, int speed1) {
  int stops = abs(dist * 64 / 215);
  
  if(dist < 0) {
    driveBackwards(speed1);
  } else {
    driveForward(speed1);
  }

  while(counter2 < stops) {
  }
    
  stopMotors();
}
