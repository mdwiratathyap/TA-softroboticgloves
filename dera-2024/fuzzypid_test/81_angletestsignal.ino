////CTRL+A THEN UNCOMMENT (CTRL+/) IF YOU WILL TEST ANGLE CONTROL
////FOR STEP SIGNAL, UNCOMMENT ONE TESTING MODE, THEN COMMENT OTHERS
////IN MAIN TAB, COMMENT / UNCOMMENT THE SUITABLE TESTER FUNCTION IN MAIN LOOP
////IF FINISHED AND WANT TO TEST PRESSURE CONTROL, CTRL+A THEN COMMENT (CTRL+/) THIS SECTION
//
////STEP UP SIGNAL TESTER (FLEXION)
//int modestep_angle = true;
//void angleStep(){
//  if (modestep_angle == true){
//    StartTimeStep = millis();
//    modestep_angle = false;
//  }
//  LastTimeStep = millis();
//  unsigned long TimeDuration0 = 10000;
//  unsigned long TimeDuration1 = 20000;
//  unsigned long TimeDuration2 = 30000;
//  unsigned long TimeDuration3 = 40000;
//  unsigned long TimeDuration4 = 50000;
//  unsigned long TimeDuration5 = 60000;
//  unsigned long TimeDuration6 = 70000;
//
//  if (LastTimeStep - StartTimeStep  < TimeDuration0) {
//    sp_angle = 60;
//  }
//  else if (LastTimeStep - StartTimeStep  < TimeDuration1) {
//    sp_angle = 75;
//  }
//  else if (LastTimeStep - StartTimeStep  < TimeDuration2) {
//    sp_angle = 90;
//  }
//  else if (LastTimeStep - StartTimeStep  < TimeDuration3) {
//    sp_angle = 105;
//  }
//  else if (LastTimeStep - StartTimeStep  < TimeDuration4) {
//    sp_angle = 90;
//  }
//  else if (LastTimeStep - StartTimeStep  < TimeDuration5) {
//    sp_angle = 75;
//  }
//  else if (LastTimeStep - StartTimeStep  < TimeDuration6) {
//    sp_angle = 60;
//  }
//  else if (LastTimeStep - StartTimeStep  > TimeDuration6) {
//    mode = 1;
//  }
//}
//
//////UNIT STEP SIGNAL TESTER (FLEXION)
////int modestep_angle = true;
////void angleStep(){
////  if (modestep_angle == true){
////    StartTimeStep = millis();
////    modestep_angle = false;
////  }
////  LastTimeStep = millis();
////  unsigned long TimeDuration0 = 10000;
////  unsigned long TimeDuration1 = 20000;
////  unsigned long TimeDuration2 = 30000;
////
////  if (LastTimeStep - StartTimeStep  < TimeDuration0) {
////    sp_angle = 60;
////  }
////  else if (LastTimeStep - StartTimeStep  < TimeDuration1) {
////    sp_angle = 85;
////  }
////  else if (LastTimeStep - StartTimeStep  < TimeDuration2) {
////    sp_angle = 85;
////  }
////  else if (LastTimeStep - StartTimeStep  > TimeDuration2) {
////    mode = 1;
////  }
////}
//
//////STEP UP SIGNAL TESTER (EXTENSION)
////int modestep_angle = true;
////void angleStep(){
////  if (modestep_angle == true){
////    StartTimeStep = millis();
////    modestep_angle = false;
////  }
////  LastTimeStep = millis();
////  unsigned long TimeDuration0 = 10000;
////  unsigned long TimeDuration1 = 20000;
////  unsigned long TimeDuration2 = 30000;
////  unsigned long TimeDuration3 = 40000;
////  unsigned long TimeDuration4 = 50000;
////  unsigned long TimeDuration5 = 60000;
////  unsigned long TimeDuration6 = 70000;
////  unsigned long TimeDuration7 = 80000;
////
////  if (LastTimeStep - StartTimeStep  < TimeDuration0) {
////    sp_angle = 0;
////  }
////  else if (LastTimeStep - StartTimeStep  < TimeDuration1) {
////    sp_angle = 0;
////  }
////  else if (LastTimeStep - StartTimeStep  < TimeDuration2) {
////    sp_angle = 15;
////  }
////  else if (LastTimeStep - StartTimeStep  < TimeDuration3) {
////    sp_angle = 30;
////  }
////  else if (LastTimeStep - StartTimeStep  < TimeDuration4) {
////    sp_angle = 45;
////  }
////  else if (LastTimeStep - StartTimeStep  < TimeDuration5) {
////    sp_angle = 30;
////  }
////  else if (LastTimeStep - StartTimeStep  < TimeDuration6) {
////    sp_angle = 15;
////  }
////  else if (LastTimeStep - StartTimeStep  < TimeDuration7) {
////    sp_angle = 0;
////  }
////  else if (LastTimeStep - StartTimeStep  > TimeDuration7) {
////    mode = 1;
////  }
////}
//
//////UNIT STEP SIGNAL TESTER (EXTENSION)
////int modestep_angle = true;
////void angleStep(){
////  if (modestep_angle == true){
////    StartTimeStep = millis();
////    modestep_angle = false;
////  }
////  LastTimeStep = millis();
////  unsigned long TimeDuration0 = 10000;
////  unsigned long TimeDuration1 = 20000;
////  unsigned long TimeDuration2 = 30000;
////  unsigned long TimeDuration3 = 40000;
////
////  if (LastTimeStep - StartTimeStep  < TimeDuration0) {
////    sp_angle = 0;
////  }
////  else if (LastTimeStep - StartTimeStep  < TimeDuration1) {
////    sp_angle = 0;
////  }
////  else if (LastTimeStep - StartTimeStep  < TimeDuration2) {
////    sp_angle = 30;
////  }
////  else if (LastTimeStep - StartTimeStep  < TimeDuration3) {
////    sp_angle = 30;
////  }
////  else if (LastTimeStep - StartTimeStep  > TimeDuration3) {
////    mode = 1;
////  }
////}
//
//// RAMP SIGNAL TESTER
//const int min_signal_value = 0; // Minimum value of the signal
//const int max_signal_value = 105; // Maximum value of the signal
//const unsigned long ramp_up_period = 15000; // Duration of the ramp-up in milliseconds (3 seconds)
//const unsigned long ramp_down_period = 15000; // Duration of the ramp-down in milliseconds (2 seconds)
//const unsigned long hold_period = 15000; // Duration to hold the max and min values in milliseconds (1 second)
//
////unsigned long start_time; // Start time of the signal generation
//unsigned long hold_start_time; // Start time of the holding period
//bool holding = true; // Start with holding at the minimum value
//bool ramping_up = true; // Indicates the direction of the ramp (true for up, false for down)
//bool at_max = false; // Indicates whether the signal is at max value
//
//int moderamp_angle = true;
//float angleRamp(unsigned long ramp_up_period, unsigned long ramp_down_period, unsigned long hold_period, int min_value, int max_value) {
//  if (moderamp_angle == true){
//    StartTimeRamp = millis();
//    StartTimeRampStop = millis();
//    hold_start_time = StartTimeRamp;
//    moderamp_angle = false;
//  }
//
//  LastTimeRamp = millis();
//  LastTimeRampStop = millis();
//  float signal_value;
//
//  if (holding) {
//    // During the holding period, keep the signal at the max or min value
//    signal_value = at_max ? max_value : min_value;
//
//    if (LastTimeRamp - hold_start_time >= hold_period) {
//      // End of the holding period
//      holding = false;
//      StartTimeRamp = LastTimeRamp; // Reset the start time for the next ramp
//    }
//  } else {
//    unsigned long elapsed_time = LastTimeRamp - StartTimeRamp; // Calculate elapsed time
//
//    if (ramping_up) {
//      // Calculate the normalized time within the ramp-up period (0 to 1)
//      float normalized_time = (float)elapsed_time / (float)ramp_up_period;
//
//      if (normalized_time >= 1.0) {
//        signal_value = max_value; // Ensure exact maximum value
//        holding = true; // Start holding period
//        hold_start_time = LastTimeRamp; // Record the start time of the holding period
//        at_max = true;
//        ramping_up = false; // Switch direction after reaching max
//      } else {
//        // Calculate the linear ramp signal for ramp-up
//        signal_value = min_value + (max_value - min_value) * normalized_time;
//      }
//    } else {
//      // Calculate the normalized time within the ramp-down period (0 to 1)
//      float normalized_time = (float)elapsed_time / (float)ramp_down_period;
//
//      if (normalized_time >= 1.0) {
//        signal_value = min_value; // Ensure exact minimum value
//        holding = true; // Start holding period
//        hold_start_time = LastTimeRamp; // Record the start time of the holding period
//        at_max = false;
//        ramping_up = true; // Switch direction after reaching min
//      } else {
//        // Calculate the linear ramp signal for ramp-down
//        signal_value = max_value - (max_value - min_value) * normalized_time;
//      }
//    }
//  }
//
//  if (LastTimeRampStop - StartTimeRampStop  > 120000) {
//    mode = 1;
//  }
//
//  return signal_value;
//}
