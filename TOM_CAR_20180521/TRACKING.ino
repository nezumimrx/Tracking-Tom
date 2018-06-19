int previous_color = 0;
int record_color = 0;
int color_change_counter = 0;
boolean openBuffer = false;
int color_Buffer[2];
void COLOR_TRACKING(int motorSpeed) {
  int ls_condition = LSfunction(); //0-白纸上，1-4踩到线,5都踩到，9-离开桌面
  int color_condition = GET_COLOR(); //1-RED,2-GREEN,3-BLUE,4-YELLOW,5-BROWN,6-BLACK,0-WHITE,9-OFFROAD
  boolean takeoff = false;
  //Serial.print("ls_condition : "); Serial.println(ls_condition);
  //Serial.print("color_condition : "); Serial.println(color_condition);
  //先判断有没有被拿起来
  if (ls_condition == 9 || color_condition == 9) {
    takeoff = true;
  } else {
    takeoff = false;
  }
  if (takeoff) {//被拿起来
    //Serial.println("takeoff");
    M_stop();
  } else if (!takeoff) {//没有被拿起来
    //Serial.println("not takeoff");

  }

  if (color_condition == 5 && openBuffer == false && previous_color != 5) { //如果读到棕色，且之前没开始记录颜色，且没有立刻再次读到棕色，那就开始记录颜色把颜色记录器清空
    openBuffer = true;
    color_change_counter = 0;
  } else if (color_condition == 5 && openBuffer == true && color_change_counter >= 2) {//如果读到棕色，且之前已经开始记录，且记录过颜色的变换数量>=2个，那就结束记录,打印记录下来的颜色
    openBuffer = false;
    record_color=0;//清空最后一次记录的颜色
    color_change_counter=0;//统计过的颜色变化数量清零
    Serial.print("color_record1 : "); Serial.println(color_Buffer[0]);
    Serial.print("color_record2 : "); Serial.println(color_Buffer[1]);
  }

  if (color_condition != previous_color) {//如果读到的颜色和记录的颜色不同
    previous_color = color_condition;//记录颜色替换为现在的颜色
    if (openBuffer == true && color_condition != 0 && color_condition != 5 && color_condition != 6&&record_color!=color_condition) {//如果记录开启，且颜色不是白、黑、粽，且之前记录最后一次读到的颜色和现在不一样，那么
      record_color = color_condition;//将最后一次记录的颜色改为现在读取到的颜色
      color_change_counter++;//颜色统计数量++
      if (color_change_counter <= 2) {//当记录的颜色数量小于2时，将数组color_Buffer中的值替换
        color_Buffer[color_change_counter - 1] = color_condition;
      }
    }
  }
  Serial.print("color_change_counter : "); Serial.println(color_change_counter);
  /*
    if (LS_CONDITION == 0&&color_condition) {
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
    }*/
}
