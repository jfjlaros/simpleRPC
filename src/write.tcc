#pragma once

#include "tuple.tcc"
#include "vector.tcc"
#include "array.tcc"

//! \defgroup write


/*! \ingroup write
 * Write a value to a stream.
 *
 * \tparam Data type.
 *
 * \param io Stream.
 * \param data Data.
 */
template <class T>
void rpcWrite(Stream& io, T data) {
  io.write(reinterpret_cast<uint8_t*>(&data), sizeof(T));
}

/*! \ingroup write
 * \copydoc rpcWrite(Stream&, T) */
inline void rpcWrite(Stream& io, char const* data) {
  for (size_t i {0}; data[i]; ++i) {
    rpcWrite(io, data[i]);
  }
  rpcWrite(io, '\0');
}

/*! \ingroup write
 * \copydoc rpcWrite(Stream&, T) */
inline void rpcWrite(Stream& io, __FlashStringHelper const* data) {
  char const* p {reinterpret_cast<char const*>(data)};
  for (uint8_t c {pgm_read_byte(p)}; c; c = pgm_read_byte(++p)) {
    rpcWrite(io, c);
  }
  rpcWrite(io, '\0');
}


/*! \ingroup write
 * \copydoc rpcWrite(Stream&, T) */
template <class T>
void rpcWrite(Stream& io, T* data) {
  io.write(reinterpret_cast<uint8_t*>(data), sizeof(T));
}


/*! \ingroup write
 * \copydoc rpcWrite(Stream&, T) */
inline void rpcWrite(Stream& io, char const** data) {
  size_t size {strlen(*data) + 1};
  for (size_t i {0}; i < size; ++i) {
    rpcWrite(io, (*data)[i]);
  }
}

/*! \ingroup write
 * \copydoc rpcWrite(Stream&, T) */
inline void rpcWrite(Stream& io, char** data) {
  char const* data_ {*data};
  rpcWrite(io, (&data_));
}

/*! \ingroup write
 * \copydoc rpcWrite(Stream&, T) */
inline void rpcWrite(Stream& io, String* data) {
  char const* data_ {(*data).c_str()};
  rpcWrite(io, &data_);
}


/*! \ingroup write
 * \copydoc rpcWrite(Stream&, T) */
template <class T>
void rpcWrite(Stream& io, Vector<T>* data) {
  rpcWrite(io, (*data).size());
  for (T& el: *data) {
    rpcWrite(io, &el);
  }
}

/*! \ingroup write
 * \copydoc rpcWrite(Stream&, T) */
template <class T, size_t n>
void rpcWrite(Stream& io, Array<T, n>* data) {
  for (T& el: *data) {
    rpcWrite(io, &el);
  }
}


//! Recursion terminator for `rpcWrite(Tuple*)()`.
inline void rpcWrite(Stream&, Tuple<>*) {}

/*! \ingroup write
 * \copydoc rpcWrite(Stream&, T) */
template <class... Ts>
void rpcWrite(Stream& io, Tuple<Ts...>* data) {
  rpcWrite(io, &(*data).head);
  rpcWrite(io, &(*data).tail);
}
