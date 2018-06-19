//Mode1.单色线模式代表的含义

int GET_COLOR() {
  r = 0;
  g = 0;
  b = 0;
  c = 0;
  lux = 0;
  //
  getRawData_noDelay(&r, &g, &b, &c);
  //colorTemp = tcs.calculateColorTemperature(r, g, b);
  float red = r;
  float green = g;
  float blue = b;
  float Clear = c;
  //  Serial.print("RAWR : "); Serial.print(red); Serial.print("  ");
  //  Serial.print("RAWG : "); Serial.print(green); Serial.print("  ");
  //  Serial.print("RAWB : "); Serial.print(blue); Serial.print("  ");
  //Serial.print("RAWClear : "); Serial.println(Clear);
  int CD = color_filter(int(red), int(green), int(blue), int(Clear));//1-RED,2-GREEN,3-BLUE,4-YELLOW,5-BROWN,6-BLACK,0-WHITE,9-OFFROAD
  return CD;
}


void getRawData_noDelay(uint16_t *r, uint16_t *g, uint16_t *b, uint16_t *c)
{
  *c = tcs.read16(TCS34725_CDATAL);
  *r = tcs.read16(TCS34725_RDATAL);
  *g = tcs.read16(TCS34725_GDATAL);
  *b = tcs.read16(TCS34725_BDATAL);
}

int color_filter(int r, int g, int b, int c) {
  //initialize Standards
  int RS = 3090; int GS = 4380; int BS = 3770; int CS = 10000;
  boolean _workstart;
  int color_condition = 0;
  //time to work, if clear value in its domain then boolean to work.
  if (c >= 500 && c <= 6500) {
    _workstart = true;
  } else if (c <= 500) {
    _workstart = false;
    color_condition = 9;
  } else if (c > 6500) {
    _workstart = false;
    color_condition = 0;
  }
  //
  if (_workstart) {
    int R_decay = RS - r;
    int G_decay = GS - g;
    int B_decay = BS - b;
    float R_G = float(G_decay) / float(R_decay);
    float R_B = float(B_decay) / float(R_decay);
    //先判断是否是黑色
    if (r <= 350 && g <= 500 && b <= 450) {
      color_condition = 6;
    }
    if (color_condition != 6) {//不是黑色
      if (R_G >= 2.10 && R_G <= 2.55 && R_B >= 1.75 && R_B <= 2.1) {
        //Serial.println("**** RED ****");
        color_condition = 1;
      } else if (R_G >= 0.95 && R_G <= 1.1 && R_B >= 1.25 && R_B <= 1.35) {
        //Serial.println("**** Green ****");
        color_condition = 2;
      } else if (R_G >= 1.05 && R_G <= 1.3 && R_B >= 0.5 && R_B <= 0.7) {
        //Serial.println("**** BLUE ****");
        color_condition = 3;
      } else if (R_G >= 2.20 && R_G <= 3.6 && R_B >= 2.20 && R_B <= 4.25) {
        //Serial.println("**** YELLOW ****");
        color_condition = 4;
      } else if (R_G >= 1.50 && R_G <= 1.8 && R_B >= 1.35 && R_B <= 1.55) {
        //Serial.println("**** BROWN ****");
        color_condition = 5;
      } 
    }

    //Serial.println(R_G);
    //Serial.println(R_B);
  }

  return color_condition;
}













