//CTRL+A THEN UNCOMMENT (CTRL+/) IF YOU WILL TEST PRESSURE CONTROL
//FOR STEP SIGNAL, UNCOMMENT ONE TESTING MODE, THEN COMMENT OTHERS
//IN MAIN TAB, COMMENT / UNCOMMENT THE SUITABLE TESTER FUNCTION IN MAIN LOOP
//IF FINISHED AND WANT TO TEST ANGLE CONTROL, CTRL+A THEN COMMENT (CTRL+/) THIS SECTION

//STEP UP SIGNAL TESTER (POSITIVE)
int modestep_press = true;
void pressStep(){
  if (modestep_press == true){
    StartTimeStep = millis();
    modestep_press = false;
  }
  LastTimeStep = millis();
  unsigned long TimeDuration0 = 10000;
  unsigned long TimeDuration1 = 20000;
  unsigned long TimeDuration2 = 30000;
  unsigned long TimeDuration3 = 40000;
  unsigned long TimeDuration4 = 50000;
  unsigned long TimeDuration5 = 60000;
  unsigned long TimeDuration6 = 70000;
  unsigned long TimeDuration7 = 80000;
  unsigned long TimeDuration8 = 90000;

  if (LastTimeStep - StartTimeStep  < TimeDuration0) {
    sp_press = 0;
  }
  else if (LastTimeStep - StartTimeStep  < TimeDuration1) {
    sp_press = 25;
  }
  else if (LastTimeStep - StartTimeStep  < TimeDuration2) {
    sp_press = 50;
  }
  else if (LastTimeStep - StartTimeStep  < TimeDuration3) {
    sp_press = 75;
  }
  else if (LastTimeStep - StartTimeStep  < TimeDuration4) {
    sp_press = 100;
  }
  else if (LastTimeStep - StartTimeStep  < TimeDuration5) {
    sp_press = 75;
  }
  else if (LastTimeStep - StartTimeStep  < TimeDuration6) {
    sp_press = 50;
  }
  else if (LastTimeStep - StartTimeStep  < TimeDuration7) {
    sp_press = 25;
  }
  else if (LastTimeStep - StartTimeStep  < TimeDuration8) {
    sp_press = 0;
  }
  else if (LastTimeStep - StartTimeStep  > TimeDuration8) {
    mode = 1;
  }
}

////UNIT STEP SIGNAL TESTER (POSITIVE)
//int modestep_press = true;
//void pressStep(){
//  if (modestep_press == true){
//    StartTimeStep = millis();
//    modestep_press = false;
//  }
//  LastTimeStep = millis();
//  unsigned long TimeDuration0 = 10000;
//  unsigned long TimeDuration1 = 20000;
//  unsigned long TimeDuration2 = 30000;
//
//  if (LastTimeStep - StartTimeStep  < TimeDuration0) {
//    sp_press = 0;
//  }
//  else if (LastTimeStep - StartTimeStep  < TimeDuration1) {
//    sp_press = 60;
//  }
//  else if (LastTimeStep - StartTimeStep  < TimeDuration2) {
//    sp_press = 60;
//  }
//  else if (LastTimeStep - StartTimeStep  > TimeDuration2) {
//    mode = 1;
//  }
//}

////STEP UP SIGNAL TESTER (NEGATIVE)
//int modestep_press = true;
//void pressStep(){
//  if (modestep_press == true){
//    StartTimeStep = millis();
//    modestep_press = false;
//  }
//  LastTimeStep = millis();
//  unsigned long TimeDuration0 = 20000;
//  unsigned long TimeDuration1 = 30000;
//  unsigned long TimeDuration2 = 40000;
//  unsigned long TimeDuration3 = 50000;
//  unsigned long TimeDuration4 = 60000;
//  unsigned long TimeDuration5 = 70000;
//  unsigned long TimeDuration6 = 80000;
//
//  if (LastTimeStep - StartTimeStep  < TimeDuration0) {
//    sp_press = -50;
//  }
//  else if (LastTimeStep - StartTimeStep  < TimeDuration1) {
//    sp_press = -35;
//  }
//  else if (LastTimeStep - StartTimeStep  < TimeDuration2) {
//    sp_press = -20;
//  }
//  else if (LastTimeStep - StartTimeStep  < TimeDuration3) {
//    sp_press = -5;
//  }
//  else if (LastTimeStep - StartTimeStep  < TimeDuration4) {
//    sp_press = -20;
//  }
//  else if (LastTimeStep - StartTimeStep  < TimeDuration5) {
//    sp_press = -35;
//  }
//  else if (LastTimeStep - StartTimeStep  < TimeDuration6) {
//    sp_press = -50;
//  }
//  else if (LastTimeStep - StartTimeStep  > TimeDuration6) {
//    mode = 1;
//  }
//}

////UNIT STEP SIGNAL TESTER (NEGATIVE)
//int modestep_press = true;
//void pressStep(){
//  if (modestep_press == true){
//    StartTimeStep = millis();
//    modestep_press = false;
//  }
//  LastTimeStep = millis();
//  unsigned long TimeDuration0 = 10000;
//  unsigned long TimeDuration1 = 20000;
//  unsigned long TimeDuration2 = 30000;
//  unsigned long TimeDuration3 = 40000;
//
//  if (LastTimeStep - StartTimeStep  < TimeDuration0) {
//    sp_press = -50;
//  }
//  else if (LastTimeStep - StartTimeStep  < TimeDuration1) {
//    sp_press = -50;
//  }
//  else if (LastTimeStep - StartTimeStep  < TimeDuration2) {
//    sp_press = -25;
//  }
//  else if (LastTimeStep - StartTimeStep  < TimeDuration3) {
//    sp_press = -25;
//  }
//  else if (LastTimeStep - StartTimeStep  > TimeDuration3) {
//    mode = 1;
//  }
//}

// RAMP SIGNAL TESTER
const int min_signal_value = -50; // Minimum value of the signal
const int max_signal_value = 100; // Maximum value of the signal
const unsigned long ramp_up_period = 10000; // Duration of the ramp-up in milliseconds (3 seconds)
const unsigned long ramp_down_period = 10000; // Duration of the ramp-down in milliseconds (2 seconds)
const unsigned long hold_period = 10000; // Duration to hold the max and min values in milliseconds (1 second)

//unsigned long start_time; // Start time of the signal generation
unsigned long hold_start_time; // Start time of the holding period
bool holding = true; // Start with holding at the minimum value
bool ramping_up = true; // Indicates the direction of the ramp (true for up, false for down)
bool at_max = false; // Indicates whether the signal is at max value

int moderamp_press = true;
float pressRamp(unsigned long ramp_up_period, unsigned long ramp_down_period, unsigned long hold_period, int min_value, int max_value) {
  if (moderamp_press == true){
    StartTimeRamp = millis();
    StartTimeRampStop = millis();
    hold_start_time = StartTimeRamp;
    moderamp_press = false;
  }

  LastTimeRamp = millis();
  LastTimeRampStop = millis();
  float signal_value;

  if (holding) {
    // During the holding period, keep the signal at the max or min value
    signal_value = at_max ? max_value : min_value;

    if (LastTimeRamp - hold_start_time >= hold_period) {
      // End of the holding period
      holding = false;
      StartTimeRamp = LastTimeRamp; // Reset the start time for the next ramp
    }
  } else {
    unsigned long elapsed_time = LastTimeRamp - StartTimeRamp; // Calculate elapsed time

    if (ramping_up) {
      // Calculate the normalized time within the ramp-up period (0 to 1)
      float normalized_time = (float)elapsed_time / (float)ramp_up_period;

      if (normalized_time >= 1.0) {
        signal_value = max_value; // Ensure exact maximum value
        holding = true; // Start holding period
        hold_start_time = LastTimeRamp; // Record the start time of the holding period
        at_max = true;
        ramping_up = false; // Switch direction after reaching max
      } else {
        // Calculate the linear ramp signal for ramp-up
        signal_value = min_value + (max_value - min_value) * normalized_time;
      }
    } else {
      // Calculate the normalized time within the ramp-down period (0 to 1)
      float normalized_time = (float)elapsed_time / (float)ramp_down_period;

      if (normalized_time >= 1.0) {
        signal_value = min_value; // Ensure exact minimum value
        holding = true; // Start holding period
        hold_start_time = LastTimeRamp; // Record the start time of the holding period
        at_max = false;
        ramping_up = true; // Switch direction after reaching min
      } else {
        // Calculate the linear ramp signal for ramp-down
        signal_value = max_value - (max_value - min_value) * normalized_time;
      }
    }
  }

  if (LastTimeRampStop - StartTimeRampStop  > 120000) {
    mode = 1;
  }

  return signal_value;
}
