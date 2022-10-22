#pragma once

#include "print.tcc"
#include "tuple.tcc"
#include "vector.tcc"

//! \defgroup write


/*! \ingroup write
 * Write a value to an stream.
 *
 * \param io Stream.
 * \param data Data.
 */
template <class T>
void rpcWrite(Stream& io, T* data) {
  uint8_t data_[sizeof(T)];
  memcpy(data_, data, sizeof(T));
  io.write(data_, sizeof(T));
}


/*! \ingroup write
 * \copydoc rpcWrite(Stream&, T*) */
inline void rpcWrite(Stream& io, char** data) {
  rpcPrint(io, *data, '\0');
}

/*! \ingroup write
 * \copydoc rpcWrite(Stream&, T*) */
inline void rpcWrite(Stream& io, char const** data) {
  rpcWrite(io, const_cast<char**>(data));
}

/*! \ingroup write
 * \copydoc rpcWrite(Stream&, T*) */
inline void rpcWrite(Stream& io, String* data) {
  rpcPrint(io, *data, '\0');
}


/*! \ingroup write
 * \copydoc rpcWrite(Stream&, T*) */
template <class T>
void rpcWrite(Stream& io, Vector<T>* data) {
  rpcWrite(io, &(*data).size);

  for (size_t i = 0; i < (*data).size; i++) {
    rpcWrite(io, &(*data)[i]);
  }
}


//! Recursion terminator for `rpcWrite(Tuple*)()`.
inline void rpcWrite(Stream&, Tuple<>*) {}

/*! \ingroup write
 * \copydoc rpcWrite(Stream&, T*) */
template <class... Membs>
void rpcWrite(Stream& io, Tuple<Membs...>* data) {
  rpcWrite(io, &(*data).head);
  rpcWrite(io, &(*data).tail);
}


/*! \ingroup write
 * \copydoc rpcWrite(Stream&, T*) */
template <class... Membs>
void rpcWrite(Stream& io, Object<Membs...>* data) {
  rpcWrite(io, dynamic_cast<Tuple<Membs...>*>(data));
}
