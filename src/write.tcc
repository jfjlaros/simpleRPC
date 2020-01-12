#ifndef SIMPLE_RPC_WRITE_TCC_
#define SIMPLE_RPC_WRITE_TCC_

/**
 * Write functions.
 */

#include "print.tcc"
#include "tuple.tcc"
#include "vector.tcc"


/*
 * Prototypes needed for recursive definitions.
 */
template <class I, class T>
  void rpcWrite(I&, Vector<T>*);
template <class I, class T, class... Args>
  void rpcWrite(I&, Tuple<T, Args...>*);
template <class I, class... Args>
  void rpcWrite(I&, Object<Args...>*);
template <class I, class T, class... Args>
  void write(I&, T, Args...);


/**
 * Write a value of basic type.
 *
 * @param io Input / output object.
 * @param data Data.
 */
template <class I, class T>
void rpcWrite(I& io, T* data) {
  io.write((byte*)data, sizeof(T));
}

/**
 * Write a value of type @a String.
 *
 * @param io Input / output object.
 * @param data String.
 */
template <class I>
void rpcWrite(I io, String* data) {
  rpcPrint(io, *data);
  rpcPrint(io, _END_OF_STRING);
}

/**
 * Write a value of type @a Vector.
 *
 * @param io Input / output object.
 * @param data Vector.
 */
template <class I, class T>
void rpcWrite(I& io, Vector<T>* data) {
  int i;

  rpcWrite(io, &(*data).size);
  for (i = 0; i < (*data).size; i++) {
    rpcWrite(io, &(*data)[i]);
  }
}


/**
 * Recursion terminator for @a rpcWrite(Tuple*)().
 *
 * @private
 */
template <class I>
void rpcWrite(I&, Tuple<>*) {}

/**
 * Write a value of type @a Tuple.
 *
 * @param io Input / output object.
 * @param data Tuple.
 */
template <class I, class T, class... Args>
void rpcWrite(I& io, Tuple<T, Args...>* data) {
  rpcWrite(io, &(*data).head);
  rpcWrite(io, &(*data).tail);
}


/**
 * Write a value of type @a Object.
 *
 * @param io Input / output object.
 * @param data Object.
 */
template <class I, class... Args>
void rpcWrite(I& io, Object<Args...>* data) {
  rpcWrite(io, (Tuple<Args...>*)data);
}

#endif
