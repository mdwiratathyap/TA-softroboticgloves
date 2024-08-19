void full_hand(){
  if(angleR[3] < 0){
    digitalWrite(SolValve[6], LOW);
    digitalWrite(SolValve[7], HIGH);

    digitalWrite(SolValve[5], HIGH);
    analogWrite(enA, 0);
    analogWrite(enB, PWM[0]);
    }

    else{
      if (Setpoint[0] - Pressure[0] <= -10){

        digitalWrite(SolValve[6], LOW);
        digitalWrite(SolValve[7], HIGH);

        digitalWrite(SolValve[1], HIGH);
        digitalWrite(SolValve[2], HIGH);
        digitalWrite(SolValve[3], HIGH);
        digitalWrite(SolValve[4], HIGH);
        digitalWrite(SolValve[5], HIGH);
        analogWrite(enA, 0);
        analogWrite(enB, PWM[0]);
    }
      else{

        digitalWrite(SolValve[6], HIGH);
        digitalWrite(SolValve[7], LOW);
        
        digitalWrite(SolValve[1], HIGH);
        digitalWrite(SolValve[2], HIGH);
        digitalWrite(SolValve[3], HIGH);
        digitalWrite(SolValve[4], HIGH);
        digitalWrite(SolValve[5], HIGH);
        analogWrite(enA, PWM[0]);
        analogWrite(enB, 0);
      }
    }

  if(PWM[0] < 20){

    digitalWrite(SolValve[1], HIGH);
    digitalWrite(SolValve[2], HIGH);
    digitalWrite(SolValve[3], HIGH);
    digitalWrite(SolValve[4], HIGH);
    digitalWrite(SolValve[5], LOW);
  }
}