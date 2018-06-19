
void COLOR_TRACKING() {
  //
  LSfunction();//0直行,1-左拐小，2右拐小，3左拐中，4右拐中，5左拐大，6右拐大
  GET_COLOR();
  //if (color_condition != 6 && color_condition != 0 && color_condition != 9) {
  //Serial.print("GET_COLOR :"); Serial.println(color_condition);}
  //先判断有没有被拿起来 , 实现基本的循迹功能
  if (color_condition == 9) { //被拿起来
    M_stop();
  } else if (color_condition != 9) { //没有被拿起来
    Color_Code_Functions();
  }
}

void Color_Code_Functions() {
  if (color_code >= 0 && color_code <= 2) {//平常循迹及十字路口处理
    color_code_012();
  } else if (color_code == 3) {//掉头
    color_code_3();
  }
}

void color_code_012() {//平常循迹及十字路口处理
  if (toggle_tracking) {
    //forward_tracking();
  } else if (!toggle_tracking) {//4个循迹传感器都读到黑色时判断为在十字路口，关闭普通循迹功能，临时开启M_intersection功能一定时间
    M_intersection(color_code);
  }

  if (toggle_record) {//临时关闭记录颜色
    color_record();
  } else if (!toggle_record) {
  }
}


void color_code_3() {
  M_stop();
  delay(500);
  M_Uturn();
  delay(1000);
  int rotation_time = 0;
  while (ls_condition != 1 ) {
    LSfunction();
    M_Uturn(); //逆时针原地打转，直到右侧靠中间的传感器检测到线
  }
  color_code = 0;
}




