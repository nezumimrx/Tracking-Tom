//库文件
#include <Adafruit_TCS34725.h>
Adafruit_TCS34725 tcs = Adafruit_TCS34725(TCS34725_INTEGRATIONTIME_50MS, TCS34725_GAIN_4X);
uint16_t r, g, b, c, colorTemp, lux;
//定义引脚
int pinLight = 7;
int carLight1 = 3;
int carLight2 = 11;
int colorLight = 2;
int LS1 = A0;//最右
int LS2 = A1;
int LS3 = A2;
int LS4 = A3;//最左

int PWMA1 = 5;
int PWMA2 = 6;
int PWMB2 = 9;
int PWMB1 = 10;

//
int LS_CONDITION = 0;
int motorSpeed = 255 ;
void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  Serial.setTimeout(25);
  pinMode(pinLight, OUTPUT);
  pinMode(carLight1, OUTPUT);
  pinMode(carLight2, OUTPUT);
  pinMode(colorLight, OUTPUT);
  pinMode(LS1, INPUT);
  pinMode(LS2, INPUT);
  pinMode(LS3, INPUT);
  pinMode(LS4, INPUT);
  pinMode(PWMA1, OUTPUT);
  pinMode(PWMA2, OUTPUT);
  pinMode(PWMB1, OUTPUT);
  pinMode(PWMB2, OUTPUT);

  if (tcs.begin()) Serial.println("Sensor OK");
  tcs.write8(TCS34725_PERS, TCS34725_PERS_NONE);
  tcs.setInterrupt(true);
  digitalWrite(pinLight, 1);
  digitalWrite(carLight1, 0);
  digitalWrite(carLight2, 0);
  digitalWrite(colorLight, 1);

}

void loop() {
  // put your main code here, to run repeatedly:
  //LSfunction();
  //LS_TRACKING(150);
  //M_forward(255);
  GET_COLOR();

}



