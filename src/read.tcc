#ifndef SIMPLE_RPC_READ_TCC_
#define SIMPLE_RPC_READ_TCC_

/**
 * Serial read functions.
 */

#include <Arduino.h>

#include "defs.h"
#include "tuple.tcc"
#include "vector.tcc"


/*
 * Prototypes needed for recursive definitions.
 */
template <class I, class T>
  void rpcRead(I&, Vector<T>*);
template <class I, class T, class... Args>
  void rpcRead(I&, Tuple<T, Args...>*);
template <class I, class... Args>
  void rpcRead(I&, Object<Args...>*);


/**
 * Read a value of basic type from serial.
 *
 * @param io Input / output object.
 * @param data Data.
 */
template <class I, class T>
void rpcRead(I& io, T* data) {
  io.read((byte*)data, sizeof(T));
}

/**
 * Read a value of type @a String from serial.
 *
 * @param io Input / output object.
 * @param data String.
 */
template <class I>
void rpcRead(I& io, String* data) {
  byte character;

  io.read((&character), sizeof(byte));

  while (character != _END_OF_STRING) {
    *data += character;
    io.read((&character), sizeof(byte));
  }
}

/**
 * Read a value of type @a Vector from serial.
 *
 * @param io Input / output object.
 * @param data Vector.
 */
template <class I, class T>
void rpcRead(I& io, Vector<T>* data) {
  size_t size;
  int i;


  rpcRead(io, &size);
  (*data).resize(size);

  for (i = 0; i < (*data).size; i++) {
    rpcRead(io, &(*data)[i]);
  }
}


/**
 * Recursion terminator for @a rpcRead(Tuple*)().
 */
template <class I>
void rpcRead(I&, Tuple<>*) {}

/**
 * Read a value of type @a Tuple from serial.
 *
 * @param io Input / output object.
 * @param data Tuple.
 */
template <class I, class T, class... Args>
void rpcRead(I& io, Tuple<T, Args...>* data) {
  rpcRead(io, &(*data).head);
  rpcRead(io, &(*data).tail);
}


/**
 * Read a value of type @a Object from serial.
 *
 * @param io Input / output object.
 * @param data Object.
 */
template <class I, class... Args>
void rpcRead(I& io, Object<Args...>* data) {
  rpcRead(io, (Tuple<Args...>*)data);
}

#endif
