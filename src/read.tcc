#pragma once

#include "tuple.tcc"
#include "vector.tcc"
#include "array.tcc"

class String_ : public Vector<char> {};

//! \defgroup read


/*! \ingroup read
 * Read a value from a stream.
 *
 * \tparam T Data type.
 *
 * \param io Stream.
 * \param data Data.
 */
template <class T>
void rpcRead(Stream& io, T* data) {
  io.readBytes(reinterpret_cast<char*>(data), sizeof(T));
}


/*! \ingroup read
 * \copydoc rpcRead(Stream&, T*) */
inline void rpcRead(Stream& io, String* data) {
  char c {};
  rpcRead(io, &c);

  while (c) {
    *data += c;
    rpcRead(io, &c);
  }
}

/*! \ingroup read
 * \copydoc rpcRead(Stream&, T*) */
inline void rpcRead(Stream& io, String_* data) {
  char c {};
  rpcRead(io, &c);

  while (c) {
    (*data).push_back(c);
    rpcRead(io, &c);
  }
}

/*! \ingroup read
 * \copydoc rpcRead(Stream&, T*) */
template <class T>
void rpcRead(Stream& io, Vector<T>* data) {
  size_t size;
  rpcRead(io, &size);

  (*data).resize(size);
  for (T& el: *data) {
    rpcRead(io, &el);
  }
}

/*! \ingroup read
 * \copydoc rpcRead(Stream&, T*) */
template <class T, size_t n>
void rpcRead(Stream& io, Array<T, n>* data) {
  for (T& el: *data) {
    rpcRead(io, &el);
  }
}


//! Recursion terminator for `rpcRead(Tuple*)`.
inline void rpcRead(Stream&, Tuple<>*) {}

/*! \ingroup read
 * \copydoc rpcRead(Stream&, T*) */
template <class... Ts>
void rpcRead(Stream& io, Tuple<Ts...>* data) {
  rpcRead(io, &(*data).head);
  rpcRead(io, &(*data).tail);
}
