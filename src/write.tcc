#ifndef __SIMPLE_RPC_WRITE_TCC__
#define __SIMPLE_RPC_WRITE_TCC__

#include <Arduino.h>

#include "print.tcc"
#include "tuple.tcc"
#include "vector.tcc"

/*
 * Prototypes needed for recursive definitions.
 */
template<class T>
  void _write(Vector <T> *);
template<class T, class... Args>
  void _write(Tuple <T, Args...> *);
template<class... Args>
  void _write(Object <Args...> *);


/**
 * Write a value of basic type to serial.
 *
 * @arg {T *} data - Data.
 */
template<class T>
void _write(T *data) {
  Serial.write((byte *)data, sizeof(T));
}

/**
 * Write a value of type String to serial.
 *
 * @arg {String *} data - String.
 */
inline void _write(String *data) {
  multiPrint(*data, _END_OF_STRING);
}

/**
 * Write a value of type Vector to serial.
 *
 * @arg {Vector <T> *} data - Vector.
 */
template<class T>
void _write(Vector <T> *data) {
  int i;

  _write(&(*data).size);
  for (i = 0; i < (*data).size; i++) {
    _write(&(*data)[i]);
  }
}


/**
 * Recursion terminator for {_write(Tuple *)()}.
 */
inline void _write(Tuple <> *) {}

/**
 * Write a value of type Tuple to serial.
 *
 * @arg {Tuple <T, Args...> *} data - Tuple.
 */
template<class T, class... Args>
void _write(Tuple <T, Args...> *data) {
  _write(&(*data).head);
  _write(&(*data).tail);
}


/**
 * Write a value of type Object to serial.
 *
 * @arg {Object <Args...> *} data - Object.
 */
template<class... Args>
void _write(Object <Args...> *data) {
  _write((Tuple <Args...>*)data);
}

#endif
