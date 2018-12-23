#ifndef __ARDUINO_H__
#define __ARDUINO_H__

#include <string.h>
#include <string>

#define _BUFFER_SIZE 128

using namespace std;

typedef string String;
typedef unsigned char byte;


class HardwareSerial {
  public:
    HardwareSerial(void);
    void reset(void);
    bool available(void);
    byte read(void);
    void readBytes(char *buf, size_t size);
    String readStringUntil(char);
    size_t write(char),
           write(byte *, size_t),
           write(string);
    size_t rx,
           tx;
    char rxBuffer[_BUFFER_SIZE],
         txBuffer[_BUFFER_SIZE];

};


extern HardwareSerial Serial;


/**
 * Read from serial.
 *
 * @return {T} - Value.
 */
template<class T>
T _read(void) {
  T data;

  Serial.readBytes((char *)&data, sizeof(T));

  return data;
}

/**
 * Write to serial.
 *
 * @arg {T} data - Value.
 */
template<class T>
size_t _write(T data) {
  Serial.write((byte *)&data, sizeof(T));
}

#endif
