int previous_speedA, previous_speedB;
boolean speedPlus, speedMinus;
void color_record() {
  //Serial.print("openBuffer : "); Serial.println(openBuffer);
  if (color_condition == 5 && openBuffer == false && previous_color != 5) { //如果读到棕色，且之前没开始记录颜色，且没有立刻再次读到棕色，那就开始记录颜色把颜色记录器清空
    int confirm_counter = 0;
    if (MspeedA > 65 && MspeedB > 65) {
      analogWrite(PWMA1, 0);
      analogWrite(PWMA2, MspeedA);
      analogWrite(PWMB1, 0);
      analogWrite(PWMB2, MspeedB);
      delay(250);
      M_stop();
    } else M_stop();

    for (int i = 0; i <= 10; i++) {
      if (brown_confirm()) {
        confirm_counter++;
      }
    }
      delay(350);
    if (confirm_counter > 6) {
      openBuffer = true;
      color_change_counter = 0;
      previous_speedA = MspeedA;
      previous_speedB = MspeedB;
      MspeedA = 55;
      MspeedB = 55;
    }
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
      bufferCounter = 0;
    }
  } else if (openBuffer == false) {
    if (color_condition == 1) {
      //      if (previous_color != 1) {
      //        M_stop();
      //        delay(500);
      //      }
      MspeedA = 105;
      MspeedB = 105;
    } else if (color_condition == 2) {
      //      if (previous_color != 2) {
      //        M_stop();
      //        delay(500);
      //      }
      //      MspeedA = 105;
      //      MspeedB = 105;
    } else if (color_condition == 3) {
      //      if (previous_color != 3) {
      //        M_stop();
      //        delay(500);
      //      }
      MspeedA = 65;
      MspeedB = 65;
    } else if (color_condition == 4) {
    } else if (color_condition == 5) {
    }
    if (speedPlus) {
      if (MspeedA < 105 && MspeedB < 105) {
        if (loopCounter % 5 == 0) {
          MspeedA++;
          MspeedB++;
        }
      } else if (MspeedA >= 102 && MspeedB >= 102) {
        speedPlus = false;
      }
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

  if (openBuffer) {
    bufferCounter++;
    if (bufferCounter >= 600) {
      bufferCounter = 0;
      openBuffer = !openBuffer;
      color_change_counter = 0;
      record_color = 0;
      color_Buffer[0] = 0;
      color_Buffer[1] = 0;
    }
  }

  //Serial.print("color_code :");Serial.println(color_code);
  //Serial.print("color_change_counter :");Serial.println(color_change_counter);
  //  Serial.print("openBuffer : "); Serial.println(openBuffer);
  //  Serial.print("bufferCounter : "); Serial.println(bufferCounter);
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
  } else if ((color_Buffer[0] == 3 && color_Buffer[1] == 2) || (color_Buffer[0] == 2 && color_Buffer[1] == 3)) { //B - - G  G - - B 加速速
    speedPlus = true;
  }  else if ((color_Buffer[0] == 3 && color_Buffer[1] == 2) || (color_Buffer[0] == 2 && color_Buffer[1] == 3)) { //B - - Y  Y - - B 减速

  } else if ((color_Buffer[0] == 2 && color_Buffer[1] == 4) || (color_Buffer[0] == 4 && color_Buffer[1] == 2)) { //G - -Y Y - - G
    M_stop();
    for (int i = 255; i >= 0; i -= 5) {
      analogWrite(carLight1, i);
      analogWrite(carLight2, i);
      delay(30);
    }
    for (int i = 0; i <= 255; i += 5) {
      analogWrite(carLight1, i);
      analogWrite(carLight2, i);
      delay(30);
    }
  } else if ((color_Buffer[0] == 1 && color_Buffer[1] == 2) || (color_Buffer[0] == 2 && color_Buffer[1] == 1)) {//G - -R R - - G
    boolRun = false;
  }
  //color_Buffer[0] = 0;
  //color_Buffer[1] = 0;

}


