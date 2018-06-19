int LSfunction() {
  int _LS1 = analogRead(LS1);
  int _LS2 = analogRead(LS2);
  int _LS3 = analogRead(LS3);
  int _LS4 = analogRead(LS4);
//    Serial.print("LS1 : "); Serial.println(_LS1);
//    Serial.print("LS2 : "); Serial.println(_LS2);
//    Serial.print("LS3 : "); Serial.println(_LS3);
//    Serial.print("LS4 : "); Serial.println(_LS4);
  float _ratio1 = float(_LS1) / float((_LS1 + _LS2 + _LS3 + _LS4) / 4);
  float _ratio2 = float(_LS2) / float((_LS1 + _LS2 + _LS3 + _LS4) / 4);
  float _ratio3 = float(_LS3) / float((_LS1 + _LS2 + _LS3 + _LS4) / 4);
  float _ratio4 = float(_LS4) / float((_LS1 + _LS2 + _LS3 + _LS4) / 4);
//  Serial.print("_ratio1 : "); Serial.println(_ratio1);
//  Serial.print("_ratio2 : "); Serial.println(_ratio2);
//  Serial.print("_ratio3 : "); Serial.println(_ratio3);
//  Serial.print("_ratio4 : "); Serial.println(_ratio4);
  //CONDITION1
  if (_LS1 <= 700 && _LS2 > 700 && _LS3 > 700 && _LS4 > 700) {//最右侧的检测到线
    LS_CONDITION = 3;
  } else if (_LS1 <= 700 && _LS2 <= 700 && _LS3 > 700 && _LS4 > 700) {//右侧两个同时踩到黑线
    LS_CONDITION = 1;
  } else if (_LS1 > 700 && _LS2 <= 700 && _LS3 > 700 && _LS4 > 700) {//最右侧的没踩到，靠近中间的踩到了
    LS_CONDITION = 1;
  } else if (_LS1 > 700 && _LS2 > 700 && _LS3 > 700 && _LS4 > 700) {//都没踩到
    LS_CONDITION = 0;
  } else if (_LS1 > 700 && _LS2 > 700 && _LS3 <= 700 && _LS4 > 700) {//最左侧的没踩到，靠近中间的踩到了
    LS_CONDITION = 2;
  } else if (_LS1 > 700 && _LS2 > 700 && _LS3 <= 700 && _LS4 <= 700) {//最左侧的没踩到，靠近中间的踩到了
    LS_CONDITION = 2;
  } else if (_LS1 > 700 && _LS2 > 700 && _LS3 > 700 && _LS4 <= 700) {//最左侧的踩到
    LS_CONDITION = 4;
  } else if (_LS1 < 100 || _LS2 < 100 || _LS3 < 100 || _LS4 < 100) {//离开桌面
    LS_CONDITION = 9;
  } else if (_ratio1 <= 1.2 && _ratio1 >= 0.8 && _ratio2 <= 1.2 && _ratio2 >= 0.8 && _ratio3 <= 1.2 && _ratio3 >= 0.8 && _ratio4 <= 1.2 && _ratio4 >= 0.8&&_LS1 < 700 && _LS2 < 700 && _LS3 < 700 && _LS4 < 700) { //全部踩到了
    LS_CONDITION = 5;
  }
  return LS_CONDITION;
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
