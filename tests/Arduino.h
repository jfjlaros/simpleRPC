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
    size_t write(byte *, size_t),
           write(char),
           write(string);
    String readStringUntil(char);
    size_t rx,
           tx;
};


extern HardwareSerial Serial;

#endif
