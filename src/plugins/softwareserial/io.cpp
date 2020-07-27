#include "io.h"


void SoftwareSerialIO::begin(SoftwareSerial& ss) {
  _ss = &ss;
}

size_t SoftwareSerialIO::available(void) {
  return (size_t)_ss->available();
}

size_t SoftwareSerialIO::read(unsigned char* buffer, size_t size) {
  return _ss->readBytes((char*)buffer, size);
}

size_t SoftwareSerialIO::write(unsigned char* buffer, size_t size) {
  return _ss->write((unsigned char const*)buffer, size);
}
