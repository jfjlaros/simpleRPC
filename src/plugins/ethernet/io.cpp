#include "io.h"


void EthernetIO::begin(EthernetServer& es) {
  _es = &es;
}

size_t EthernetIO::available(void) {
  *_ec = _es->available();

  return (size_t)_ec->available();
}

size_t EthernetIO::read(byte* buffer, size_t size) {
  return _ec->read(buffer, size);
}

size_t EthernetIO::write(byte* buffer, size_t size) {
  return _es->write(buffer, size);
}
