void sequential(){

  int currentMillis = millis();
  int period = 5000;

  if (status == 0){
    if (angleR[3] >= 50){
        digitalWrite(SolValve[6], HIGH);
        digitalWrite(SolValve[7], LOW);

        digitalWrite(SolValve[current_valve], HIGH);

        if (current_finger > 0){
          digitalWrite(SolValve[0], LOW);
        }

        analogWrite(enA, PWM[current_finger]);
        analogWrite(enB, 0);
      
    }
    if(angleR[3] < 50 && currentMillis - previousMillis >= period){
      previousMillis = currentMillis;
      digitalWrite(SolValve[current_valve], LOW);
      status = 1;
      Serial.println(currentMillis - previousMillis);
    }
  }

  if (status == 1){

    digitalWrite(SolValve[6], LOW);
    digitalWrite(SolValve[7], HIGH);

    digitalWrite(SolValve[current_valve], HIGH);
    analogWrite(enA, 0);
    analogWrite(enB, PWM[current_finger]);

    if(currentMillis - previousMillis >= period){
      previousMillis = currentMillis;
      digitalWrite(SolValve[current_valve], LOW);

      status = 0;

      current_finger += 1;
      current_valve -=1;

      if(current_finger == 5){
        current_finger = 0;
        current_valve = 5;
      }
      

      Serial.println(current_finger);
      Serial.println(current_valve);
      Serial.println(status);
      Serial.println();

    }
  }
}