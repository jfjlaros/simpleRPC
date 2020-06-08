#ifndef SIMPLE_RPC_HARDWARESERIAL_IO_H_
#define SIMPLE_RPC_HARDWARESERIAL_IO_H_

#include <Arduino.h>

class HardwareSerialIO {
  public:
    HardwareSerialIO(void) {}
    void begin(HardwareSerial&);
    size_t available(void);
    size_t read(byte*, size_t);
    size_t write(byte*, size_t);
  private:
    HardwareSerial* _hs;
};

#endif
