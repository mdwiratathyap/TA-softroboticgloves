float dFlexROut[4];
float vFlexROut[4];
float flexR[4];
float angleR[4];

float read_flex(){
  // Read ADC 0 = index finger, 3 = pinky finger
  dFlexROut[0] = ADSFR.readADC(0);

  float f_flex = ADSFR.toVoltage(1);

  //calibrate flex sensor
  const float R_DIV = 10000.0; 
  const float VCC = 5;

  vFlexROut[0] = dFlexROut[0] * f_flex;
  flexR[0] = R_DIV * (VCC / vFlexROut[0] - 1.0);

//  angleR[0] = -299.58*vFlexROut[0]+692.51;
  angleR[0] = (vFlexROut[0]-2.255)*180.0/(1.4-2.255);

  //Serial.print(angleR[0]); Serial.print('\t'); //angle
  //Serial.print(flexR[0]); Serial.print('\t');  //Resistance
  //Serial.print(vFlexROut[0]); Serial.print('\t'); //volt
  //Serial.print(dFlexROut[0]); Serial.print('\t'); //ADC
  return angleR[0];
}
