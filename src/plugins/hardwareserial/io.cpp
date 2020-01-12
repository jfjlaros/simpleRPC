#include "io.h"


void HardwareSerialIO::begin(unsigned long speed) {
  Serial.begin(speed);
}

size_t HardwareSerialIO::available(void) {
  return (size_t)Serial.available();
}

size_t HardwareSerialIO::read(byte* buffer, size_t size) {
  return Serial.readBytes((char*)buffer, size);
}

size_t HardwareSerialIO::write(byte* buffer, size_t size) {
  return Serial.write((const byte*)buffer, size);
}
