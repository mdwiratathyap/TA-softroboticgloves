void motor_control(){
    // ring
    // if(angleR[2] < 0){
    //   Setpoint[1] = abs(map(angleR[2], 0, 10, 0, 100));
    // }
    // else{
    //   Setpoint[1] = abs(map(angleR[2], 0, 130, 0, 100));
    // }
    
    if (mode == 0){
      if(angleR[3] < 0){
        Setpoint[0] = abs(map(angleR[3], 0, 10, 0, 60));
      }
      else{
        Setpoint[0] = abs(map(angleR[3], 0, 130, 0, 60));
      }
      full_hand();
    }

    if (mode == 1){
      Setpoint[0] = 60;
      Setpoint[1] = 60;
      Setpoint[2] = 60;
      Setpoint[3] = 60;
      Setpoint[4] = 60;

      sequential();
    }

  }

