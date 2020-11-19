#include "io.h"


void StreamIO::begin(Stream& ss) {
  _ss = &ss;
}

size_t StreamIO::available(void) {
  return (size_t)_ss->available();
}

size_t StreamIO::read(byte* buffer, size_t size) {
  return _ss->readBytes((char*)buffer, size);
}

size_t StreamIO::write(byte* buffer, size_t size) {
  return _ss->write((byte const*)buffer, size);
}
