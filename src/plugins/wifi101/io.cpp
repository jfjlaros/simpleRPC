#include "io.h"


void WiFi101IO::begin(WiFiClient& wc) {
  _wc = &wc;
}

size_t WiFi101IO::available(void) {
  return (size_t)_wc->available();
}

size_t WiFi101IO::read(uint8_t* buffer, size_t size) {
  if (_wc->connected()) {
    return _wc->read(buffer, size);
  }
  else {
    _wc->connect(_wc->remoteIP(), _wc->remotePort());
  }
  return -1;
}

size_t WiFi101IO::write(uint8_t* buffer, size_t size) {
  return _wc->write(buffer, size);
}
