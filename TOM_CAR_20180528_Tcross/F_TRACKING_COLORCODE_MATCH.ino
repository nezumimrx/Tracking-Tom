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
