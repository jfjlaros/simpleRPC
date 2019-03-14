#ifndef __SIMPLE_RPC_READ_TCC__
#define __SIMPLE_RPC_READ_TCC__

/*
 * Note that since overloading by return type is not allowed, we have to pass
 * an unused variable, i.e., instead of:
 *
 *   T f(void) {}
 *
 * we have to use:
 *
 *   T f(T) {}
 */
#include <Arduino.h>

#include "tuple.tcc"

/*
 * Prototypes needed for recursive definitions.
 */
template<class T>
  Vector <T>_read(Vector <T>);
template<class T, class... Args>
  Tuple <T, Args...>_read(Tuple <T, Args...>);
template<class... Args>
  Object <Args...>_read(Object <Args...>);


/**
 * Read a value of basic type from serial.
 *
 * @arg {T} - Data type.
 *
 * @return {T} - Data.
 */
template<class T>
T _read(T) {
  T data;

  Serial.readBytes((char *)&data, sizeof(T));

  return data;
}

/**
 * Read a value of type Vector from serial.
 *
 * @arg {Vector <T>} - Vector type.
 *
 * @return {Vector <T>} - Vector.
 */
template<class T>
Vector <T>_read(Vector <T>) {
  Vector <T>data;
  int i;

  data.length = _read(data.length);
  data.data = (T *)malloc(data.length * sizeof(T));

  for (i = 0; i < data.length; i++) {
    data.data[i] = _read(data.data[i]);
  }

  return data;
}

/**
 * Recursion terminator for {_read(Tuple)}.
 */
inline Tuple <>_read(Tuple <>) {}

/**
 * Read a value of type Tuple from serial.
 *
 * @arg {Tuple <T, Args...>} - Tuple type.
 *
 * @return {Tuple <T, Args...>} - Tuple.
 */
template<class T, class... Args>
Tuple <T, Args...>_read(Tuple <T, Args...>) {
  Tuple <T, Args...>data;

  data.head = _read(data.head);
  data.tail = _read(data.tail);

  return data;
}

/**
 * Read a value of type Object from serial.
 *
 * @arg {Object <Args...>} - Object type.
 *
 * @return {Object <Args...>} - Object.
 */
template<class... Args>
Object <Args...>_read(Object <Args...>) {
  Object <Args...>data;

  data.members = _read(data.members);

  return data;
}

#endif
