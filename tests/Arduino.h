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
    template<class T> T _read(void);
    template<class T> size_t _write(T);
    template<class T> T _inspect(void);
    template<class T> size_t _prepare(T);
    size_t rx,
           tx;
    char rxBuffer[_BUFFER_SIZE],
         txBuffer[_BUFFER_SIZE];

};


/**
 * Read from serial.
 *
 * @return {T} - Value.
 */
template<class T>
T HardwareSerial::_read(void) {
  T data;

  readBytes((char *)&data, sizeof(T));

  return data;
}

/**
 * Write to serial.
 *
 * @arg {T} data - Value.
 */
template<class T>
size_t HardwareSerial::_write(T data) {
  return write((byte *)&data, sizeof(T));
}

template<class T>
T HardwareSerial::_inspect(void) {
  T data;

  strncpy((char *)&data, &txBuffer[tx], sizeof(T));
  tx += sizeof(T);

  return data;
}

template<class T>
size_t HardwareSerial::_prepare(T data) {
  strncpy(&rxBuffer[rx], (char *)&data, sizeof(T));
  rx += sizeof(T);

  return sizeof(T);
}


extern HardwareSerial Serial;

#endif
