#include "io.h"


void RWIO::begin(unsigned long speed) {
  Serial.begin(speed);
}

size_t RWIO::available(void) {
  return (size_t)Serial.available();
}

size_t RWIO::read(byte* buffer, size_t size) {
  return Serial.readBytes((char *)buffer, size);
}

size_t RWIO::write(byte* buffer, size_t size) {
  return Serial.write((const byte*)buffer, size);
}
