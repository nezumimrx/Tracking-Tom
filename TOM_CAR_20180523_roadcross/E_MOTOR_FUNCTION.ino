
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
  analogWrite(PWMA1, int(Mspeed / 4));
  analogWrite(PWMA2, 0);
  analogWrite(PWMB1, int(Mspeed));
  analogWrite(PWMB2, 0);
}

void M_back_left_slow() {
  analogWrite(PWMA1, 0);
  analogWrite(PWMA2, int(Mspeed));
  analogWrite(PWMB1, 0);
  analogWrite(PWMB2, 0);

}

void M_right_slow() {
  analogWrite(PWMA1, Mspeed);
  analogWrite(PWMA2, 0);
  analogWrite(PWMB1, int(Mspeed / 4));
  analogWrite(PWMB2, 0);
}

void M_back_right_slow() {
  analogWrite(PWMA1, 0);
  analogWrite(PWMA2, 0);
  analogWrite(PWMB1, 0);
  analogWrite(PWMB2, Mspeed);
}

void M_left_fast() {
  analogWrite(PWMA1, 0);
  analogWrite(PWMA2, 0);
  analogWrite(PWMB1, Mspeed);
  analogWrite(PWMB2, 0);
}
void M_back_left_fast() {
  analogWrite(PWMA1, 0);
  analogWrite(PWMA2, Mspeed);
  analogWrite(PWMB1, 0);
  analogWrite(PWMB2, 0);
}

void M_right_fast() {
  analogWrite(PWMA1, Mspeed);
  analogWrite(PWMA2, 0);
  analogWrite(PWMB1, 0);
  analogWrite(PWMB2, 0);
}

void M_back_right_fast() {
  analogWrite(PWMA1, 0);
  analogWrite(PWMA2, 0);
  analogWrite(PWMB1, 0);
  analogWrite(PWMB2, Mspeed);
}
void M_stop() {
  analogWrite(PWMA1, 0);
  analogWrite(PWMA2, 0);
  analogWrite(PWMB1, 0);
  analogWrite(PWMB2, 0);
}

void M_turn_left() {
  analogWrite(PWMA1, 0);
  analogWrite(PWMA2, 0);
  analogWrite(PWMB1, 255);
  analogWrite(PWMB2, 0);
}

void M_turn_right() {
  analogWrite(PWMA1, 255);
  analogWrite(PWMA2, 0);
  analogWrite(PWMB1, 0);
  analogWrite(PWMB2, 0);
}

void M_intersection(int dir) {//十字路口左右直走处理 0-forward,1-left,2-right
  if (dir == 0) {
    M_forward();
    delay(500);
    toggle_record = true;
    toggle_tracking = true;
  } else if (dir == 1) {
    while (LSfunction()!=2) {//向左转，知道左侧靠中间的传感器可以监测到线
      M_turn_left();
    }
    toggle_record = true;
    toggle_tracking = true;
  } else if (dir == 2) {
     while (LSfunction()!=1) {//向右转，直到右侧靠近中间的传感器可以监测到线
       M_turn_right();
    }
    toggle_record = true;
    toggle_tracking = true;
  }
}

void M_Uturn() {
  analogWrite(PWMA1, 0);
  analogWrite(PWMA2, 255);
  analogWrite(PWMB1, 255);
  analogWrite(PWMB2, 0);
}

void M_Uturn2() {
  analogWrite(PWMA1, 255);
  analogWrite(PWMA2, 0);
  analogWrite(PWMB1, 0);
  analogWrite(PWMB2, 255);
}
