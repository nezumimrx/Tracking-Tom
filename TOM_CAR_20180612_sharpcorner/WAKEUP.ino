void WAKEUP_process() {
  delay(1000);
  analogWrite(carLight1, 255);
  analogWrite(carLight2, 50);
  analogWrite(PWMA1, 0);
  analogWrite(PWMA2, 55);
  analogWrite(PWMB1, 55);
  analogWrite(PWMB2, 0);
  delay(1500);
  analogWrite(carLight1, 50);
  analogWrite(carLight2, 255);
  analogWrite(PWMA1, 55);
  analogWrite(PWMA2, 0);
  analogWrite(PWMB1, 0);
  analogWrite(PWMB2, 55);
  delay(1500);
  M_stop();
  digitalWrite(carLight1, 0);
  digitalWrite(carLight2, 0);
  delay(300);
  for (int i = 0; i <= 255; i += 5) {
    analogWrite(carLight1, i);
    analogWrite(carLight2, i);
    delay(25);
  }
  delay(300);
  digitalWrite(carLight1, 0);
  digitalWrite(carLight2, 0);
  delay(300);
  digitalWrite(carLight1, 1);
  digitalWrite(carLight2, 1);
  delay(500);
  analogWrite(PWMA1, 50);
  analogWrite(PWMA2, 0);
  analogWrite(PWMB1, 50);
  analogWrite(PWMB2, 0);
  delay(1250);
  M_stop();
  delay(1250);
}

void WAKEUP_process2() {
  for (int i = 0; i <= 5; i++) {
    if (i % 2 == 0) {
      digitalWrite(carLight1, 1);
      digitalWrite(carLight2, 0);
      delay(250);
    } else {
      digitalWrite(carLight1, 0);
      digitalWrite(carLight2, 1);
      delay(250);
    }
  }
  digitalWrite(carLight1, 1);
  digitalWrite(carLight2, 1);
  analogWrite(PWMA1, 0);
  analogWrite(PWMA2, 255);
  analogWrite(PWMB1, 255);
  analogWrite(PWMB2, 0);
  delay(1500);
  M_stop();
  delay(1500);

}

