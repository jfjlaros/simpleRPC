#include "Arduino.h"


/**
 * Constructor.
 */
HardwareSerial::HardwareSerial(void) {
  reset();
}

/**
 * Reset the internal counters.
 */
void HardwareSerial::reset(void) {
  rx = 0;
  tx = 0;
}

/*
 * Functions that record the number of bytes read or written.
 */

void HardwareSerial::readBytes(char *buf, size_t size) {
  rx += size;
}

String HardwareSerial::readStringUntil(char) {
  rx += 3;

  return "xxx";
}

size_t HardwareSerial::write(byte *, size_t size) {
  tx += size;

  return size;
}

size_t HardwareSerial::write(char) {
  tx++;

  return 1;
}

size_t HardwareSerial::write(string s) {
  tx += s.length();

  return s.length();
}


HardwareSerial Serial;
