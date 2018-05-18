//Defines (Constants)
#define buffering 25 //what counts as straight ahead? If too small, the robot will jitter. If too large the robot will drive away from the transmitter
//pinout
#define ANT_WAVEFORM_OUT 8 // set output pin
#define SPEAKER_FROM_WALKIETALKIE A1 //set input pin
#define CALIBRATE_IN 11
#define SERVO1pin  9
#define SERVO2pin  10

//Variables
uint16_t caliset = 0;
uint16_t voltage = 0;


//includes
#include <EEPROM.h>
#include <Servo.h> 

Servo servo1;  // Wheel Servo 
Servo servo2;  // Wheel Servo 

//start program
void setup() {
analogReference(DEFAULT);
servo1.attach(SERVO1pin);  // attaches the servos
servo2.attach(SERVO2pin);  
Serial.begin(9600); //begin serial monitor output, remove if you don't want it
delay(6000); // I put this delay here so the robot won't move until the walkie talkie has had time to turn on.
pinMode(ANT_WAVEFORM_OUT, OUTPUT);
pinMode(SPEAKER_FROM_WALKIETALKIE, INPUT);
pinMode(CALIBRATE_IN, INPUT);
digitalWrite(CALIBRATE_IN, HIGH); // enable internal pullup resistor

//read calibration word from EEPROM
byte HByte =  EEPROM.read(1);
byte LByte =  EEPROM.read(2);
caliset = word(HByte, LByte);
Serial.print("EEPROM Calibration number: ");
Serial.print(caliset);
Serial.println(" If you haven't calibrated yet, you need to for it to work");

if (digitalRead(CALIBRATE_IN) == LOW){ // used for calibrating
delay(9000); // a wait so you can back away from the robot while it is calibrating
}
}

void loop(){
digitalWrite(ANT_WAVEFORM_OUT, HIGH);  //output antenna switching waveform
delay(1);
digitalWrite(ANT_WAVEFORM_OUT, LOW);
delay(1);
digitalWrite(ANT_WAVEFORM_OUT, HIGH);
delay(1);
digitalWrite(ANT_WAVEFORM_OUT, LOW);
delay(1);
digitalWrite(ANT_WAVEFORM_OUT, HIGH);
delay(1);
digitalWrite(ANT_WAVEFORM_OUT, LOW);
delay(1);
digitalWrite(ANT_WAVEFORM_OUT, HIGH);
delay(1);
digitalWrite(ANT_WAVEFORM_OUT, LOW);
delay(1);
voltage = analogRead(SPEAKER_FROM_WALKIETALKIE); //read voltage from radio
if (digitalRead(CALIBRATE_IN) == LOW){           //if in calibrate mode, store voltage in EEPROM
caliset = voltage;
byte HByte = highByte(caliset);
byte LByte = lowByte(caliset);
EEPROM.write(1, HByte);
EEPROM.write(2, LByte);
delay(5000);
endprogram();
}

if (voltage > (caliset - buffering) && voltage < (caliset + buffering)) { //drive forward

//motor control code for FORWARD here
//code for a continuous roating servo is included below
servo1.write(180);
servo2.write(0);
}

if (voltage > (caliset + buffering)){ //turn

//motor control code for TURNING here (right or left depends on antenna config.)
//code for a continuous roating servo is included below
servo1.write(180);
servo2.write(180);
}
if (voltage < (caliset - buffering)){  //turn the other way

//motor control code for TURNING the OTHER DIRECTION here (right or left depends on antenna config.)
//code for a continuous roating servo is included below
servo1.write(0);
servo2.write(0);
}
delay(5); //just a simple wait
Serial.print("In, Cal\t");
Serial.print(voltage);
Serial.print("\t");
Serial.println(caliset);
}


void endprogram(){
  Serial.print("Calibrated to: ");
Serial.print(caliset);
  while(1){
    //end
  }
}

