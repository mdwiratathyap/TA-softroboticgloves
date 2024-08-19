#include <PID_v1.h>
//Define Variables we'll be connecting to
double sp_press, in_press, out_press;
double sp_angle, in_angle, out_angle;

//Specify the links and initial tuning parameters
double Kp1=5, Ki1=1, Kd1=2;
double Kp1_new=Kp1, Ki1_new=Ki1, Kd1_new=Kd1;
PID presPID_sup(&in_press, &out_press, &sp_press, Kp1_new, Ki1_new, Kd1_new, DIRECT);

double Kp2=10, Ki2=5, Kd2=1;
double Kp2_new=Kp2, Ki2_new=Ki2, Kd2_new=Kd2;
PID presPID_vac(&in_press, &out_press, &sp_press, Kp2_new, Ki2_new, Kd2_new, DIRECT);

//Specify the links and initial tuning parameters
double Kp3=3, Ki3=2, Kd3=2;
double Kp3_new=Kp3, Ki3_new=Ki3, Kd3_new=Kd3;
PID anglePID_sup(&in_angle, &out_angle, &sp_angle, Kp3_new, Ki3_new, Kd3_new, DIRECT);

double Kp4=5, Ki4=3, Kd4=1;
double Kp4_new=Kp4, Ki4_new=Ki4, Kd4_new=Kd4;
PID anglePID_vac(&in_angle, &out_angle, &sp_angle, Kp4_new, Ki4_new, Kd4_new, DIRECT);
