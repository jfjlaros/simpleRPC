#ifndef __ARDUINO_H__
#define __ARDUINO_H__

#include <string>

using namespace std;

typedef string String;
typedef unsigned char byte;


class HardwareSerial {
  public:
    HardwareSerial(void);
    void reset(void),
         readBytes(char *buf, size_t size);
    String readStringUntil(char);
    byte read(void);
    size_t write(byte *, size_t),
           write(char),
           write(string);
    bool available(void);
    size_t rx,
           tx;
    string rxBuf,
           txBuf;
};


extern HardwareSerial Serial;

#endif
