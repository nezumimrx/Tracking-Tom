void Color_Code_Functions() {
  if (color_code >= 0 && color_code <= 2) {//平常循迹及十字路口处理
    color_code_012();
  } else if (color_code == 3) {//掉头
    color_code_3();
  }

}


void color_code_012() {//平常循迹及十字路口处理
  if (toggle_tracking) {
    forward_tracking();
  } else if (!toggle_tracking) {//4个循迹传感器都读到黑色时判断为在十字路口，关闭普通循迹功能，临时开启M_intersection功能一定时间
    M_intersection(color_code);
  }

  if (toggle_record) {//临时关闭记录颜色
    color_record();
  } else if (!toggle_record) {
  }

}

void color_code_3() {//掉头
  M_stop();
  delay(500);
  M_Uturn();
  delay(350);
  int rotation_time = 0;
  while (ls_condition != 2 && ls_condition != 1 ) {
    LSfunction();
    if (rotation_time == 0) {
      M_Uturn();
      delay(200);
      rotation_time = 1;
    }
    M_Uturn(); //逆时针原地打转，直到右侧靠中间的传感器检测到线
  }
  M_forward();
  delay(200);
  color_code = 0;
}

