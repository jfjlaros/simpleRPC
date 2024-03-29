#pragma once

#include <Stream.h>


class HalfDuplexStream : public Stream {
public:
  HalfDuplexStream(Stream&, uint8_t, unsigned long=1000);

  virtual void begin();
  virtual int available();
  virtual int peek();
  virtual int read();
  virtual size_t write(uint8_t);
  virtual size_t write(uint8_t const*, size_t);

private:
  Stream* stream_;
  uint8_t pin_;
  unsigned long delay_;
};
