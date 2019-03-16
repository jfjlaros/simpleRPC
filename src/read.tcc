#ifndef __SIMPLE_RPC_READ_TCC__
#define __SIMPLE_RPC_READ_TCC__

#include <Arduino.h>

#include "tuple.tcc"

/*
 * Prototypes needed for recursive definitions.
 */
template<class T>
  void _read(Vector <T> *);
template<class T, class... Args>
  void _read(Tuple <T, Args...> *);
template<class... Args>
  void _read(Object <Args...> *);


/**
 * Read a value of basic type from serial.
 *
 * @arg {T *} data - Data.
 */
template<class T>
void _read(T *data) {
  Serial.readBytes((char *)data, sizeof(T));
}

/**
 * Read a value of type Vector from serial.
 *
 * @arg {Vector <T> *} data - Vector.
 */
template<class T>
void _read(Vector <T> *data) {
  size_t length;
  int i;


  _read(&length);
  (*data).setLength(length);

  for (i = 0; i < (*data).length; i++) {
    _read(&(*data)[i]);
  }
}


/**
 * Recursion terminator for {_read(Tuple *)()}.
 */
void _read(Tuple <> *) {}

/**
 * Read a value of type Tuple from serial.
 *
 * @arg {Tuple <T, Args...> *} data - Tuple.
 */
template<class T, class... Args>
void _read(Tuple <T, Args...> *data) {
  _read(&(*data).head);
  _read(&(*data).tail);
}


/**
 * Read a value of type Object from serial.
 *
 * @arg {Object <Args...> *} data - Object.
 */
template<class... Args>
void _read(Object <Args...> *data) {
  _read(&(*data).members);
}

#endif
