
#define IR_LED_PIN     D7

#include "./honeywell_ho5500_fan.h"

void setup() {
  Serial.begin(115200);
  delay(10);
  Serial.println();
  Serial.println();

  pinMode(IR_LED_PIN, OUTPUT);
  digitalWrite(IR_LED_PIN, HIGH);

  // initialize sw-pwm @ 38 KHz
  init_software_pwm(38);

  Serial.println();
  Serial.println();
  Serial.println("Setup ready");
}

void loop() {
  HO5500RE_POWER();
  delay(1000);
  HO5500RE_SPEED();
  delay(1000);
  HO5500RE_MOVEMENT();
  delay(1000);
  HO5500RE_TIMER();
  delay(1000);
  HO5500RE_SCENE();
  delay(1000);
  HO5500RE_POWER();
  delay(5000);
}
