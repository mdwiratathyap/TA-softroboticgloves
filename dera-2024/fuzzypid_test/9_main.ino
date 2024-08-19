void parseCommand() {
    // baca perintah 
    String cmd = Serial.readStringUntil(' ');
    cmd.trim();
    cmd.toLowerCase();
    
    if (cmd == "standby") {
      mode = 0;
    }
    else if (cmd == "reset") {
      mode = 1;
    }
    else if (cmd == "pressa") {
      sp_press = Serial.parseInt();
      mode = 2;
      fuzzypid = false;
    }
    else if (cmd == "pressb") {
      sp_press = Serial.parseInt();
      mode = 2;
      fuzzypid = true;
    }
    else if (cmd == "testpressa") {
      mode = 3;
      fuzzypid = false;
    }
    else if (cmd == "testpressb") {
      mode = 3;
      fuzzypid = true;
    }
    else if (cmd == "anglea") {
      sp_angle = Serial.parseInt();
      mode = 4;
      fuzzypid = false;
    } 
    else if (cmd == "angleb") {
      sp_angle = Serial.parseInt();
      mode = 4;
      fuzzypid = true;
    } 
    else if (cmd == "testanglea") {
      mode = 5;
      fuzzypid = false;
    } 
    else if (cmd == "testangleb") {
      mode = 5;
      fuzzypid = true;
    } 
}

void motorSetup(){
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
}

void valveSetup(){
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
}

void setup() {
  // put your setup code here, to run once:
  Serial.begin(115200);

  // Start ADS
  Wire.begin();
  
  ADS.begin();
  ADS2.begin();
  ADSFR.begin();

  motorSetup();
  valveSetup();
  fuzzySRSetup();
  press_fuzzypidSetup();
  angle_fuzzypidSetup();

  presPID_sup.SetMode(AUTOMATIC);
  presPID_vac.SetMode(AUTOMATIC);
  anglePID_sup.SetMode(AUTOMATIC);
  anglePID_vac.SetMode(AUTOMATIC);
  
  StartTime = millis();
  LastTime = StartTime;
  
  printHeader();
}


void loop(){
  Time = millis();
  if (Serial.available()) {
    parseCommand();
  }
  if (Time - LastTime >= TimeSampling) {
    LastTime = Time;
    pressure = read_pressure();
    angle = read_flex();
    if (mode == 0){
      pwmA = 0;
      pwmB = 0;
      analogWrite(enA, pwmA);
      analogWrite(enB, pwmB);
      digitalWrite(SolValve[0], LOW);
      digitalWrite(SolValve[2], LOW);
      digitalWrite(SolValve[6], LOW);
      digitalWrite(SolValve[7], LOW);
    }
    else if (mode == 1){
      pwmA = 0;
      pwmB = 0;
      analogWrite(enA, pwmA);
      analogWrite(enB, pwmB);
      digitalWrite(SolValve[0], HIGH);
      digitalWrite(SolValve[2], HIGH);
      digitalWrite(SolValve[6], HIGH);
      digitalWrite(SolValve[7], HIGH);
    }
    else if (mode == 2){
      if (sp_press < 0){
        if (fuzzypid == true){
          pressfuzzy_error = sp_press - pressure;
          pressfuzzy_derror = (pressfuzzy_error - pressfuzzy_lasterror)/(TimeSampling);
          pressfuzzy_lasterror = pressfuzzy_error;
          press_fuzzypid->setInput(1, pressfuzzy_error);
          press_fuzzypid->setInput(2, pressfuzzy_derror);
          press_fuzzypid->fuzzify();
          float pid_kp = press_fuzzypid->defuzzify(1);
          float pid_ki = press_fuzzypid->defuzzify(2);
          float pid_kd = press_fuzzypid->defuzzify(3);
  
          Kp2_new = Kp2 + 10*pid_kp;
          Ki2_new = Ki2 + 5*pid_ki;
          Kd2_new = Kd2 + 1*pid_kd;
          presPID_vac.SetTunings(Kp2_new, Ki2_new, Kd2_new);
        } 
        in_press = pressure;
        presPID_vac.Compute();
        mvA = constrain(out_press, 0,100);
        if (mvA > 0){
          mvA = map(mvA, 0.1, 100.0, 50.0, 100.0);
        }
        pwmA = (int) 255*mvA/100;
  
        if (mvA == 0){
          mvB = 100;
        }
        else if (mvA > 0){
          fuzzy_SR->setInput(1, mvA);
          fuzzy_SR->fuzzify();
          mvB = fuzzy_SR->defuzzify(1);
        }
        mvB = constrain(mvB, 75,100);
        pwmB = (int) 255*mvB/100;

        analogWrite(enA, pwmA);
        analogWrite(enB, pwmB);
        digitalWrite(SolValve[0], LOW);
        digitalWrite(SolValve[2], HIGH);
        digitalWrite(SolValve[6], LOW);
        digitalWrite(SolValve[7], HIGH);
      }
      else if (sp_press >=0){
        if (fuzzypid == true){
          pressfuzzy_error = sp_press - pressure;
          pressfuzzy_derror = (pressfuzzy_error - pressfuzzy_lasterror)/(TimeSampling);
          pressfuzzy_lasterror = pressfuzzy_error;
          press_fuzzypid->setInput(1, pressfuzzy_error);
          press_fuzzypid->setInput(2, pressfuzzy_derror);
          press_fuzzypid->fuzzify();
          float pid_kp = press_fuzzypid->defuzzify(1);
          float pid_ki = press_fuzzypid->defuzzify(2);
          float pid_kd = press_fuzzypid->defuzzify(3);
  
          Kp1_new = Kp1 + 5*pid_kp;
          Ki1_new = Ki1 + 1*pid_ki;
          Kd1_new = Kd1 + 1*pid_kd;
          presPID_sup.SetTunings(Kp1_new, Ki1_new, Kd1_new);
        }
        in_press = pressure;
        presPID_sup.Compute();
        mvA = constrain(out_press, 0,100);
        if (mvA > 0){
          mvA = map(mvA, 0.1, 100.0, 50.0, 100.0);
        }
        pwmA = (int) 255*mvA/100;
        pwmA = (int) 255*mvA/100;
        pwmB = 0;
        analogWrite(enA, pwmA);
        analogWrite(enB, pwmB);
        digitalWrite(SolValve[0], HIGH);
        digitalWrite(SolValve[2], HIGH);
        digitalWrite(SolValve[6], HIGH);
        digitalWrite(SolValve[7], LOW);
      }
      Serial.print(sp_press);
      Serial.print("\t");
      Serial.print(pressure);
      Serial.println();
    }
    else if (mode == 3){
//      pressStep();
//      sp_press = pressRamp(ramp_up_period, ramp_down_period, hold_period, min_signal_value, max_signal_value);
      if (sp_press < 0){
        if (fuzzypid == true){
          pressfuzzy_error = sp_press - pressure;
          pressfuzzy_derror = (pressfuzzy_error - pressfuzzy_lasterror)/(TimeSampling);
          pressfuzzy_lasterror = pressfuzzy_error;
          press_fuzzypid->setInput(1, pressfuzzy_error);
          press_fuzzypid->setInput(2, pressfuzzy_derror);
          press_fuzzypid->fuzzify();
          float pid_kp = press_fuzzypid->defuzzify(1);
          float pid_ki = press_fuzzypid->defuzzify(2);
          float pid_kd = press_fuzzypid->defuzzify(3);
  
          Kp2_new = Kp2 + 10*pid_kp;
          Ki2_new = Ki2 + 5*pid_ki;
          Kd2_new = Kd2 + 1*pid_kd;
          presPID_vac.SetTunings(Kp2_new, Ki2_new, Kd2_new);
        } 
        in_press = pressure;
        presPID_vac.Compute();
        mvA = constrain(out_press, 0,100);
        if (mvA > 0){
          mvA = map(mvA, 0.1, 100.0, 50.0, 100.0);
        }
        pwmA = (int) 255*mvA/100;
  
        if (mvA == 0){
          mvB = 100;
        }
        else if (mvA > 0){
          fuzzy_SR->setInput(1, mvA);
          fuzzy_SR->fuzzify();
          mvB = fuzzy_SR->defuzzify(1);
        }
        mvB = constrain(mvB, 70,100);
        pwmB = (int) 255*mvB/100;

        analogWrite(enA, pwmA);
        analogWrite(enB, pwmB);
        digitalWrite(SolValve[0], LOW);
        digitalWrite(SolValve[2], HIGH);
        digitalWrite(SolValve[6], LOW);
        digitalWrite(SolValve[7], HIGH);
      }
      else if (sp_press >=0){
        if (fuzzypid == true){
          pressfuzzy_error = sp_press - pressure;
          pressfuzzy_derror = (pressfuzzy_error - pressfuzzy_lasterror)/(TimeSampling);
          pressfuzzy_lasterror = pressfuzzy_error;
          press_fuzzypid->setInput(1, pressfuzzy_error);
          press_fuzzypid->setInput(2, pressfuzzy_derror);
          press_fuzzypid->fuzzify();
          float pid_kp = press_fuzzypid->defuzzify(1);
          float pid_ki = press_fuzzypid->defuzzify(2);
          float pid_kd = press_fuzzypid->defuzzify(3);
  
          Kp1_new = Kp1 + 5*pid_kp;
          Ki1_new = Ki1 + 1*pid_ki;
          Kd1_new = Kd1 + 1*pid_kd;
          presPID_sup.SetTunings(Kp1_new, Ki1_new, Kd1_new);
        }
        in_press = pressure;
        presPID_sup.Compute();
        mvA = constrain(out_press, 0,100);
        if (mvA > 0){
          mvA = map(mvA, 0.1, 100.0, 50.0, 100.0);
        }
        pwmA = (int) 255*mvA/100;
        pwmA = (int) 255*mvA/100;
        pwmB = 0;
        analogWrite(enA, pwmA);
        analogWrite(enB, pwmB);
        digitalWrite(SolValve[0], HIGH);
        digitalWrite(SolValve[2], HIGH);
        digitalWrite(SolValve[6], HIGH);
        digitalWrite(SolValve[7], LOW);
      }
      Serial.print(Time - StartTime - TimeSampling);
      Serial.print("\t");
      Serial.print(sp_press);
      Serial.print("\t");
      Serial.print(pressure);
      Serial.print("\t");
      Serial.print(angle);
      Serial.print("\t");
      Serial.print(pwmA);
      Serial.print("\t");
      Serial.print(pwmB);
      Serial.print("\t");
      Serial.print(Kp1_new);
      Serial.print("\t");
      Serial.print(Ki1_new);
      Serial.print("\t");
      Serial.print(Kd1_new);
      Serial.print("\t");
      Serial.print(Kp2_new);
      Serial.print("\t");
      Serial.print(Ki2_new);
      Serial.print("\t");
      Serial.print(Kd2_new);
      Serial.print("\t");
      Serial.println();
    }
    else if (mode == 4){
      if (sp_angle < 60){
        if (fuzzypid == true){
          anglefuzzy_error = sp_angle - angle;
          anglefuzzy_derror = (anglefuzzy_error - anglefuzzy_lasterror)/(TimeSampling);
          anglefuzzy_lasterror = anglefuzzy_error;
          angle_fuzzypid->setInput(1, anglefuzzy_error);
          angle_fuzzypid->setInput(2, anglefuzzy_derror);
          angle_fuzzypid->fuzzify();
          float pid_kp = angle_fuzzypid->defuzzify(1);
          float pid_ki = angle_fuzzypid->defuzzify(2);
          float pid_kd = angle_fuzzypid->defuzzify(3);
  
          Kp4_new = Kp4 + 10*pid_kp;
          Ki4_new = Ki4 + 2*pid_ki;
          Kd4_new = Kd4 + 1*pid_kd;
          anglePID_vac.SetTunings(Kp4_new, Ki4_new, Kd4_new);
        }
        in_angle = angle;
        anglePID_vac.Compute();
        mvA = constrain(out_angle, 0,100);
        if (mvA > 0){
          mvA = map(mvA, 0.1, 100.0, 50.0, 100.0);
        }
        pwmA = (int) 255*mvA/100;
  
        if (mvA == 0){
          mvB = 100;
        }
        else if (mvA > 0){
          fuzzy_SR->setInput(1, mvA);
          fuzzy_SR->fuzzify();
          mvB = fuzzy_SR->defuzzify(1);
        }
        mvB = constrain(mvB, 60,100);
        if (mvB <= 75){
          mvB = 0;
        }
        pwmB = (int) 255*mvB/100;

        analogWrite(enA, pwmA);
        analogWrite(enB, pwmB);
        digitalWrite(SolValve[0], LOW);
        digitalWrite(SolValve[2], HIGH);
        digitalWrite(SolValve[6], LOW);
        digitalWrite(SolValve[7], HIGH);
      }
      else if (sp_angle >=60){
        if (fuzzypid == true){
          anglefuzzy_error = sp_angle - angle;
          anglefuzzy_derror = (anglefuzzy_error - anglefuzzy_lasterror)/(TimeSampling);
          anglefuzzy_lasterror = anglefuzzy_error;
          angle_fuzzypid->setInput(1, anglefuzzy_error);
          angle_fuzzypid->setInput(2, anglefuzzy_derror);
          angle_fuzzypid->fuzzify();
          float pid_kp = angle_fuzzypid->defuzzify(1);
          float pid_ki = angle_fuzzypid->defuzzify(2);
          float pid_kd = angle_fuzzypid->defuzzify(3);
  
          Kp3_new = Kp3 + 5*pid_kp;
          Ki3_new = Ki3 + 5*pid_ki;
          Kd3_new = Kd3 + 1*pid_kd;
          anglePID_sup.SetTunings(Kp3_new, Ki3_new, Kd3_new);
        }
        in_angle = angle;
        anglePID_sup.Compute();
        mvA = constrain(out_angle, 0,100);
        if (mvA > 0){
          mvA = map(mvA, 0.1, 100.0, 50.0, 100.0);
        }
        pwmA = (int) 255*mvA/100;
        pwmA = (int) 255*mvA/100;
        pwmB = 0;
        analogWrite(enA, pwmA);
        analogWrite(enB, pwmB);
        digitalWrite(SolValve[0], HIGH);
        digitalWrite(SolValve[2], HIGH);
        digitalWrite(SolValve[6], HIGH);
        digitalWrite(SolValve[7], LOW);
      }
      Serial.print(sp_angle);
      Serial.print("\t");
      Serial.print(angle);
      Serial.println();
    }
    else if (mode == 5){
//      angleStep();
//      sp_angle = angleRamp(ramp_up_period, ramp_down_period, hold_period, min_signal_value, max_signal_value);
      if (sp_angle < 60){
        if (fuzzypid == true){
          anglefuzzy_error = sp_angle - angle;
          anglefuzzy_derror = (anglefuzzy_error - anglefuzzy_lasterror)/(TimeSampling);
          anglefuzzy_lasterror = anglefuzzy_error;
          angle_fuzzypid->setInput(1, anglefuzzy_error);
          angle_fuzzypid->setInput(2, anglefuzzy_derror);
          angle_fuzzypid->fuzzify();
          float pid_kp = angle_fuzzypid->defuzzify(1);
          float pid_ki = angle_fuzzypid->defuzzify(2);
          float pid_kd = angle_fuzzypid->defuzzify(3);
  
          Kp4_new = Kp4 + 5*pid_kp;
          Ki4_new = Ki4 + 3*pid_ki;
          Kd4_new = Kd4 + 1*pid_kd;
          anglePID_vac.SetTunings(Kp4_new, Ki4_new, Kd4_new);
        }
        in_angle = angle;
        anglePID_vac.Compute();
        mvA = constrain(out_angle, 0,100);
        if (mvA > 0){
          mvA = map(mvA, 0.1, 100.0, 50.0, 100.0);
        }
        pwmA = (int) 255*mvA/100;
  
        if (mvA == 0){
          mvB = 100;
        }
        else if (mvA > 0){
          fuzzy_SR->setInput(1, mvA);
          fuzzy_SR->fuzzify();
          mvB = fuzzy_SR->defuzzify(1);
        }
        mvB = constrain(mvB, 60,100);
        if (mvB <= 75){
          mvB = 0;
        }
        pwmB = (int) 255*mvB/100;

        analogWrite(enA, pwmA);
        analogWrite(enB, pwmB);
        digitalWrite(SolValve[0], LOW);
        digitalWrite(SolValve[2], HIGH);
        digitalWrite(SolValve[6], LOW);
        digitalWrite(SolValve[7], HIGH);
      }
      else if (sp_angle >=60){
        if (fuzzypid == true){
          anglefuzzy_error = sp_angle - angle;
          anglefuzzy_derror = (anglefuzzy_error - anglefuzzy_lasterror)/(TimeSampling);
          anglefuzzy_lasterror = anglefuzzy_error;
          angle_fuzzypid->setInput(1, anglefuzzy_error);
          angle_fuzzypid->setInput(2, anglefuzzy_derror);
          angle_fuzzypid->fuzzify();
          float pid_kp = angle_fuzzypid->defuzzify(1);
          float pid_ki = angle_fuzzypid->defuzzify(2);
          float pid_kd = angle_fuzzypid->defuzzify(3);
  
          Kp3_new = Kp3 + 3*pid_kp;
          Ki3_new = Ki3 + 2*pid_ki;
          Kd3_new = Kd3 + 2*pid_kd;
          anglePID_sup.SetTunings(Kp3_new, Ki3_new, Kd3_new);
        }
        in_angle = angle;
        anglePID_sup.Compute();
        mvA = constrain(out_angle, 0,100);
        if (mvA > 0){
          mvA = map(mvA, 0.1, 100.0, 50.0, 100.0);
        }
        pwmA = (int) 255*mvA/100;
        pwmA = (int) 255*mvA/100;
        pwmB = 0;
        analogWrite(enA, pwmA);
        analogWrite(enB, pwmB);
        digitalWrite(SolValve[0], HIGH);
        digitalWrite(SolValve[2], HIGH);
        digitalWrite(SolValve[6], HIGH);
        digitalWrite(SolValve[7], LOW);
      }
      Serial.print(Time - StartTime - TimeSampling);
      Serial.print("\t");
      Serial.print(sp_angle);
      Serial.print("\t");
      Serial.print(pressure);
      Serial.print("\t");
      Serial.print(angle);
      Serial.print("\t");
      Serial.print(pwmA);
      Serial.print("\t");
      Serial.print(pwmB);
      Serial.print("\t");
      Serial.print(Kp3_new);
      Serial.print("\t");
      Serial.print(Ki3_new);
      Serial.print("\t");
      Serial.print(Kd3_new);
      Serial.print("\t");
      Serial.print(Kp4_new);
      Serial.print("\t");
      Serial.print(Ki4_new);
      Serial.print("\t");
      Serial.print(Kd4_new);
      Serial.print("\t");
      Serial.println();
    }
  }
}
