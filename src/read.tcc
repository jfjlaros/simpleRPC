#ifndef __SIMPLE_RPC_READ_TCC__
#define __SIMPLE_RPC_READ_TCC__

#include <Arduino.h>

#include "defs.h"
#include "tuple.tcc"
#include "vector.tcc"

/*
 * Prototypes needed for recursive definitions.
 */
template <class T>
  void _read(Vector<T>*);
template <class T, class... Args>
  void _read(Tuple<T, Args...>*);
template <class... Args>
  void _read(Object<Args...>*);


/**
 * Read a value of basic type from serial.
 *
 * @arg {T*} data - Data.
 */
template <class T>
void _read(T* data) {
  Serial.readBytes((char*)data, sizeof(T));
}

/**
 * Read a value of type String from serial.
 *
 * @arg {String*} data - String.
 */
inline void _read(String* data) {
  *data = Serial.readStringUntil(_END_OF_STRING);
}

/**
 * Read a value of type Vector from serial.
 *
 * @arg {Vector<T>*} data - Vector.
 */
template <class T>
void _read(Vector<T>* data) {
  size_t size;
  int i;


  _read(&size);
  (*data).resize(size);

  for (i = 0; i < (*data).size; i++) {
    _read(&(*data)[i]);
  }
}


/**
 * Recursion terminator for {_read(Tuple*)()}.
 */
inline void _read(Tuple<>*) {}

/**
 * Read a value of type Tuple from serial.
 *
 * @arg {Tuple<T, Args...>*} data - Tuple.
 */
template <class T, class... Args>
void _read(Tuple<T, Args...>* data) {
  _read(&(*data).head);
  _read(&(*data).tail);
}


/**
 * Read a value of type Object from serial.
 *
 * @arg {Object<Args...>*} data - Object.
 */
template <class... Args>
void _read(Object<Args...>* data) {
  _read((Tuple<Args...>*)data);
}

#endif
