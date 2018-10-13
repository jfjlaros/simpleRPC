#include "interface.h"


int bla(void) {
  return 1;
}

int add(int a, int b) {
  return a + b;
}


void setup(void) {
  Serial.begin(9600);
}

void loop(void) {
  if (Serial.available()) {
    caller();
  }
}
