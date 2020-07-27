#include "io.h"


void HardwareSerialIO::begin(HardwareSerial& hs) {
  _hs = &hs;
}

size_t HardwareSerialIO::available(void) {
  return (size_t)_hs->available();
}

size_t HardwareSerialIO::read(unsigned char* buffer, size_t size) {
  return _hs->readBytes((char*)buffer, size);
}

size_t HardwareSerialIO::write(unsigned char* buffer, size_t size) {
  return _hs->write((unsigned char const*)buffer, size);
}
