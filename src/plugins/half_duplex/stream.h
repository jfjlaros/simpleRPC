#ifndef HALF_DUPLEX_STREAM_H
#define HALF_DUPLEX_STREAM_H

#include <Stream.h>


class HalfDuplexStream : public Stream
{
public:
  HalfDuplexStream(Stream& stream, int _transmit_pin, unsigned long transmit_delay_microseconds=1000);
  virtual void begin();
  virtual int available();
  virtual int peek();
  virtual int read();
  virtual size_t write(uint8_t);
  virtual size_t write(const uint8_t *buffer, size_t size);

private:
  Stream* _stream;
  int _transmit_pin;
  unsigned long _transmit_delay_microseconds;
};

#endif
