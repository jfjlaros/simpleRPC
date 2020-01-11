#ifndef SIMPLE_RPC_WRITE_TCC_
#define SIMPLE_RPC_WRITE_TCC_

/**
 * Serial write functions.
 */

#include <Arduino.h>

//#include "print.tcc"
#include "tuple.tcc"
#include "vector.tcc"

#include "serial/io.h"
extern RWIO IO;


/*
 * Prototypes needed for recursive definitions.
 */
template <class T>
  void _write(Vector<T>*);
template <class T, class... Args>
  void _write(Tuple<T, Args...>*);
template <class... Args>
  void _write(Object<Args...>*);
template <class T, class... Args>
  void write(T, Args...);


/**
 * Write a value of basic type to serial.
 *
 * @param data Data.
 */
template <class T>
void _write(T* data) {
  IO.write((byte*)data, sizeof(T));
}

/**
 * Write a value of type @a String to serial.
 *
 * @param data String.
 */
//inline void _write(String* data) {
//  //write((*data).c_str(), _END_OF_STRING);
//  byte m = 'X';
//
//  IO.write(&m, 1);
//  IO.write((byte*)(*data).c_str(), (*data).length());
//  IO.write(_END_OF_STRING, sizeof(byte));
//}

template <class T>
void xrite(T data) {
  _write(&data);
}

inline void xrite(const char* data) {
  size_t i = 0;

  while (data[i] != _END_OF_STRING) {
    xrite(data[i]);
    i++;
  }
}

inline void xrite(String data) {
  xrite(data.c_str());
}

inline void xrite(const __FlashStringHelper* data) {
  const char* __attribute__((progmem)) p = (const char*)data;
  byte c = pgm_read_byte(p);

  while (c) {
    xrite(c);
    p++;
    c = pgm_read_byte(p);
  }
}

template <class H, class... Tail>
void xrite(H data, Tail... tail) {
  xrite(data);
  xrite(tail...);
}

/**
 * Write a value of type @a Vector to serial.
 *
 * @param data Vector.
 */
template <class T>
void _write(Vector<T>* data) {
  int i;

  _write(&(*data).size);
  for (i = 0; i < (*data).size; i++) {
    _write(&(*data)[i]);
  }
}


/**
 * Recursion terminator for @a _write(Tuple*)().
 *
 * @private
 */
inline void _write(Tuple<>*) {}

/**
 * Write a value of type @a Tuple to serial.
 *
 * @param data Tuple.
 */
template <class T, class... Args>
void _write(Tuple<T, Args...>* data) {
  _write(&(*data).head);
  _write(&(*data).tail);
}


/**
 * Write a value of type @a Object to serial.
 *
 * @param data Object.
 */
template <class... Args>
void _write(Object<Args...>* data) {
  _write((Tuple<Args...>*)data);
}


/* TODO: Documentation */
//inline void write(void) {}

/* TODO: Documentation */
//template <class T, class... Args>
//void write(T data, Args... args) {
//  _write(&data);
//  write(args...);
//}

#endif
