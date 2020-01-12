#include "io.h"


void SoftwareSerialIO::begin(unsigned long speed) {
  _ss.begin(speed);
}

size_t SoftwareSerialIO::available(void) {
  return (size_t)_ss.available();
}

size_t SoftwareSerialIO::read(byte* buffer, size_t size) {
  return _ss.readBytes((char*)buffer, size);
}

size_t SoftwareSerialIO::write(byte* buffer, size_t size) {
  return _ss.write((const byte*)buffer, size);
}
