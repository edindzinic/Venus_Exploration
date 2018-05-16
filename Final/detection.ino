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
