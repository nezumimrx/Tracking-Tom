void LSfunction() {
  int _LS1 = analogRead(LS1);
  int _LS2 = analogRead(LS2);
  int _LS3 = analogRead(LS3);
  int _LS4 = analogRead(LS4);
//Serial.print("LS1 : "); Serial.println(_LS1);
//Serial.print("LS2 : "); Serial.println(_LS2);
//Serial.print("LS3 : "); Serial.println(_LS3);
//Serial.print("LS4 : "); Serial.println(_LS4);
  //CONDITION1
  if (_LS1 <= 650 && _LS2 > 650 && _LS3 > 650 && _LS4 > 650) {//最右侧的检测到线
    LS_CONDITION = 3;
  } else if (_LS1 <= 650 && _LS2 <= 650 && _LS3 > 650 && _LS4 > 650) {//右侧两个同时踩到黑线
    LS_CONDITION = 1;
  } else if (_LS1 > 650 && _LS2 <= 650 && _LS3 > 650 && _LS4 > 650) {//最右侧的没踩到，靠近中间的踩到了
    LS_CONDITION = 1;
  } else if (_LS1 > 650 && _LS2 > 650 && _LS3 > 650 && _LS4 > 650) {//都没踩到
    LS_CONDITION = 0;
  } else if (_LS1 > 650 && _LS2 > 650 && _LS3 <= 650 && _LS4 > 650) {//最左侧的没踩到，靠近中间的踩到了
    LS_CONDITION = 2;
  } else if (_LS1 > 650 && _LS2 > 650 && _LS3 <= 650 && _LS4 <= 650) {//最左侧的没踩到，靠近中间的踩到了
    LS_CONDITION = 2;
  } else if (_LS1 > 650 && _LS2 > 650 && _LS3 > 650 && _LS4 <= 650) {//
    LS_CONDITION = 4;
  }
  //Serial.print("LS_CONDITION : "); Serial.println(LS_CONDITION);
}

void LS_TRACKING(int motorSpeed) {
  //Serial.println(IR_CONDITION);
  if (LS_CONDITION == 0) {
    M_forward(motorSpeed);
  } else if (LS_CONDITION == 1) {
    M_right_fast(motorSpeed);
  } else if (LS_CONDITION == 2) {
    M_left_fast(motorSpeed);
  } else if (LS_CONDITION == 3) {
    M_right_fast(motorSpeed);
  } else if (LS_CONDITION == 4) {
    M_left_fast(motorSpeed);
  } else if (LS_CONDITION == 5) {//白色
    M_forward(motorSpeed);
  } else if (LS_CONDITION == 6) {//十字路口
    M_forward(motorSpeed);
  } else if (LS_CONDITION == 7) {//提起来
    M_stop();
  }
}
