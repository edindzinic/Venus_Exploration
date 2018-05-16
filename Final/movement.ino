void grabber(bool state){
  if(state){
    grabbingServo.write(180);
  }else{
    grabbingServo.write(0);
  }
}

void stopMotors() {
  rightMotor.detach();
  leftMotor.detach();
}

void driveBackwards(int speed1) {
  rightMotor.attach(PIN_MOTOR_RIGHT);
  leftMotor.attach(PIN_MOTOR_LEFT);
  rightMotor.writeMicroseconds(1400 - speed1);
  leftMotor.writeMicroseconds(1600 + speed1);
}

void driveForward(int speed1) {
  rightMotor.attach(PIN_MOTOR_RIGHT);
  leftMotor.attach(PIN_MOTOR_LEFT);
  rightMotor.writeMicroseconds(1600 + speed1);
  leftMotor.writeMicroseconds(1400 - speed1);
}

void turnDegrees(int degrees1, int turningSpeed) {
  int counter = 0;
  float degreesdivided = abs(degrees1/90.0);
  int stops = round(degreesdivided * 23); 

  rightMotor.attach(PIN_MOTOR_RIGHT);
  leftMotor.attach(PIN_MOTOR_LEFT);
  
  if(degrees1 < 0) {
    rightMotor.writeMicroseconds(1400 - turningSpeed);
    leftMotor.writeMicroseconds(1400 - turningSpeed);
  } else {
    rightMotor.writeMicroseconds(1600 + turningSpeed);
    leftMotor.writeMicroseconds(1600 + turningSpeed);
  }
  
  while(counter != stops) {
    if(digitalRead(PIN_ENCODER_LEFT) !=  prevState) {
      counter += 1;
      prevState = digitalRead(PIN_ENCODER_LEFT);
    }
  }
  
  rightMotor.detach();
  leftMotor.detach();
}
