#define vehicleID 1 // or 2 || for communication



void returnToLab(){
  returning = true;
  int turningAngle = 0, oppositeAngle = 0;
  
  calculatePositionVector();
  Serial.print("Position: "); Serial.println(positionAngle);
  
  if(positionAngle >=0 ){
    oppositeAngle = positionAngle - 180;
  }else{
    oppositeAngle = 180 + positionAngle;
  }
  
  Serial.print("Opposite angle: ");Serial.println(oppositeAngle);
  Serial.print("Direction angle: ");Serial.println(directionAngle);
  int rotationAngle = oppositeAngle - directionAngle;
  
  if(rotationAngle > 180){
    rotationAngle = rotationAngle - 360;
  }else if(rotationAngle < -180){
    rotationAngle = rotationAngle + 360;
  }
  
  Serial.print("Rotation angle: ");Serial.println(rotationAngle);
  turnDegrees(rotationAngle, speed1);
  
  float distanceFloat = sqrt(pow(x,2) + pow(y,2));
  distanceFloat = floor(distanceFloat);
  int distance = (int) distanceFloat;
  
  driveStops(distance, speed1);
  returning = false;
  state = STATE_DROP;  
}

void updateAngle(int turningAngle){
  //if greater than 180 or less than -180 then adjust
  if(directionAngle + turningAngle > 180){
    int a = 180 - directionAngle;
    int b = turningAngle - a;
    int c = b - 180;
    directionAngle = c;
  }else if(directionAngle + turningAngle < -180){ 
    int a = 180 + directionAngle;
    int b = abs(a + turningAngle);
    int c = 180 - b;
    directionAngle = c;
  }else{
    directionAngle += turningAngle;
    Serial.print("Direction angle: ");Serial.println(directionAngle);
  }
}

void updatePositionForwards(int distance){
  y += distance*cos(directionAngle*PI / 180.0);
  x += distance*sin(directionAngle*PI / 180.0);
  Serial.print("X, Y: "); Serial.print(x);Serial.print("\t");Serial.println(y);
  
}

void updatePositionBackwards(int distance){
  x += distance*cos(180-directionAngle);
  y += distance*sin(180-directionAngle);
 
}

void calculatePositionVector(){
  float tangentAlpha = x / y;
  float alpha = (atan(tangentAlpha));
  alpha = alpha * 57.2958;
  positionAngle = convertAngle(alpha);
}

float convertAngle(float angle){
  Serial.print("Pos angle: ");Serial.println(angle);
  if(x<0 && y<0){
    return angle - 180;
  }else if(x>0 && y<0){
    return  180 + angle;
  }else{
    return angle;
  }
}


void returnToLab2(){
  Serial.println(directionAngle);
  if(y < 0 && x > -200 && x < 200){
    turnDegrees(-directionAngle, speed1);
    driveStops(abs(y) - 150, speed1);
    state = STATE_DROP;
  }else{
    if(y > 0 && x > -200 && x < 200){
      turnDegrees(-directionAngle-90, speed1);
      driveStops(100, speed1);
    }
    
    if(y < -105){
      turnDegrees(-directionAngle, speed1);
      driveStops(-y - 105, speed1);
    }else if(y >= -105 && x > 0){
      if(directionAngle > 0) {
        turnDegrees(180 - directionAngle, speed1);
      } else {
        turnDegrees(-180 - directionAngle, speed1);
      }
      
                  Serial.println("wrong1");
      driveStops(y+105, speed1);
    }else if(y >= -105 && x < 0){
      if(directionAngle > 0) {
        turnDegrees(180 - directionAngle, speed1);
      } else {
        turnDegrees(-180 - directionAngle, speed1);
      }
                  Serial.println("wrong2");
      driveStops(y+105, speed1);

    }
  
    if(x>0){
      turnDegrees(-directionAngle - 90, speed1);
      driveStops(abs(x) - 200, speed1);
      state = STATE_DROP;
    }else if(x < 0){
      turnDegrees(-directionAngle + 90,speed1);
      driveStops(abs(x) - 200, speed1);
      state = STATE_DROP;
    }

  }
}




