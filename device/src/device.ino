#include "simpleRPC.h"


int testInt(void) {
  return 1;
}

float testFloat(void) {
  return 1.6180339887;
}

int add(int a, int b) {
  return a + b;
}

void setLed(int brightness) {
  analogWrite(13, brightness);
}


void setup(void) {
  Serial.begin(9600);
}

void loop(void) {
  interface();
}
