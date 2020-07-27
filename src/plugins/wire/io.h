#ifndef SIMPLE_RPC_WIRE_IO_H_
#define SIMPLE_RPC_WIRE_IO_H_

#include <Wire.h>

class WireIO {
  public:
    WireIO(void) {}
    void begin(TwoWire&);
    size_t available(void);
    size_t read(unsigned char*, size_t);
    size_t write(unsigned char*, size_t);
  private:
    TwoWire* _tw;
};

#endif
