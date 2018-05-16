int detectCliff() {
  int inputL, inputR, inputB, warn;
  warn = 0;
  inputR = analogRead(PIN_IR_R);
  inputL = analogRead(PIN_IR_L);
  inputB = analogRead(PIN_IR_B);
  if(inputR<IR_THRESHOLD)
    warn = 1;
  if(inputL<IR_THRESHOLD)
    warn = 2;
  if(inputR<IR_THRESHOLD && inputL<IR_THRESHOLD)
    warn = 4;
  if(inputB<IR_THRESHOLD)
    warn = 3;
  return warn;
}

int measureDist() {
  long duration;
  int cm;
  
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

