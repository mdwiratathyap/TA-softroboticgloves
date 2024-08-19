void read_flex(){

  // Read ADC 0 = index finger, 3 = pinky finger

  dFlexROut[0] = ADSFR.readADC(0);
  dFlexROut[1] = ADSFR.readADC(1);
  dFlexROut[2] = ADSFR.readADC(2);
  dFlexROut[3] = ADSFR.readADC(3);

  float f_flex = ADSFR.toVoltage(1);

  //calibrate flex sensor
  const float R_DIV = 10000.0; 
  const float STRAIGHT_RESISTANCE = 13070; //14366;//13070.0;
  const float BEND_RESISTANCE = 33000.0;
  const float VCC = 5;

  vFlexROut[0] = dFlexROut[0] * f_flex;
  vFlexROut[1] = dFlexROut[1] * f_flex;
  vFlexROut[2] = dFlexROut[2] * f_flex;
  vFlexROut[3] = dFlexROut[3] * f_flex;

  flexR[0] = R_DIV * (VCC / vFlexROut[0] - 1.0);
  flexR[1] = R_DIV * (VCC / vFlexROut[1] - 1.0);
  flexR[2] = R_DIV * (VCC / vFlexROut[2] - 1.0);
  flexR[3] = R_DIV * (VCC / vFlexROut[3] - 1.0);

  angleR[0] = map(flexR[0], STRAIGHT_RESISTANCE, BEND_RESISTANCE,0, 90.0);
  angleR[1] = map(flexR[1], STRAIGHT_RESISTANCE, BEND_RESISTANCE,0, 90.0);
  angleR[2] = map(flexR[2], STRAIGHT_RESISTANCE, BEND_RESISTANCE,0, 90.0); // ring
  angleR[3] = map(flexR[3], STRAIGHT_RESISTANCE, BEND_RESISTANCE,0, 90.0); // pinky

  // Serial.print("\tAnalog0: "); Serial.println(angleR[0]);
  // Serial.print("\tAnalog1: "); Serial.println(angleR[1]);
  // Serial.print(angleR[3]); Serial.print('\t'); Serial.print(angleR[2]); Serial.print('\t'); Serial.println(Pressure[0]);
  //Serial.print("\tAnalog3: "); Serial.println(angleR[3]);
  //Serial.println();
}
