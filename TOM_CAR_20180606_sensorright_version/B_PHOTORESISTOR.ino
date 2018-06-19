String sensor_array[3];
String FINAL_LS;
int LSfunction() {
  String LS  = LSregulator() ;
  //Serial.print("sensordata : "); Serial.println(LS);
  if (LS == "00000") {
    M_forward();
  } else if (LS == "11111") {//全在线上
  } else if (LS == "00001") {//最右
    ls_condition = 6;
  } else if (LS == "00010" || LS == "00011") {
    ls_condition = 4;
  } else if (LS == "00110" || LS == "00111") {
    ls_condition = 2;
  } else if (LS == "00100" || LS == "01110" || LS == "01010") {
    ls_condition = 0;
  } else if (LS == "01100" || LS == "11100") {
    ls_condition = 1;
  } else if (LS == "01000" || LS == "11000") {
    ls_condition = 3;
  } else if (LS == "10000") {//最左
    ls_condition = 5;
  }
  //////////////////////////////////////////////////////////////////
  if (LS == "11111" ) { //十字路口或者黑布
    ls_condition = 9;
    //Serial.println(" ****************************** ");
  }
  //Serial.print("ls_condition : "); Serial.println(ls_condition);
  return ls_condition;
  ////////////////////////////////////////////////////////////////////
}

void forward_tracking() {
  if (ls_condition == 6)M_right_fast(); //右拐-大
  else if (ls_condition == 4)M_right_slow(); //右拐-中
  else if (ls_condition == 2)M_right_little(); //右拐-小
  else if (ls_condition == 0)M_forward(); //直行
  else if (ls_condition == 1)M_left_little(); //左拐-小
  else if (ls_condition == 3)M_left_slow(); //左拐-中
  else if (ls_condition == 5)M_left_fast(); //左拐-大
  else if (ls_condition == 9) {
    toggle_record = false;
    toggle_tracking = false;
  }
}
char valueFilter(int standard, int value) {
  if (value > standard)return '0';
  else if (value <= standard)return '1';
}

String LSregulator() {
  for (int i = 0; i <= 2; i++) {
    ls_condition = 0;
    int standard = 700;
    int _LS1 = analogRead(LS1);//RIGHT
    int _LS2 = analogRead(LS2);
    int _LS3 = analogRead(LS3);
    int _LS4 = analogRead(LS4)*1.3;//LEFT
    int _LSM = int(c);
//    Serial.print("_LS2 : "); Serial.println(_LS2);
//    Serial.print("_LS3 : "); Serial.println(_LS3);
    float _ratio1 = float(_LS1) / float((_LS1 + _LS2 + _LS3 + _LS4) / 4);
    float _ratio2 = float(_LS2) / float((_LS1 + _LS2 + _LS3 + _LS4) / 4);
    float _ratio3 = float(_LS3) / float((_LS1 + _LS2 + _LS3 + _LS4) / 4);
    float _ratio4 = float(_LS4) / float((_LS1 + _LS2 + _LS3 + _LS4) / 4);
    char sensors[5];
    sensors[4] = valueFilter(700, _LS1);//最右
    sensors[3] = valueFilter(700, _LS2);
    sensors[1] = valueFilter(700, _LS3);
    sensors[0] = valueFilter(700, _LS4);
    sensors[2] = valueFilter(6000, _LSM);
    String LS  = String((char*)sensors);
    sensor_array[i] = LS;
  }

  if (sensor_array[0] == sensor_array[1] && sensor_array[0] == sensor_array[2]) {
    FINAL_LS = sensor_array[0];
  } else {
    FINAL_LS = FINAL_LS;
  }
  return FINAL_LS;
}












