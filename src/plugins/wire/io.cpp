#include "io.h"


void WireIO::begin(TwoWire& tw) {
  _tw = &tw;
}

size_t WireIO::available(void) {
  return (size_t)_tw->available();
}

size_t WireIO::read(byte* buffer, size_t size) {
  size_t i;

  for (i = 0; i < size; i++) {
    buffer[i] = (byte)_tw->read();
  }

  return i;
}

size_t WireIO::write(byte* buffer, size_t size) {
  return _tw->write(buffer, size);
}
