#ifndef SIMPLE_RPC_SERIAL_IO_H_
#define SIMPLE_RPC_SERIAL_IO_H_

#include <Arduino.h>

class RWIO {
  public:
    RWIO(void) {}
    void begin(unsigned long);
    size_t available(void),
           read(byte*, size_t),
           write(byte*, size_t);
};

#endif
