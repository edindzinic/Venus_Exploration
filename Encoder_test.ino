#include <Servo.h>

#define leftEncoder 7
#define rightEncoder 8
#define leftMotorPin 12
#define rightMotorPin 13

int prevState = HIGH;
int revolutions = 0;

Servo rightMotor;
Servo leftMotor;

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  
  pinMode(leftEncoder, INPUT);
  pinMode(rightEncoder, INPUT);
  

  turnDegrees(-180, 1);
  driveForward(100);
  delay(1000);
  driveBackwards(100);
  delay(1000);
  stopMotors();
}

void loop() {
  
}

void stopMotors() {
  rightMotor.detach();
  leftMotor.detach();
}

void driveBackwards(int speed1) {
  rightMotor.attach(rightMotorPin);
  leftMotor.attach(leftMotorPin);
  rightMotor.writeMicroseconds(1400 - speed1);
  leftMotor.writeMicroseconds(1600 + speed1);
}

void driveForward(int speed1) {
  rightMotor.attach(rightMotorPin);
  leftMotor.attach(leftMotorPin);
  rightMotor.writeMicroseconds(1600 + speed1);
  leftMotor.writeMicroseconds(1400 - speed1);
}

void turnDegrees(int degrees1, int turningSpeed) {
  int counter = 0;
  float degreesdivided = abs(degrees1/90.0);
  int stops = round(degreesdivided * 23); 

  rightMotor.attach(rightMotorPin);
  leftMotor.attach(leftMotorPin);
  
  if(degrees1 < 0) {
    rightMotor.writeMicroseconds(1400 - turningSpeed);
    leftMotor.writeMicroseconds(1400 - turningSpeed);
  } else {
    rightMotor.writeMicroseconds(1600 + turningSpeed);
    leftMotor.writeMicroseconds(1600 + turningSpeed);
  }
  
  while(counter != stops) {
    if(digitalRead(leftEncoder) !=  prevState) {
      counter += 1;
      prevState = digitalRead(leftEncoder);
    }
  }
  
  rightMotor.detach();
  leftMotor.detach();
}

