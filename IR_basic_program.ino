int rightIR = 1;
int leftIR = 2;
int backIR = 3;

void setup() {
 Serial.begin(9600);
}

void loop() {
  int input, voltage, pin;
  input = analogRead(pin);
  voltage = map(input, 0, 1023, 0, 5000);
  Serial.write(voltage);
  Serial.write("mV \n");
}

int detectCliff(){
  int input, warn;
  if(analogRead(rightIR)<200)
    warn = 1;
  else 
    input = analogRead(leftIR);
  if(input<200)
    warn = 2;
  else if(analogRead(backIR)<200)
    warn = 3;
  else if(input<200 && warn == 1)
    warn = 4;
  else
    warn = 0;
  return warn;
}

