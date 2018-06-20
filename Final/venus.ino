#include <Servo.h>

// define all states for state machine
#define STATE_SEARCH 0
#define STATE_GRAB 1
#define STATE_FINDLAB 2
#define STATE_DROP 3

/*
define pin numbers here
 */
#define PIN_SERVO_GRABBER 10
#define PIN_SOUND_SERVO 11
#define PIN_SOUND_TOP 9
#define PIN_SOUND_BOTTOM 6

#define PIN_ENCODER_LEFT 7
#define PIN_ENCODER_RIGHT 8
#define PIN_MOTOR_LEFT 12
#define PIN_MOTOR_RIGHT 13

#define PIN_IR_R A0
#define PIN_IR_L A1
//#define PIN_IR_B A2
#define PIN_IR_R_ROCK A2
#define PIN_IR_L_ROCK A3
#define PIN_IR_F_ROCK A4
#define IR_THRESHOLD 400

#define PIN_GRAB_DETECT 5

Servo grabbingServo;  // create servo object to control a servo; twelve servo objects can be created on most boards
Servo rightMotor;
Servo leftMotor;
Servo soundServo;

int state = STATE_SEARCH;
int prevState = HIGH;
int revolutions = 0;
volatile int counter2 = 0;
volatile int totalCounter = 0;
//false is backwards, true is forward
bool direction2 = true;
bool driving = false;

//backtracking
float x = 0.0;
float y = 0.0;
int directionAngle = 0;
int positionAngle = 0;
int speed1 = 20; // nvm
int aprox = 5;
bool returning = false;

void setup() {
  // pinMode... for all defined pins
  pinMode(PIN_ENCODER_LEFT, INPUT);
  pinMode(PIN_ENCODER_RIGHT, INPUT);
  pinMode(PIN_IR_R, INPUT);
  pinMode(PIN_IR_L, INPUT);
  pinMode(PIN_IR_R_ROCK, INPUT);
  pinMode(PIN_IR_L_ROCK, INPUT);
  pinMode(PIN_IR_F_ROCK, INPUT);
  pinMode(PIN_GRAB_DETECT, INPUT_PULLUP);
  
  grabbingServo.attach(PIN_SERVO_GRABBER);  // attaches the servo on pin PIN_SERVO_GRABBER to the servo object
  soundServo.attach(PIN_SOUND_SERVO);

  rightMotor.attach(PIN_MOTOR_RIGHT);
  leftMotor.attach(PIN_MOTOR_LEFT);
  stopMotors();

  Serial.begin(9600);
  grabbingServo.write(100);
  delay(1000);

  attachInterrupt(digitalPinToInterrupt(2), interruptCounter, CHANGE);
  /*driveStops(50,20);
  turnDegrees(-90,20);
  driveStops(200,20);
  turnDegrees(-60,20);
  driveStops(150,20);
  turnDegrees(-60,20);
  driveStops(150,20);
  //turnDegrees(20,20);
  returnToLab2();*/
  


  
  drop();

}

void interruptCounter() {
  counter2+=1;
}

void loop() {
  switch(state){
    case STATE_SEARCH:
      search();
      break;
    case STATE_GRAB:
      grab();
      break;
    case STATE_FINDLAB:
      findLab();
      break;
    case STATE_DROP:
      drop();
      break;
  }
}
