int previous_color = 0;//上一个被检测到的颜色
int record_color = 0;//上一个被记录过的颜色
int color_change_counter = 0;//变换过多少种不同的颜色
boolean openBuffer = false;//开启记录
int color_Buffer[2];//记录颜色数量
boolean Mdirection;//行动方向
boolean flip_direction;//
boolean toggle_tracking = true;
boolean toggle_record = true;
int color_code;
void COLOR_TRACKING() {
  ls_condition = LSfunction(); //0-白纸上，1-4踩到线,5都踩到，6,中间两个踩到，直行9-离开桌面
  color_condition = GET_COLOR(); //1-RED,2-GREEN,3-BLUE,4-YELLOW,5-BROWN,6-BLACK,0-WHITE,9-OFFROAD
  boolean takeoff = false;
  if (color_condition != 6 && color_condition != 0 && color_condition != 5) {
    //Serial.print("GET_COLOR :"); Serial.println(color_condition);
  }
  //Serial.print("ls_condition :"); Serial.println(ls_condition);
  //

  //先判断有没有被拿起来
  if ( color_condition == 9) {
    takeoff = true;
  } else {
    takeoff = false;
  }
  //实现基本的循迹功能
  if (takeoff) {//被拿起来
    M_stop();

  } else if (!takeoff) {//没有被拿起来
    Color_Code_Functions();
  }
}

void color_record() {
  //Serial.print("openBuffer : "); Serial.println(openBuffer);
  if (color_condition == 5 && openBuffer == false && previous_color != 5) { //如果读到棕色，且之前没开始记录颜色，且没有立刻再次读到棕色，那就开始记录颜色把颜色记录器清空
    openBuffer = true;
    color_change_counter = 0;
  } else if (color_condition == 5 && openBuffer == true && color_change_counter == 1) {
    M_Uturn();
    delay(1300);
    M_stop();
    delay(500);
    M_Uturn2();
    delay(1250);
    M_stop();
    delay(500);
    openBuffer = false;
    color_change_counter = 0; //统计过的颜色变化数量清零
    record_color = 0; //清空最后一次记录的颜色
    //color_code=4;//如果在结束时候只监测到了1个颜色，那么就进入color_code=4的模式延迟一下再继续
  } else if (color_condition == 5 && openBuffer == true && color_change_counter >= 2) {//如果读到棕色，且之前已经开始记录，且记录过颜色的变换数量>=2个，那就结束记录,打印记录下来的颜色
    openBuffer = false;
    record_color = 0; //清空最后一次记录的颜色
    color_change_counter = 0; //统计过的颜色变化数量清零
    Serial.print("color_record1 : "); Serial.println(color_Buffer[0]);
    Serial.print("color_record2 : "); Serial.println(color_Buffer[1]);
    Color_Code_Match();//Match Color Code here在这里匹配颜色代码
  }

  if (color_condition != previous_color) {//如果读到的颜色和记录的颜色不同
    previous_color = color_condition;//记录颜色替换为现在的颜色
    if (openBuffer == true && color_condition != 0 && color_condition != 5 && color_condition != 6 && record_color != color_condition) { //如果记录开启，且颜色不是白、黑、粽，且之前记录最后一次读到的颜色和现在不一样，那么
      record_color = color_condition;//将最后一次记录的颜色改为现在读取到的颜色
      color_change_counter++;//颜色统计数量++
      if (color_change_counter <= 2) { //当记录的颜色数量小于2时，将数组color_Buffer中的值替换
        color_Buffer[color_change_counter - 1] = color_condition;
      }
    }
  }
//  Serial.print("openBuffer : "); Serial.println(openBuffer);
//  Serial.print("color_condition : "); Serial.println(color_condition);
//  Serial.print("color_change_counter : "); Serial.println(color_change_counter);
}


void one_color_code() {
  if (color_condition != 5 && color_condition != 0 && color_condition != 6 && openBuffer == false) { //目前下方颜色不是棕色\白色\黑色，且记录没有开启
    if (color_condition == 1) { //RED
      if (Mspeed != 105) {
        Mspeed = 105;
      }
      flip_direction = false;
    } else if (color_condition == 2) { //GREEN
      if (Mspeed != 150) {
        Mspeed = 150;
      }
      flip_direction = false;
    } else if (color_condition == 3 ) { //BLUE
      if (Mspeed != 255) {
        Mspeed = 255;
      }
      flip_direction = false;
    } else if (color_condition == 4 ) { //YELLOW
      if (flip_direction == false) {
        Mdirection = !Mdirection;
        flip_direction = true;
      }
    }
  }
}












