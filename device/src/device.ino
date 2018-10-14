#include "interface.h"
#include "led.h"

LED led(13);


int bla(void) {
  return 1;
}

int add(int a, int b) {
  return a + b;
}

void setLed(int brightness) {
  led.setBrightness((byte)brightness);
}


void setup(void) {
  led.setBrightness(40);
  Serial.begin(9600);
}

void loop(void) {
  caller();
}
