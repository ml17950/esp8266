
#define TRANSMITTER_PIN     D7

#include "./ritter_8341c.h"

void int_led_blink(int cnt, int delayms = 500) {
  for (int i=0; i<cnt; i++) {
    digitalWrite(BUILTIN_LED, LOW); // turn led on
    delay(delayms);
    digitalWrite(BUILTIN_LED, HIGH); // turn led off
    delay(delayms);
  }
}

void setup() {
  Serial.begin(115200);
  delay(10);
  Serial.println();
  Serial.println();

  pinMode(BUILTIN_LED, OUTPUT);
  digitalWrite(BUILTIN_LED, HIGH); // turn led off

  ritter_socket_init();

  Serial.println();
  Serial.println();
  Serial.println("Setup ready");
  int_led_blink(20, 100);
}

void loop() {
  delay(3000);
  for (int i = 1; i < 4; i++) {
    int_led_blink(i, 100);
    ritter_socket_on(i);
    delay(1000);
  }

  delay(3000);
  for (int i = 1; i < 4; i++) {
    int_led_blink(i, 250);
    ritter_socket_off(i);
    delay(1000);
  }
}
