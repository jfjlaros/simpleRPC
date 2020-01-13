#include "io.h"


void WiFiIO::begin(WiFiServer& ws) {
  _ws = &ws;
}

size_t WiFiIO::available(void) {
  *_wc = _ws->available();

  return (size_t)_wc->available();
}

size_t WiFiIO::read(byte* buffer, size_t size) {
  return _wc->read(buffer, size);
}

size_t WiFiIO::write(byte* buffer, size_t size) {
  return _ws->write(buffer, size);
}
