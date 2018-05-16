int pingPin = 9;

void setup() {
  Serial.begin(9600);
}

void loop() {
  int warn;
  warn = measureDist();

  Serial.write(warn);
  Serial.write("\n");
}

int measureDist() {
  long duration, cm, warn;
  
  //Start measurement
  pinMode(pingPin, OUTPUT);
  digitalWrite(pingPin, LOW);
  delayMicroseconds(2);
  digitalWrite(pingPin, HIGH);
  delayMicroseconds(5);
  digitalWrite(pingPin, LOW);

  //Read result
  pinMode(pingPin, INPUT);
  duration = pulseIn(pingPin, HIGH);
  cm = duration / 29 / 2;
  
  //Serial.print(cm);
  //Serial.print("cm \n");

 if(cm < 20)
  warn = 1;
 else
  warn = 0;
 return warn;
}

