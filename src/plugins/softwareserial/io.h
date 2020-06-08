#ifndef SIMPLE_RPC_SOFTWARESERIAL_IO_H_
#define SIMPLE_RPC_SOFTWARESERIAL_IO_H_

#include <Arduino.h>
#include <SoftwareSerial.h>

class SoftwareSerialIO {
  public:
    SoftwareSerialIO(void) {}
    void begin(SoftwareSerial&);
    size_t available(void);
    size_t read(byte*, size_t);
    size_t write(byte*, size_t);
  private:
    SoftwareSerial* _ss;
};

#endif
