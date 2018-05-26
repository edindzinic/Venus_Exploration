#include <Servo.h>
#include <EEPROM.h>

// define all states for state machine
#define STATE_CALIBRATION 0
#define STATE_SEARCH 1
#define STATE_GRAB 2
#define STATE_FINDLAB 3
#define STATE_DROP 4

//define pin numbers here
#define PIN_SERVO_GRABBER 10
#define PIN_SOUND_SERVO 11
#define PIN_SOUND 9

#define PIN_ENCODER_LEFT 7
#define PIN_ENCODER_RIGHT 8
#define PIN_MOTOR_LEFT 12
#define PIN_MOTOR_RIGHT 13

#define PIN_IR_R A0
#define PIN_IR_L A1
#define PIN_IR_B A2
#define IR_THRESHOLD 700

#define CALIBRATE_IN 2
#define ANT_WAVEFORM_OUT 4 
#define SPEAKER_FROM_WALKIETALKIE A3 
#define buffering 25

uint16_t caliset = 0;
uint16_t voltage = 0;

Servo grabbingServo;  // create servo object to control a servo; twelve servo objects can be created on most boards
Servo rightMotor;
Servo leftMotor;
Servo soundServo;

int state = STATE_SEARCH;
int prevState = HIGH;
int revolutions = 0;

void setup() {
  analogReference(DEFAULT);
  Serial.begin(9600);
  // pinMode... for all defined pins
  pinMode(PIN_ENCODER_LEFT, INPUT);
  pinMode(PIN_ENCODER_RIGHT, INPUT);
  pinMode(PIN_IR_R, INPUT);
  pinMode(PIN_IR_L, INPUT);
  pinMode(PIN_IR_B, INPUT);
  pinMode(ANT_WAVEFORM_OUT, OUTPUT);
  pinMode(SPEAKER_FROM_WALKIETALKIE, INPUT);
  pinMode(CALIBRATE_IN, INPUT);

  //delay(6000);
  digitalWrite(CALIBRATE_IN, HIGH);
  //read calibration word from EEPROM
  byte HByte =  EEPROM.read(1);
  byte LByte =  EEPROM.read(2);
  caliset = word(HByte, LByte);

  grabbingServo.attach(PIN_SERVO_GRABBER);  // attaches the servo on pin PIN_SERVO_GRABBER to the servo object
  soundServo.attach(PIN_SOUND_SERVO);
}

void loop() {

  if(digitalRead(CALIBRATE_IN) == LOW){
    state = STATE_CALIBRATION;
  }

  switch(state){
    case STATE_CALIBRATION:
      findLab(true);
      break;
    case STATE_SEARCH:
      search();
      break;
    case STATE_GRAB:
      grab();
      break;
    case STATE_FINDLAB:
      findLab(false);
      break;
    case STATE_DROP:
      drop();
      break;
  }

}
