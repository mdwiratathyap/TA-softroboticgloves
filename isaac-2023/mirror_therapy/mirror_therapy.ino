#include "ADS1X15.h"
#include <PID_v1.h>

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

// Solenoid valve port assignment

int SolValve[8] = {28, 30, 32, 34, 36, 38, 40, 42};


// PID variable declarations

double Pressure[5];

float dFlexROut[4];
float vFlexROut[4];
float flexR[4];
float angleR[4];

// declare PWMs

double PWM[5];

double Kp = 55;
double Ki = 1;
double Kd = 1;

double Setpoint[5];

// PID Loop declarations
PID pid0(&Pressure[0], &PWM[0], &Setpoint[0], Kp, Ki, Kd, DIRECT); // pinky
PID pid1(&Pressure[1], &PWM[1], &Setpoint[1], Kp, Ki, Kd, DIRECT); // ring
PID pid2(&Pressure[2], &PWM[2], &Setpoint[2], Kp, Ki, Kd, DIRECT); // middle
PID pid3(&Pressure[3], &PWM[3], &Setpoint[3], Kp, Ki, Kd, DIRECT); // index
PID pid4(&Pressure[4], &PWM[4], &Setpoint[4], Kp, Ki, Kd, DIRECT); // thumb

unsigned long previousMillis = 0;

int mode = 0;
int status = 0;

int current_finger = 0;
int current_valve = 5;
void setup() 
{
  Serial.begin(9600);

  // Start ADS
  ADS.begin();
  ADS2.begin();
  ADSFR.begin();

  //Set motor pin modes
  pinMode(enA, OUTPUT);
	pinMode(enB, OUTPUT);
	pinMode(in1, OUTPUT);
	pinMode(in2, OUTPUT);
	pinMode(in3, OUTPUT);
	pinMode(in4, OUTPUT);

  // Set initial motor state

  digitalWrite(in1, HIGH);
  digitalWrite(in2, LOW);

  digitalWrite(in3, HIGH);
  digitalWrite(in4, LOW);
  // Set solenoid pin modes
  pinMode(SolValve[0], OUTPUT); // exhaust
  pinMode(SolValve[1], OUTPUT); // thumb
  pinMode(SolValve[2], OUTPUT); // index
  pinMode(SolValve[3], OUTPUT); // middle
  pinMode(SolValve[4], OUTPUT); // ring
  pinMode(SolValve[5], OUTPUT); // pinky
  pinMode(SolValve[6], OUTPUT); // pressurise
  pinMode(SolValve[7], OUTPUT); // depressurise

  //Turn PID on
  pid0.SetMode(AUTOMATIC);
  pid1.SetMode(AUTOMATIC);
  pid2.SetMode(AUTOMATIC);
  pid3.SetMode(AUTOMATIC);
  pid4.SetMode(AUTOMATIC);

  // Set Limits
//   pid0.SetOutputLimits(0, 255);
//   pid1.SetOutputLimits(0, 255);
//   pid2.SetOutputLimits(0, 255);
//   pid3.SetOutputLimits(0, 255);
//   pid4.SetOutputLimits(0, 255);
}
 
void loop() {
  read_pressure();
  motor_control();
  // Compute PID values
  pid0.Compute();
  pid1.Compute();
  pid2.Compute();
  pid3.Compute();
  pid4.Compute();
  read_flex();
  //actuator_test();

}
