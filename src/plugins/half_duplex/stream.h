#ifndef SIMPLE_RPC_HALF_DUPLEX_STREAM_H_
#define SIMPLE_RPC_HALF_DUPLEX_STREAM_H_

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
    Stream* _stream;
    uint8_t _pin;
    unsigned long _delay;
};

#endif
