#ifndef SIMPLE_RPC_SOFTWARESERIAL_IO_H_
#define SIMPLE_RPC_SOFTWARESERIAL_IO_H_

#include <Arduino.h>
#include <SoftwareSerial.h>

class SoftwareSerialIO {
  public:
    SoftwareSerialIO(uint8_t txPin, uint8_t rxPin) : _ss(txPin, rxPin) {}
    void begin(unsigned long);
    size_t available(void),
           read(byte*, size_t),
           write(byte*, size_t);
  private:
    SoftwareSerial _ss;
};

#endif
