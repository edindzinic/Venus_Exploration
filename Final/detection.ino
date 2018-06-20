int detectCliff() {
  //If 
  
  int inputL, inputR, warn;
  warn = 0;
  inputR = analogRead(PIN_IR_R);
  inputL = analogRead(PIN_IR_L);
  if(inputR<IR_THRESHOLD)
    warn = 1;
  if(inputL<IR_THRESHOLD)
    warn = 2;
  if(inputR<IR_THRESHOLD && inputL<IR_THRESHOLD)
    warn = 4;
  //Serial.print("Left: "); Serial.println(inputL);
  //Serial.print("Right: "); Serial.println(inputR);
  Serial.println(warn);
  return warn;
}

int measureDist(int PIN_SOUND) {
  long duration;
  int cm;

  delay(5);
  //Sensor 0 is bottom, 1 is top
  //Start measurement
  pinMode(PIN_SOUND, OUTPUT);
  digitalWrite(PIN_SOUND, LOW);
  delayMicroseconds(2);
  digitalWrite(PIN_SOUND, HIGH);
  delayMicroseconds(5);
  digitalWrite(PIN_SOUND, LOW);

  //Read result
  pinMode(PIN_SOUND, INPUT);
  duration = pulseIn(PIN_SOUND, HIGH);
  cm = duration / 29 / 2;

  return cm;
}

int measureDistmm(int PIN_SOUND) {
  long duration;
  int cm;

  delay(5);
  //Sensor 0 is bottom, 1 is top
  //Start measurement
  pinMode(PIN_SOUND, OUTPUT);
  digitalWrite(PIN_SOUND, LOW);
  delayMicroseconds(2);
  digitalWrite(PIN_SOUND, HIGH);
  delayMicroseconds(5);
  digitalWrite(PIN_SOUND, LOW);

  //Read result
  pinMode(PIN_SOUND, INPUT);
  duration = 10*pulseIn(PIN_SOUND, HIGH);
  cm = duration / 29 / 2;

  return cm;
}

int stoneDetected() {
  int inputL = 0, inputR = 0, inputF = 0, warn = 0;
  //inputR = analogRead(PIN_IR_R_ROCK);
  //inputL = analogRead(PIN_IR_L_ROCK);
  //inputF = analogRead(PIN_IR_F_ROCK);
  if(inputR>IR_THRESHOLD)
    warn = 1;
  if(inputL>IR_THRESHOLD)
    warn = 2;
  if(inputF>IR_THRESHOLD)
    warn = 3;
  int distance = measureDist(PIN_SOUND_BOTTOM);
  Serial.println(distance);
  if(distance < 15)
  {
    soundServo.write(90);
    delay(50);
    distance -= measureDist(PIN_SOUND_TOP);
    if(abs(distance) > 25)  warn = 4;
  }
  return warn;
}



