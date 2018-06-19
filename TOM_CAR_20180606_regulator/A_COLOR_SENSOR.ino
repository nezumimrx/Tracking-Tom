float color_array[2][4];
int colorShake = 50;

int GET_COLOR() {
  COLORregulator();
  //colorTemp = tcs.calculateColorTemperature(r, g, b);
  red = shakeTester(red, color_array[0][0], color_array[1][0], color_array[2][0]);
  green = shakeTester(green, color_array[0][1], color_array[1][1], color_array[2][1]);
  blue = shakeTester(blue, color_array[0][2], color_array[1][2], color_array[2][2]);
  Clear = shakeTester(Clear, color_array[0][3], color_array[1][3], color_array[2][3]);
//  Serial.print("RAWR : "); Serial.print(red); Serial.print("  ");
//  Serial.print("RAWG : "); Serial.print(green); Serial.print("  ");
//  Serial.print("RAWB : "); Serial.print(blue); Serial.print("  ");
//  Serial.print("RAWClear : "); Serial.println(Clear);
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
  color_condition = 0;
  //time to work, if clear value in its domain then boolean to work.
  if (c >= 500 && c <= 8000) {
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
      if (R_G >= 1.95 && R_G <= 3.2 && R_B > 1.68 && R_B <= 2.6 && g < (b+30)) {
        //Serial.println("**** RED ****");
        color_condition = 1;
      } else if (R_G >= 0.85 && R_G <= 1.2 && R_B >= 1.20 && R_B <= 1.35) {
        //Serial.println("**** Green ****");
        color_condition = 2;
      } else if (R_G >= 1.00 && R_G <= 1.3 && R_B >= 0.25 && R_B <= 0.85) {
        //Serial.println("**** BLUE ****");
        color_condition = 3;
      } else if (R_G >= 2.20 && R_G <= 4.8 && R_B >= 2.20 && R_B <= 6.8 && (g - b) > 400) {
        //Serial.println("**** YELLOW ****");
        color_condition = 4;
      } else if (R_G >= 1.40 && R_G <= 1.85 && R_B >= 1.25 && R_B <= 1.65 && r > g) {
        //Serial.println("**** BROWN ****");
        color_condition = 5;
      }
    }
    //Serial.print("R_G :");Serial.println(R_G);
    //Serial.print("R_B :");Serial.println(R_B);
  }
  //Serial.print("color_condition");Serial.println(color_condition);
  return color_condition;
}

void COLORregulator() {

  for (int i = 0; i <= 2; i++) {
    uint16_t tempR, tempG, tempB, tempC;
    tempR = 0; tempG = 0; tempB = 0; tempC = 0;
    getRawData_noDelay(&tempR, &tempG, &tempB, &tempC);
    float tempred = tempR; float tempgreen = tempG; float tempblue = tempB; float tempClear = tempC;
    color_array[i][0] = tempred;
    color_array[i][1] = tempgreen;
    color_array[i][2] = tempblue;
    color_array[i][3] = tempClear;
  }
}

float shakeTester(float value, float test0, float test1, float test2) {
  if (test0 <= (test1 + colorShake) && test0 >= (test1 - colorShake) && test1 <= (test2 + 50) && test1 >= (test2 - 50)) {
    return test0;
  } else return value;

}



















