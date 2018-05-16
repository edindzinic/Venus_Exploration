/* Sweep
 by BARRAGAN <http://barraganstudio.com>
 This example code is in the public domain.

 modified 8 Nov 2013
 by Scott Fitzgerald
 http://www.arduino.cc/en/Tutorial/Sweep
*/

#include <Servo.h>

#define grabbingServoPin 10

Servo grabbingServo;  // create servo object to control a servo
// twelve servo objects can be created on most boards

void setup() {
  grabbingServo.attach(grabbingServoPin);  // attaches the servo on pin 9 to the servo object
  
}

void loop() {
  openGrabber();
  delay(1000);
  closeGrabber();
  delay(1000);
  //sweepServo();
}

void openGrabber() {
  grabbingServo.write(180);
}

void closeGrabber() {
  grabbingServo.write(0);
}

void sweepServo() {
  int pos = 0;    // variable to store the servo position
  for (pos = 0; pos <= 180; pos += 1) { // goes from 0 degrees to 180 degrees
    // in steps of 1 degree
    grabbingServo.write(pos);              // tell servo to go to position in variable 'pos'
    delay(5);                       // waits 15ms for the servo to reach the position
  }
  for (pos = 180; pos >= 0; pos -= 1) { // goes from 180 degrees to 0 degrees
    grabbingServo.write(pos);              // tell servo to go to position in variable 'pos'
    delay(5);                       // waits 15ms for the servo to reach the position
  }
}


