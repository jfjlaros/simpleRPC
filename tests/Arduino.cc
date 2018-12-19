#include "Arduino.h"


HardwareSerial::HardwareSerial(void) {
  reset();
}

void HardwareSerial::reset(void) {
  rx = 0;
  tx = 0;
}

void HardwareSerial::readBytes(char *buf, size_t size) {
  int i;

  for (i = 0; i < size; i++) {
    buf[i] = 'x';
    rx++;
  }
}

size_t HardwareSerial::write(byte *, size_t size) {
  tx += size;

  return size;
}

size_t HardwareSerial::write(char) {
  tx += 1;

  return 1;
}

size_t HardwareSerial::write(string s) {
  int length = s.length();

  tx += length;

  return length;
}

String HardwareSerial::readStringUntil(char) {
  String s = "xxx";

  rx += s.length();

  return s;
}


HardwareSerial Serial;
