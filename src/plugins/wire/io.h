#ifndef SIMPLE_RPC_WIRE_IO_H_
#define SIMPLE_RPC_WIRE_IO_H_

#include <Wire.h>

class WireIO {
  public:
    WireIO(void) {}
    void begin(TwoWire&);
    size_t available(void);
    size_t readBytes(uint8_t*, size_t);
    size_t write(uint8_t*, size_t);
  private:
    TwoWire* _tw;
};

#endif
