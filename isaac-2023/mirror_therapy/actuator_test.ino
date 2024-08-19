void actuator_test(){
  //digitalWrite(SolValve[6], HIGH);
  digitalWrite(SolValve[0],HIGH);
  digitalWrite(SolValve[1], HIGH);
  //digitalWrite(SolValve[2], HIGH);
  // digitalWrite(SolValve[3], HIGH);
  // digitalWrite(SolValve[4], HIGH);
  // digitalWrite(SolValve[5], HIGH);


  Setpoint[4] = 100;
  //analogWrite(enA, PWM[4]);
  Serial.print(Pressure[4]); Serial.print('\t'); Serial.println(angleR[2]);

}
