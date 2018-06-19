int previous_speedA, previous_speedB;
void color_record() {
  //Serial.print("openBuffer : "); Serial.println(openBuffer);
  if (color_condition == 5 && openBuffer == false && previous_color != 5) { //如果读到棕色，且之前没开始记录颜色，且没有立刻再次读到棕色，那就开始记录颜色把颜色记录器清空
    openBuffer = true;
    color_change_counter = 0;
    previous_speedA = MspeedA;
    previous_speedB = MspeedB;
    MspeedA = 60;
    MspeedB = 60;
  } else if (color_condition == 5 && openBuffer == true && previous_color != 5) {//如果读到棕色，且已经开始记录颜色，且上一个读到的颜色不是棕色，那就结束记录
    if (color_change_counter >= 2) {//如果被记录的颜色数量==2
      Serial.print("color_record1 : "); Serial.println(color_Buffer[0]);
      Serial.print("color_record2 : "); Serial.println(color_Buffer[1]);
      Color_Code_Match();//Match Color Code here在这里匹配颜色代码
      openBuffer = false; //关闭记录
      color_change_counter = 0; //统计过的颜色变化数量清零
      record_color = 0; //清空最后一次记录的颜色
      MspeedA = 65;
      MspeedB = 65;
    }
  } else if (openBuffer == false) {
    if (color_condition == 1) {
      MspeedA = 165;
      MspeedB = 165;
    } else if (color_condition == 2) {
      MspeedA = 105;
      MspeedB = 105;
    } else if (color_condition == 3) {
      MspeedA = 65;
      MspeedB = 65;
    } else if (color_condition == 4) {
    } else if (color_condition == 5) {
    }
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
  //Serial.print("color_code :");Serial.println(color_code);
  //Serial.print("color_change_counter :");Serial.println(color_change_counter);
  //  Serial.print("openBuffer : "); Serial.println(openBuffer);
  //  Serial.print("color_condition : "); Serial.println(color_condition);
  //  Serial.print("color_change_counter : "); Serial.println(color_change_counter);

}

void Color_Code_Match() {//颜色代码比较//1-RED,2-GREEN,3-BLUE,4-YELLOW,5-BROWN,6-BLACK,0-WHITE,9-OFFROAD
  if (color_Buffer[0] == 4 && color_Buffer[1] == 1) {// Y - - R 十字路口左拐
    color_code = 1;
  } else if (color_Buffer[0] == 1 && color_Buffer[1] == 4) {//R - - Y 十字路口右拐
    color_code = 2;
  } else if ((color_Buffer[0] == 3 && color_Buffer[1] == 1) || (color_Buffer[0] == 1 && color_Buffer[1] == 3)) { //B - - R 掉头
    color_code = 3;
  } else if (color_Buffer[0] == 3 && color_Buffer[1] == 2) { //B - - G 减速
    if (Mspeed > 105) {
      Mspeed--;
      delay(2);
    }
  } else if (color_Buffer[0] == 2 && color_Buffer[1] == 3) { //G - - B 加速
    if (Mspeed < 255) {
      Mspeed++;
      delay(2);
    }
  } else if ((color_Buffer[0] == 2 && color_Buffer[1] == 4) || (color_Buffer[0] == 4 && color_Buffer[1] == 2)) { //G - -Y Y - - G
    M_stop();
    delay(2000);
    toggle_record = true;
    toggle_tracking = true;
  }
  //color_Buffer[0] = 0;
  //color_Buffer[1] = 0;

}
