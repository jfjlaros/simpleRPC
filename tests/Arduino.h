#ifndef __ARDUINO_H__
#define __ARDUINO_H__

#include <string>

using namespace std;

typedef string String;
typedef unsigned char byte;


class HardwareSerial {
  public:
    void readBytes(char *buf, size_t size);
    size_t write(byte *, size_t),
           write(string);
    String readStringUntil(char);
};


extern HardwareSerial Serial;

#endif
