#include "ADS1X15.h"

// Solenoid valve port assignment
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

//for main process
unsigned long Time, StartTime, LastTime;
unsigned long TimeSampling = 40;

//for testing
unsigned long StartTimeRamp,StartTimeRampStop,StartTimeSinus,StartTimeStep,LastTimeRamp,LastTimeRampStop,LastTimeSinus,LastTimeStep;

unsigned long pwmA = 0;
unsigned long pwmB = 0;
float mvA = 0;
float mvB = 0;
float pressure = 0.0;
float angle = 0.0;
int mode = 0;
bool fuzzypid = false;

void printHeader() {
  Serial.println("Time\tInput\tPress\tAngle\tPWM-A\tPWM-B\tKp1\tKi1\tKd1\tKp2\tKi2\tKd2");
}
