void M_forward(int motorSpeed) {
  analogWrite(PWMA1, motorSpeed);
  analogWrite(PWMA2, 0);
  analogWrite(PWMB1, motorSpeed);
  analogWrite(PWMB2, 0);
}

void M_backward(int motorSpeed) {
  analogWrite(PWMA1, 0);
  analogWrite(PWMA2, motorSpeed);
  analogWrite(PWMB1, 0);
  analogWrite(PWMB2, motorSpeed);
}

void M_left_slow(int motorSpeed) {
  analogWrite(PWMA1, int(motorSpeed / 2));
  analogWrite(PWMA2, 0);
  analogWrite(PWMB1, int(motorSpeed));
  analogWrite(PWMB2, 0);
}

void M_right_slow(int motorSpeed) {
  analogWrite(PWMA1, motorSpeed);
  analogWrite(PWMA2, 0);
  analogWrite(PWMB1, int(motorSpeed / 2));
  analogWrite(PWMB2, 0);
}

void M_left_fast(int motorSpeed) {
  analogWrite(PWMA1, int(motorSpeed / 4));
  analogWrite(PWMA2, 0);
  analogWrite(PWMB1, motorSpeed);
  analogWrite(PWMB2, 0);
}

void M_right_fast(int motorSpeed) {
  analogWrite(PWMA1, motorSpeed);
  analogWrite(PWMA2, 0);
  analogWrite(PWMB1, int(motorSpeed / 4));
  analogWrite(PWMB2, 0);
}
void M_stop() {
  analogWrite(PWMA1, 0);
  analogWrite(PWMA2, 0);
  analogWrite(PWMB1, 0);
  analogWrite(PWMB2, 0);
}

