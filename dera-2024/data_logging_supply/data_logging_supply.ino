#include <ADS1X15.h>

int SolValve[8] = {28, 30, 32, 34, 36, 38, 40, 42};

// Set motor terminals
int enA = 2;
int enB = 4;

int in1 = 6;
int in2 = 8;

int in3 = 10;
int in4 = 12;

//ADS Addressing
ADS1115 ADS(0x48); // ADS1
ADS1115 ADS2(0x49); // ADS2
ADS1115 ADSFR(0x4B); // Flex right

double Pressure[5];

float dFlexROut[4];
float vFlexROut[4];
float flexR[4];
float angleR[4];

int serial = 0;
int pwm = 0;
int action = 0;
bool start = false;

unsigned long Time, StartTime, LastTime;
unsigned long TimeSampling = 40, DeltaTime;
unsigned long StartTime1, LastTime1;

unsigned long TimeDuration1 = 20000;
unsigned long TimeDuration2 = 35000;
unsigned long TimeDuration3 = 40000;
unsigned long TimeDuration4 = 50000;

unsigned int pwmA = 0;
unsigned int pwmB = 0;

void read_pressure(){
  ADS2.setGain(0);

  float dPressOut3 = ADS2.readADC(0);
  float dPressOutRef = ADS2.readADC(2);

  float Vs = 4.7; // Input Voltage

  float f4 = ADS2.toVoltage(1);

  float vPressOut3 = dPressOut3 * f4;
  float vPressRef = dPressOutRef * f4;

  float PressureRef = (vPressRef/Vs - 0.04)/0.0012858;
  Pressure[3] = (vPressOut3/Vs - 0.04)/0.0012858 - PressureRef - 0.99; // index

  Serial.print(vPressRef);
  Serial.print("\t");
  Serial.print(vPressOut3);
  Serial.print("\t");
  Serial.print(Pressure[3]);
  //Serial.println();
}

void read_flex(){
  // Read ADC 0 = index finger, 3 = pinky finger
  dFlexROut[0] = ADSFR.readADC(0);

  float f_flex = ADSFR.toVoltage(1);

  //calibrate flex sensor
  const float R_DIV = 10000.0; 
  const float STRAIGHT_RESISTANCE = 13070; //14366;//13070.0;
  const float BEND_RESISTANCE = 33000.0;
  const float VCC = 5;

  vFlexROut[0] = dFlexROut[0] * f_flex;

  flexR[0] = R_DIV * (VCC / vFlexROut[0] - 1.0);

//  angleR[0] = map(flexR[0], STRAIGHT_RESISTANCE, BEND_RESISTANCE,0, 90.0);
//  angleR[0] = -299.58*vFlexROut[0]+692.51;

  angleR[0] = (vFlexROut[0]-2.25)*180.0/(1.4-2.25);
  Serial.print(angleR[0]); Serial.print('\t'); //angle
//  Serial.print(flexR[0]); Serial.print('\t');  //Resistance
  Serial.print(vFlexROut[0]); Serial.print('\t'); //volt
  Serial.print(dFlexROut[0]); Serial.print('\t'); //ADC
}

void print_header() {
  Serial.println("Time\tPWMA\tAngle\tVolt\tADC\tVref\tVout\tPress");
}


void setup() {
  // put your setup code here, to run once:
  Serial.begin(115200);

  // Start ADS
  Wire.begin();
  ADS.begin();
  ADS2.begin();
  ADSFR.begin();

  //Set motor pin modes
  pinMode(enA, OUTPUT); //pressure
  pinMode(enB, OUTPUT); //depressure
  pinMode(in1, OUTPUT);
  pinMode(in2, OUTPUT);
  pinMode(in3, OUTPUT);
  pinMode(in4, OUTPUT);

  // Set initial motor state
  digitalWrite(in1, HIGH);
  digitalWrite(in2, LOW);
  digitalWrite(in3, HIGH);
  digitalWrite(in4, LOW);
  
  // Set solenoid pin modes, normally closed (open = high)
  pinMode(SolValve[0], OUTPUT); // exhaust
  pinMode(SolValve[1], OUTPUT); // thumb
  pinMode(SolValve[2], OUTPUT); // index
  pinMode(SolValve[3], OUTPUT); // middle
  pinMode(SolValve[4], OUTPUT); // ring
  //pinMode(SolValve[5], OUTPUT); // pinky
  pinMode(SolValve[6], OUTPUT); // pressurise
  pinMode(SolValve[7], OUTPUT); // depressurise

  digitalWrite(SolValve[0], LOW);
  digitalWrite(SolValve[1], LOW);
  digitalWrite(SolValve[2], LOW);
  digitalWrite(SolValve[3], LOW);
  digitalWrite(SolValve[4], LOW);
  //digitalWrite(SolValve[5], LOW);
  digitalWrite(SolValve[6], LOW);
  digitalWrite(SolValve[7], LOW);

  StartTime = millis();
  LastTime = StartTime;
  
  print_header();
}

void loop() {
  Time = millis();
  LastTime1 = Time;
  
  if (Serial.available()) {
    serial = Serial.parseInt();
    if (serial <= 2){
      action = serial;
      start = false;
    }
    else{
      action = 0;
      pwm = serial;
      StartTime1 = Time;
      start = true;
    }
  }
  if (action == 1){
    pwmA = 0;
    pwmB = 0;
    analogWrite(enA, pwmA);
    analogWrite(enB, pwmB);
    digitalWrite(SolValve[0], LOW);
    digitalWrite(SolValve[2], LOW);
    digitalWrite(SolValve[6], LOW);
    digitalWrite(SolValve[7], LOW);
  }
  if (action == 2){
    pwmA = 0;
    pwmB = 0;
    analogWrite(enA, pwmA);
    analogWrite(enB, pwmB);
    digitalWrite(SolValve[0], HIGH);
    digitalWrite(SolValve[2], HIGH);
    digitalWrite(SolValve[6], HIGH);
    digitalWrite(SolValve[7], HIGH);
  }
  
  if (LastTime1 - StartTime1  < TimeDuration1 and start == true) {
    pwmA = (int) 255*pwm/100;
    pwmB = 0;
    analogWrite(enA, pwmA);
    analogWrite(enB, pwmB);
    digitalWrite(SolValve[0], HIGH);
    digitalWrite(SolValve[2], HIGH);
    digitalWrite(SolValve[6], HIGH);
    digitalWrite(SolValve[7], LOW);
  }
  else if (LastTime1 - StartTime1  < TimeDuration2 and start == true) {
    pwmA = 0;
    pwmB = 0;
    analogWrite(enA, pwmA);
    analogWrite(enB, pwmB);
    digitalWrite(SolValve[0], HIGH);
    digitalWrite(SolValve[2], HIGH);
    digitalWrite(SolValve[6], HIGH);
    digitalWrite(SolValve[7], LOW);
  }
  
  else if (LastTime1 - StartTime1  > TimeDuration2 and start == true) {
    start = false;
  }
  
  if (Time - LastTime >= TimeSampling and start == true) {
    DeltaTime = Time - LastTime;
    LastTime = Time;
    Serial.print(LastTime1 - StartTime1);
    Serial.print("\t");
    Serial.print((int) (100*pwmA/255.0+0.5));
    Serial.print("\t");
    read_flex();
    read_pressure();
    Serial.println();
  }
}
