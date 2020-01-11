#ifndef SIMPLE_RPC_READ_TCC_
#define SIMPLE_RPC_READ_TCC_

/**
 * Serial read functions.
 */

#include <Arduino.h>

#include "defs.h"
#include "tuple.tcc"
#include "vector.tcc"

//#include "serial/io.h"
//extern RWIO IO;


/*
 * Prototypes needed for recursive definitions.
 */
template <class I, class T>
  void _read(I&, Vector<T>*);
template <class I, class T, class... Args>
  void _read(I&, Tuple<T, Args...>*);
template <class I, class... Args>
  void _read(I&, Object<Args...>*);


/**
 * Read a value of basic type from serial.
 *
 * @param data Data.
 */
template <class I, class T>
void _read(I& io, T* data) {
  io.read((byte*)data, sizeof(T));
}

/**
 * Read a value of type @a String from serial.
 *
 * @param data String.
 */
template <class I>
void _read(I& io, String* data) {
  byte character;

  io.read((&character), sizeof(byte));

  while (character != _END_OF_STRING) {
    *data += character;
    io.read((&character), sizeof(byte));
  }
  //*data = Serial.readStringUntil(_END_OF_STRING);
}

/**
 * Read a value of type @a Vector from serial.
 *
 * @param data Vector.
 */
template <class I, class T>
void _read(I& io, Vector<T>* data) {
  size_t size;
  int i;


  _read(io, &size);
  (*data).resize(size);

  for (i = 0; i < (*data).size; i++) {
    _read(io, &(*data)[i]);
  }
}


/**
 * Recursion terminator for @a _read(Tuple*)().
 */
template <class I>
void _read(I&, Tuple<>*) {}

/**
 * Read a value of type @a Tuple from serial.
 *
 * @param data Tuple.
 */
template <class I, class T, class... Args>
void _read(I& io, Tuple<T, Args...>* data) {
  _read(io, &(*data).head);
  _read(io, &(*data).tail);
}


/**
 * Read a value of type @a Object from serial.
 *
 * @param data Object.
 */
template <class I, class... Args>
void _read(I& io, Object<Args...>* data) {
  _read(io, (Tuple<Args...>*)data);
}

#endif
