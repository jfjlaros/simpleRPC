#ifndef SIMPLE_RPC_WRITE_TCC_
#define SIMPLE_RPC_WRITE_TCC_

/**
 * Serial write functions.
 */

#include <Arduino.h>

#include "defs.h"
#include "tuple.tcc"
#include "vector.tcc"


/*
 * Prototypes needed for recursive definitions.
 */
template <class I, class T>
  void _write(I&, Vector<T>*);
template <class I, class T, class... Args>
  void _write(I&, Tuple<T, Args...>*);
template <class I, class... Args>
  void _write(I&, Object<Args...>*);
template <class I, class T, class... Args>
  void write(I&, T, Args...);


/**
 * Write a value of basic type to serial.
 *
 * @param data Data.
 */
template <class I, class T>
void _write(I& io, T* data) {
  io.write((byte*)data, sizeof(T));
}

/**
 * Write a value of type @a String to serial.
 *
 * @param data String.
 */
template <class I>
void _write(I io, String* data) {
  xrite(io, *data); // TODO: Resolve this weird recursion.
  xrite(io, _END_OF_STRING);
}

template <class I, class T>
void xrite(I& io, T data) {
  _write(io, &data);
}

template <class I>
void xrite(I& io, const char* data) {
  size_t i = 0;

  while (data[i] != _END_OF_STRING) {
    xrite(io, data[i]);
    i++;
  }
}

template <class I>
void xrite(I& io, String& data) {
  xrite(io, data.c_str());
}

template <class I>
void xrite(I& io, const __FlashStringHelper* data) {
  const char* p = (const char*)data;
  byte c = pgm_read_byte(p);

  while (c) {
    xrite(io, c);
    p++;
    c = pgm_read_byte(p);
  }
}

template <class I, class H, class... Tail>
void xrite(I& io, H data, Tail... tail) {
  xrite(io, data);
  xrite(io, tail...);
}

/**
 * Write a value of type @a Vector to serial.
 *
 * @param data Vector.
 */
template <class I, class T>
void _write(I& io, Vector<T>* data) {
  int i;

  _write(io, &(*data).size);
  for (i = 0; i < (*data).size; i++) {
    _write(io, &(*data)[i]);
  }
}


/**
 * Recursion terminator for @a _write(Tuple*)().
 *
 * @private
 */
template <class I>
void _write(I&, Tuple<>*) {}

/**
 * Write a value of type @a Tuple to serial.
 *
 * @param data Tuple.
 */
template <class I, class T, class... Args>
void _write(I& io, Tuple<T, Args...>* data) {
  _write(io, &(*data).head);
  _write(io, &(*data).tail);
}


/**
 * Write a value of type @a Object to serial.
 *
 * @param data Object.
 */
template <class I, class... Args>
void _write(I& io, Object<Args...>* data) {
  _write(io, (Tuple<Args...>*)data);
}

#endif
