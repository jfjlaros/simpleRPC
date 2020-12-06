#include <Arduino.h>

#include "stream.h"


HalfDuplexStream::HalfDuplexStream(
    Stream& stream, uint8_t pin, unsigned long delay) {
  _stream = &stream;
  _pin = pin;
  _delay = delay;
}

void HalfDuplexStream::begin() {
  pinMode(_pin, OUTPUT);
  digitalWrite(_pin, LOW);
}

int HalfDuplexStream::available() {
  return _stream->available();
}

int HalfDuplexStream::peek() {
  return _stream->peek();
}

int HalfDuplexStream::read() {
  return _stream->read();
}

size_t HalfDuplexStream::write(uint8_t b) {
  return _stream->write(b);
}

size_t HalfDuplexStream::write(uint8_t const* buffer, size_t size) {
  digitalWrite(_pin, HIGH);

  int result = _stream->write(buffer, size);
  _stream->flush();
  delayMicroseconds(_delay);

  digitalWrite(_pin, LOW);

  return result;
}
