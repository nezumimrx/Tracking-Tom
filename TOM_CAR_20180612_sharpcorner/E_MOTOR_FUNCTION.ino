void M_forward() {
  analogWrite(PWMA1, MspeedA);
  analogWrite(PWMA2, 0);
  analogWrite(PWMB1, MspeedB);
  analogWrite(PWMB2, 0);
}

void M_backward() {
  analogWrite(PWMA1, 0);
  analogWrite(PWMA2, MspeedA);
  analogWrite(PWMB1, 0);
  analogWrite(PWMB2, MspeedB);
}

void M_right_fast() {
  analogWrite(PWMA1, MspeedA);
  analogWrite(PWMA2, 0);
  analogWrite(PWMB1, 0);
  analogWrite(PWMB2, 0);
}
void M_right_slow() {
  analogWrite(PWMA1, MspeedA);
  analogWrite(PWMA2, 0);
  analogWrite(PWMB1, int(MspeedB / 2.0));
  analogWrite(PWMB2, 0);
}

void M_right_little() {
  analogWrite(PWMA1, MspeedA);
  analogWrite(PWMA2, 0);
  analogWrite(PWMB1, (MspeedB - int(MspeedB / 4.0)));
  analogWrite(PWMB2, 0);
}

void M_left_fast() {
  analogWrite(PWMA1, 0);
  analogWrite(PWMA2, 0);
  analogWrite(PWMB1, MspeedB);
  analogWrite(PWMB2, 0);
}
void M_left_slow() {
  analogWrite(PWMA1, int(MspeedA / 2.0));
  analogWrite(PWMA2, 0);
  analogWrite(PWMB1, MspeedB);
  analogWrite(PWMB2, 0);
}
void M_left_little() {
  analogWrite(PWMA1, (MspeedA - int(MspeedA / 4.0)));
  analogWrite(PWMA2, 0);
  analogWrite(PWMB1, MspeedB);
  analogWrite(PWMB2, 0);
}

void M_stop() {
  analogWrite(PWMA1, 0);
  analogWrite(PWMA2, 0);
  analogWrite(PWMB1, 0);
  analogWrite(PWMB2, 0);
}

void M_Uturn() {
  analogWrite(PWMA1, 0);
  analogWrite(PWMA2, 65);
  analogWrite(PWMB1, 65);
  analogWrite(PWMB2, 0);
}

void M_Uturn_reverse() {
  analogWrite(PWMA1, 65);
  analogWrite(PWMA2, 0);
  analogWrite(PWMB1, 0);
  analogWrite(PWMB2, 65);
}

void M_intersection(int dir) {//十字路口左右直走处理 0-forward,1-left,2-right
  if (dir == 0) {
    M_forward();
    delay(500);
    toggle_record = true;
    toggle_tracking = true;
  } else if (dir == 1) {
    M_left_fast();
    delay(1050);
    while (ls_condition != 1 && ls_condition != 2) { //向左转，知道左侧靠中间的传感器可以监测到线
      GET_COLOR();
      LSfunction();
      M_left_fast();
    }
    toggle_record = true;
    toggle_tracking = true;
  } else if (dir == 2) {
    M_right_fast();
    delay(1050);
    while ( ls_condition != 1 && ls_condition != 2) { //向右转，直到右侧靠近中间的传感器可以监测到线
      GET_COLOR();
      LSfunction();
      M_right_fast();
    }
    toggle_record = true;
    toggle_tracking = true;
  }
}
