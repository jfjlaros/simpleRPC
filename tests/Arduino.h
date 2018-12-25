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
           write(String);
    template<class T> T _read(void);
    template<class T> size_t _write(T);
    template<class T> T inspect(void);
    template<class... Args> size_t prepare(Args...);
    size_t rx,
           tx;
    char rxBuffer[_BUFFER_SIZE],
         txBuffer[_BUFFER_SIZE];
  private:
    template<class T> T _inspect(void);
    inline size_t _prepare(void);
    template<class... Args> size_t _prepare(const char *, Args...);
    template<class T, class... Args> size_t _prepare(T, Args...);

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

template<>
inline String HardwareSerial::_inspect(void) {
  size_t size = strchr(txBuffer, '\0') - rxBuffer+ 1;

  return ((String)txBuffer).substr(0, size - 1);
}

template<class T>
T HardwareSerial::inspect(void) {
  T data;

  reset();
  data = _inspect<T>();
  reset();

  return data;
}

inline size_t HardwareSerial::_prepare(void) {
  return 0;
}

template<class... Args>
size_t HardwareSerial::_prepare(const char *data, Args... args) {
  size_t size = strlen(data);

  strcpy(&rxBuffer[rx], data);
  rx += size + 1;

  return size + _prepare(args...);
}

template<class T, class... Args>
size_t HardwareSerial::_prepare(T data, Args... args) {
  strncpy(&rxBuffer[rx], (char *)&data, sizeof(T));
  rx += sizeof(T);

  return sizeof(T) + _prepare(args...);
}

template<class... Args>
size_t HardwareSerial::prepare(Args... args) {
  size_t size;

  reset();
  size = _prepare(args...);
  reset();

  return size;
}


extern HardwareSerial Serial;

#endif
