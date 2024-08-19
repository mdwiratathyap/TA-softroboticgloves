void read_pressure(){
  ADS.setGain(0);
  ADS2.setGain(0);
  float dPressOut0 = ADS.readADC(0);
  float dPressOut1 = ADS.readADC(1);
  float dPressOut2 = ADS.readADC(2);

  float dPressOut3 = ADS2.readADC(0);
  float dPressOut4 = ADS2.readADC(1);
  float dPressOutRef = ADS2.readADC(2);

  float Vs = 4.7; // Input Voltage
  // float vPressOut0 = (dPressOut0/32767)*Vs;
  // float vPressOut1 = (dPressOut1/32767)*Vs;
  // float vPressOut2 = (dPressOut2/32767)*Vs;
  // float vPressOut3 = (dPressOut3/32767)*Vs;
  // float vPressOut4 = (dPressOut4/32767)*Vs;

  float f1 = ADS.toVoltage(1);
  float f4 = ADS2.toVoltage(1);

  float vPressOut0 = dPressOut0 * f1;
  float vPressOut1 = dPressOut1 * f1;
  float vPressOut2 = dPressOut2 * f1;
  float vPressOut3 = dPressOut3 * f4;
  float vPressOut4 = dPressOut4 * f4;
  float vPressRef = dPressOutRef * f4;

  float PressureRef = (vPressRef/Vs - 0.04)/0.0012858;
  Pressure[0] = abs((vPressOut0/Vs - 0.04)/0.0012858 - PressureRef); // pinky
  Pressure[1] = abs((vPressOut1/Vs - 0.04)/0.0012858 - PressureRef); // ring
  Pressure[2] = (vPressOut2/Vs - 0.04)/0.0012858 - PressureRef; // middle
  Pressure[3] = (vPressOut3/Vs - 0.04)/0.0012858 - PressureRef; // index
  Pressure[4] = (vPressOut4/Vs - 0.04)/0.0012858 - PressureRef; // thumb
  
  // Serial.print("\tAnalog0: "); Serial.print('\t'); Serial.println(Pressure[0]);
  // Serial.print("\tAnalog1: "); Serial.print('\t'); Serial.println(Pressure[1]); 
  // Serial.print("\tAnalog2: "); Serial.print('\t'); Serial.println(Pressure[2]);
  // Serial.print("\tAnalog3: "); Serial.print('\t'); Serial.println(Pressure[3]);
  // Serial.print("\tAnalog4: "); Serial.print('\t'); Serial.println(Pressure[4]);
  //Serial.print("\tAnalog5: "); Serial.print(dPressOutRef); Serial.print('\t'); Serial.println(PressureRef);
  //Serial.println(); 
  delay(50);

}
