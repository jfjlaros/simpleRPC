#include "Arduino.h"


void HardwareSerial::readBytes(char *buf, size_t size) {
  int i;

  for (i = 0; i < size; i++) {
    buf[i] = 'x';
  }
}

size_t HardwareSerial::write(byte *, size_t) {
  return 0;
}

size_t HardwareSerial::write(string s) {
  return s.length();
}

String HardwareSerial::readStringUntil(char) {
  return "xxx";
}


HardwareSerial Serial;
