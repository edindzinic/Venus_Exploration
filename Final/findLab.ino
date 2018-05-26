void findLab(bool calibration){
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

  	if(calibration){
  		//calibrate
  		delay(6000);
  		caliset = voltage;
    	byte HByte = highByte(caliset);
    	byte LByte = lowByte(caliset);
    	EEPROM.write(1, HByte);
    	EEPROM.write(2, LByte);
    	delay(5000);
    	endCalibration();

  	}else{
  		//search
  		if (voltage > (caliset - buffering) && voltage < (caliset + buffering)) { //drive forward
   		//motor control code for FORWARD here
    	//code for a continuous roating servo is included below
     	//servo1.write(180);
     	//servo2.write(0);
    	Serial.println("Go forward");
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
      	//servo1.write(0);
      	//servo2.write(0);
    	Serial.println("Turn right?");
  	}
  	delay(5); //just a simple wait
  	Serial.print("In, Cal\t");
  	Serial.print(voltage);
  	Serial.print("\t");
  	Serial.println(caliset);
  	}
}

void endCalibration(){
  	Serial.print("Calibrated to: ");
 	Serial.println(caliset);
	
	while(1){
		//end
	}
}
