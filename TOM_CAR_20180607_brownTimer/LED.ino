
void LED_FUNCTIONS() {
  ledBlink();
}


void ledBlink() {
  digitalWrite(carLight1, LED_toggle);
  digitalWrite(carLight2, LED_toggle);
  if (loopCounter >= 30) {
    if (openBuffer)LED_toggle = !LED_toggle;
    else if (!openBuffer)LED_toggle = 1;
    loopCounter = 0;
  }
}
