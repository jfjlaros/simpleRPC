#ifndef SIMPLE_RPC_SOFTWARESERIAL_IO_H_
#define SIMPLE_RPC_SOFTWARESERIAL_IO_H_

#include <SoftwareSerial.h>

class SoftwareSerialIO {
  public:
    SoftwareSerialIO(void) {}
    void begin(SoftwareSerial&);
    size_t available(void);
    size_t read(unsigned char*, size_t);
    size_t write(unsigned char*, size_t);
  private:
    SoftwareSerial* _ss;
};

#endif
