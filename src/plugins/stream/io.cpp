#include "io.h"


void StreamIO::begin(Stream& ss) {
  _ss = &ss;
}

size_t StreamIO::available(void) {
  return (size_t)_ss->available();
}

size_t StreamIO::readBytes(char* buffer, size_t size) {
  return _ss->readBytes(buffer, size);
}

size_t StreamIO::write(byte* buffer, size_t size) {
  return _ss->write((byte const*)buffer, size);
}
