#ifndef SIMPLE_RPC_DEL_TCC_
#define SIMPLE_RPC_DEL_TCC_

/**
 * @file del.tcc
 *
 * Delete functions.
 */
#include "tuple.tcc"


/**
 * Delete a basic type.
 *
 * @param data Data.
 */
template <class T>
void rpcDel(T* data) {}


/**
 * Delete an array.
 *
 * @param data Array of type @a T*.
 */
template <class T>
void rpcDel(T** data) {
  free(*data);
}

/// @private Delete an array of type @a const T*.
template <class T>
void rpcDel(const T** data) {
  rpcDel((T**)data);
}


/**
 * Recursion terminator for @a rpcDel(Tuple*)().
 *
 * @private
 */
inline void rpcDel(Tuple<>*) {}

/**
 * Delete a @a Tuple.
 *
 * @param data Tuple.
 */
template <class T, class... Args>
void rpcDel(Tuple<T, Args...>* data) {
  rpcDel(&(*data).head);
  rpcDel(&(*data).tail);
}


/**
 * Delete an @a Object.
 *
 * @param data Object.
 */
template <class... Args>
void rpcDel(Object<Args...>* data) {
  rpcDel((Tuple<Args...>*)data);
}

#endif
