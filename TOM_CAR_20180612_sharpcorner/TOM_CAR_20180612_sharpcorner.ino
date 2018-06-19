#include <Adafruit_TCS34725.h>
Adafruit_TCS34725 tcs = Adafruit_TCS34725(TCS34725_INTEGRATIONTIME_50MS, TCS34725_GAIN_4X);
uint16_t r, g, b, c, colorTemp, lux;
int PWMA1 = 5;
int PWMA2 = 6;
int PWMB2 = 9;
int PWMB1 = 10;
//定义引脚
int pinLight = 7;
int carLight1 = 3;
int carLight2 = 11;
int colorLight = 2;
int LS1 = A0;//最右
int LS2 = A1;
int LS3 = A2;
int LS4 = A3;//最左
//
int ls_condition, color_condition;
int Mspeed = 105;
int MspeedA = 65;
int MspeedB = 65;
//
int previous_color = 0;//上一个被检测到的颜色
int record_color = 0;//上一个被记录过的颜色
int color_change_counter = 0;//变换过多少种不同的颜色
boolean openBuffer = false;//开启记录
int color_Buffer[2];//记录颜色数量
boolean toggle_tracking = true;
boolean toggle_record = true;
int color_code;//0-路口直走，1-路口左拐，2-路口右拐
//
int loopCounter;
int bufferCounter;
int timerCounter;
boolean LED_toggle = 0;
boolean LED_Blink = 1;
boolean boolRun = 1;
boolean firstStop = 1;
void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  Serial.setTimeout(25);
  pinMode(pinLight, OUTPUT);
  pinMode(carLight1, OUTPUT);
  pinMode(carLight2, OUTPUT);
  pinMode(colorLight, OUTPUT);
  pinMode(PWMA1, OUTPUT);
  pinMode(PWMA2, OUTPUT);
  pinMode(PWMB1, OUTPUT);
  pinMode(PWMB2, OUTPUT);
  pinMode(LS1, INPUT);
  pinMode(LS2, INPUT);
  pinMode(LS3, INPUT);
  pinMode(LS4, INPUT);
  digitalWrite(pinLight, 1);
  digitalWrite(carLight1, 0);
  digitalWrite(carLight2, 0);
  digitalWrite(colorLight, 1);

  if (tcs.begin()) Serial.println("Sensor OK");
  tcs.write8(TCS34725_PERS, TCS34725_PERS_NONE);
  tcs.setInterrupt(true);

  //WAKEUP_process2();
}

void loop() {
  // put your main code here, to run repeatedly:
  //LSfunction();
  loopCounter++;
  //LSfunction();//0直行,1-左拐小，2右拐小，3左拐中，4右拐中，5左拐大，6右拐大
  //GET_COLOR();
  if (boolRun) {
    COLOR_TRACKING();
    LED_FUNCTIONS();
  } else {
    if (firstStop) {
      M_stop();
      WAKEUP_process2();
      firstStop=0;
    }
    M_stop();
  }


}












