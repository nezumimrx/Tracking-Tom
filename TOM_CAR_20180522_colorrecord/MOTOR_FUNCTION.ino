
void M_forward() {
  analogWrite(PWMA1, Mspeed);
  analogWrite(PWMA2, 0);
  analogWrite(PWMB1, Mspeed);
  analogWrite(PWMB2, 0);
}

void M_backward() {
  analogWrite(PWMA1, 0);
  analogWrite(PWMA2, Mspeed);
  analogWrite(PWMB1, 0);
  analogWrite(PWMB2, Mspeed);
}

void M_left_slow() {
  analogWrite(PWMA1, int(Mspeed / 2));
  analogWrite(PWMA2, 0);
  analogWrite(PWMB1, int(Mspeed));
  analogWrite(PWMB2, 0);
}

void M_back_left_slow() {
  analogWrite(PWMA1, 0);
  analogWrite(PWMA2, int(Mspeed));
  analogWrite(PWMB1, 0);
  analogWrite(PWMB2, int(Mspeed / 2));

}

void M_right_slow() {
  analogWrite(PWMA1, Mspeed);
  analogWrite(PWMA2, 0);
  analogWrite(PWMB1, int(Mspeed / 2));
  analogWrite(PWMB2, 0);
}

void M_back_slow() {
  analogWrite(PWMA1, 0);
  analogWrite(PWMA2, int(Mspeed / 2));
  analogWrite(PWMB1, 0);
  analogWrite(PWMB2, Mspeed);
}

void M_left_fast() {
  analogWrite(PWMA1, int(Mspeed / 4));
  analogWrite(PWMA2, 0);
  analogWrite(PWMB1, Mspeed);
  analogWrite(PWMB2, 0);
}
void M_back_left_fast() {
  analogWrite(PWMA1, 0);
  analogWrite(PWMA2, Mspeed);
  analogWrite(PWMB1, 0);
  analogWrite(PWMB2, int(Mspeed / 4));
}

void M_right_fast() {
  analogWrite(PWMA1, Mspeed);
  analogWrite(PWMA2, 0);
  analogWrite(PWMB1, int(Mspeed / 4));
  analogWrite(PWMB2, 0);
}

void M_back_right_fast() {
  analogWrite(PWMA1, 0);
  analogWrite(PWMA2, int(Mspeed / 4));
  analogWrite(PWMB1, 0);
  analogWrite(PWMB2, Mspeed);
}
void M_stop() {
  analogWrite(PWMA1, 0);
  analogWrite(PWMA2, 0);
  analogWrite(PWMB1, 0);
  analogWrite(PWMB2, 0);
}

void forward_tracking() {
  if (ls_condition == 0 ) {
    M_forward();
  } else if (ls_condition == 1) {
    M_right_fast();
  } else if (ls_condition == 2) {
    M_left_fast();
  } else if (ls_condition == 3) {
    M_right_fast();
  } else if (ls_condition == 4) {
    M_left_fast();
  } else if (ls_condition == 5) {//十字路口
    M_forward();
  } else if (ls_condition == 6) {
    M_forward();
  }
}


void backward_tracking() {
  if (ls_condition == 0 ) {
    M_backward();
  } else if (ls_condition == 1) {
    M_back_right_fast();
  } else if (ls_condition == 2) {
    M_back_left_fast();
  } else if (ls_condition == 3) {
    M_back_right_fast();
  } else if (ls_condition == 4) {
    M_back_left_fast();
  } else if (ls_condition == 5) {//十字路口
    M_backward();
  } else if (ls_condition == 6) {
    M_backward();
  }
}

