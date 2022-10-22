#include <Arduino.h>

#include "stream.h"


HalfDuplexStream::HalfDuplexStream(
    Stream& stream, uint8_t pin, unsigned long delay) {
  stream_ = &stream;
  pin_ = pin;
  delay_ = delay;
}

void HalfDuplexStream::begin() {
  pinMode(pin_, OUTPUT);
  digitalWrite(pin_, LOW);
}

int HalfDuplexStream::available() {
  return stream_->available();
}

int HalfDuplexStream::peek() {
  return stream_->peek();
}

int HalfDuplexStream::read() {
  return stream_->read();
}

size_t HalfDuplexStream::write(uint8_t b) {
  return stream_->write(b);
}

size_t HalfDuplexStream::write(uint8_t const* buffer, size_t size) {
  digitalWrite(pin_, HIGH);

  int result = stream_->write(buffer, size);
  stream_->flush();
  delayMicroseconds(delay_);

  digitalWrite(pin_, LOW);

  return result;
}
