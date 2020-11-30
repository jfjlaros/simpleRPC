#ifndef SIMPLE_RPC_STREAM_IO_H_
#define SIMPLE_RPC_STREAM_IO_H_

#include <Arduino.h>

class StreamIO {
  public:
    StreamIO(void) {}
    void begin(Stream&);
    size_t available(void);
    size_t readBytes(char*, size_t);
    size_t write(byte*, size_t);
  private:
    Stream* _ss;
};

typedef StreamIO SoftwareSerialIO;
typedef StreamIO HardwareSerialIO;

#endif
