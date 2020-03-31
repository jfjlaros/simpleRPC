#ifndef SIMPLE_RPC_READ_TCC_
#define SIMPLE_RPC_READ_TCC_

/**
 * Read functions.
 */

#include "defs.h"
#include "tuple.tcc"
#include "vector.tcc"


/**
 * Read a value of basic type.
 *
 * @param io Input / output object.
 * @param data Data.
 */
template <class I, class T>
void rpcRead(I& io, T* data) {
  io.read((byte*)data, sizeof(T));
}


/**
 * Read a value of type @a String.
 *
 * @param io Input / output object.
 * @param data String.
 */
template <class I>
void rpcRead(I& io, String* data) {
  char character;

  io.read(((byte*)&character), sizeof(char));

  while (character != _END_OF_STRING) {
    *data += character;
    io.read(((byte*)&character), sizeof(char));
  }
}

/// @private C string of type @a char*.
template <class I>
void rpcRead(I& io, char** data) {
  String s;

  rpcRead(io, &s);
  *data = (char*)malloc((s.length() + 1) * sizeof(char));
  strcpy(*data, s.c_str());
}

/// @private C string of type @a const char*.
template <class I>
void rpcRead(I& io, const char** data) {
  rpcRead(io, (char**)data);
}


/**
 * Read a value of type @a Vector.
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
 *
 * @private
 */
template <class I>
void rpcRead(I&, Tuple<>*) {}

/**
 * Read a value of type @a Tuple.
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
 * Read a value of type @a Object.
 *
 * @param io Input / output object.
 * @param data Object.
 */
template <class I, class... Args>
void rpcRead(I& io, Object<Args...>* data) {
  rpcRead(io, (Tuple<Args...>*)data);
}

#endif
