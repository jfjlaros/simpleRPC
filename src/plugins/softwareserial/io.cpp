#include "io.h"


void SoftwareSerialIO::begin(SoftwareSerial& ss) {
  _ss = &ss;
}

size_t SoftwareSerialIO::available(void) {
  return (size_t)_ss->available();
}

size_t SoftwareSerialIO::read(uint8_t* buffer, size_t size) {
  return _ss->readBytes((char*)buffer, size);
}

size_t SoftwareSerialIO::write(uint8_t* buffer, size_t size) {
  return _ss->write((uint8_t const*)buffer, size);
}
