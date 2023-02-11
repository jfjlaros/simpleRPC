#pragma once

#include "print.tcc"
#include "tuple.tcc"
#include "vector.tcc"
#include "array.tcc"

//! \defgroup write


/*! \ingroup write
 * Write a value to a stream.
 *
 * \param io Stream.
 * \param data Data.
 */
template <class T>
void rpcWrite(Stream& io, T* data) {
  io.write(reinterpret_cast<uint8_t*>(data), sizeof(T));
}


/*! \ingroup write
 * \copydoc rpcWrite(Stream&, T*) */
inline void rpcWrite(Stream& io, char const** data) {
  size_t size {strlen(*data) + 1};
  rpcWrite(io, &size);
  rpcPrint(io, *data, '\0');
}

/*! \ingroup write
 * \copydoc rpcWrite(Stream&, T*) */
inline void rpcWrite(Stream& io, char** data) {
  rpcWrite(io, const_cast<char const**>(data));
}

/*! \ingroup write
 * \copydoc rpcWrite(Stream&, T*) */
inline void rpcWrite(Stream& io, String* data) {
  char const* data_ {(*data).c_str()};
  rpcWrite(io, &data_);
}


/*! \ingroup write
 * \copydoc rpcWrite(Stream&, T*) */
template <class T>
void rpcWrite(Stream& io, Vector<T>* data) {
  size_t size {(*data).size()};
  rpcWrite(io, &size);
  for (size_t i {0}; i < size; ++i) {
    rpcWrite(io, &(*data)[i]);
  }
}

/*! \ingroup write
 * \copydoc rpcWrite(Stream&, T*) */
template <class T, size_t n>
void rpcWrite(Stream& io, Array<T, n>* data) {
  size_t size {(*data).size()};
  rpcWrite(io, &size);
  for (size_t i {0}; i < size; ++i) {
    rpcWrite(io, &(*data)[i]);
  }
}


//! Recursion terminator for `rpcWrite(Tuple*)()`.
inline void rpcWrite(Stream&, Tuple<>*) {}

/*! \ingroup write
 * \copydoc rpcWrite(Stream&, T*) */
template <class... Ts>
void rpcWrite(Stream& io, Tuple<Ts...>* data) {
  rpcWrite(io, &(*data).head);
  rpcWrite(io, &(*data).tail);
}
