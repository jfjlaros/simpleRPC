#include "stream.h"
#include <Arduino.h>


HalfDuplexStream::HalfDuplexStream(Stream& stream, int transmit_pin, unsigned long transmit_delay_microseconds) :
_stream(&stream), _transmit_pin(transmit_pin), _transmit_delay_microseconds(transmit_delay_microseconds) {
}

void HalfDuplexStream::begin() {
  pinMode(_transmit_pin, OUTPUT);
  digitalWrite(_transmit_pin, LOW);
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

size_t HalfDuplexStream::write(const uint8_t *buffer, size_t size) {
  digitalWrite(_transmit_pin, HIGH);
  int result = _stream->write(buffer, size);
  _stream->flush();
  delayMicroseconds(_transmit_delay_microseconds);
  digitalWrite(_transmit_pin, LOW);
  return result;
}
