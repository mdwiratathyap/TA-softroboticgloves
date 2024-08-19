double Pressure[5];

float read_pressure(){
  ADS2.setGain(0);

  float dPressOut3 = ADS2.readADC(0);
  float dPressOutRef = ADS2.readADC(2);

  float Vs = 4.7; // Input Voltage

  float f4 = ADS2.toVoltage(1);

  float vPressOut3 = dPressOut3 * f4;
  float vPressRef = dPressOutRef * f4;

  float PressureRef = (vPressRef/Vs - 0.04)/0.0012858;
  Pressure[3] = (vPressOut3/Vs - 0.04)/0.0012858 - PressureRef; // index

  return Pressure[3];
}
