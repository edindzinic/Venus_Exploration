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
#define PIN_ENCODER_LEFT 7
#define PIN_ENCODER_RIGHT 8
#define PIN_MOTOR_LEFT 12
#define PIN_MOTOR_RIGHT 13

#define PIN_IR_R A0
#define PIN_IR_L A1
#define PIN_IR_B A2
#define IR_THRESHOLD 700

Servo grabbingServo;  // create servo object to control a servo; twelve servo objects can be created on most boards
Servo rightMotor;
Servo leftMotor;
Servo soundServo;

int state = STATE_SEARCH;
int prevState = HIGH;
int revolutions = 0;

void setup() {
  // pinMode... for all defined pins
  pinMode(PIN_ENCODER_LEFT, INPUT);
  pinMode(PIN_ENCODER_RIGHT, INPUT);
  pinMode(PIN_IR_R, INPUT);
  pinMode(PIN_IR_L, INPUT);
  pinMode(PIN_IR_B, INPUT);
  
  grabbingServo.attach(PIN_SERVO_GRABBER);  // attaches the servo on pin PIN_SERVO_GRABBER to the servo object


  Serial.begin(9600);

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
