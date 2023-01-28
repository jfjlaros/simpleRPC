#pragma once

#include "defs.h"
#include "tuple.tcc"
#include "vector.tcc"

//! \defgroup read


/*! \ingroup read
 * Read a value from an stream.
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
template <class T>
inline void rpcRead(Stream& io, T const* data) {  // TODO write analogue?
  rpcRead(io, const_cast<T*>(data));
}


/*! \ingroup read
 * \copydoc rpcRead(Stream&, T*) */
inline void rpcRead(Stream& io, char** data) {
  *data = new char[1];
  rpcRead(io, *data);

  for (size_t size {1}; (*data)[size - 1]; size++) {
    char* data_ {new char[size + 1]};
    memcpy(data_, *data, size);
    delete[] *data;
    *data = data_;

    rpcRead(io, *data + size);
  }
}

/*! \ingroup read
 * \copydoc rpcRead(Stream&, T*) */
inline void rpcRead(Stream& io, char const** data) {
  rpcRead(io, const_cast<char**>(data));
}

/*! \ingroup read
 * \copydoc rpcRead(Stream&, T*) */
inline void rpcRead(Stream& io, String* data) {
  char character;

  rpcRead(io, &character);

  while (character) {
    *data += character;
    rpcRead(io, &character);
  }
}


/*! \ingroup read
 * \copydoc rpcRead(Stream&, T*) */
template <class T>
void rpcRead(Stream& io, Vector<T>* data) {
  size_t size;

  rpcRead(io, &size);
  (*data).resize(size);

  for (size_t i {0}; i < (*data).size(); i++) {
    rpcRead(io, &(*data)[i]);
  }
}

/*! \ingroup read
 * \copydoc rpcRead(Stream&, T*) */
template <class T>
void rpcRead(Stream& io, T** data) {
  size_t size;

  rpcRead(io, &size);
  *data = new T[size];

  for (size_t i {0}; i < size; i++) {
    rpcRead(io, *data + i);
  }
}

/*! \ingroup read
 * \copydoc rpcRead(Stream&, T*) */
template <class T>
void rpcRead(Stream& io, T const** data) {
  rpcRead(io, const_cast<T**>(data));
}

/*! \ingroup read
 * \copydoc rpcRead(Stream&, T*) */
template <class T>
void rpcRead(Stream& io, T*** data) {
  size_t size;

  rpcRead(io, &size);
  *data = new T*[size + 1];

  for (size_t i {0}; i < size; i++) {
    rpcRead(io, *data + i);
  }
  (*data)[size] = nullptr;
}


//! Recursion terminator for `rpcRead(Tuple*)`.
inline void rpcRead(Stream&, Tuple<>*) {}

/*! \ingroup read
 * \copydoc rpcRead(Stream&, T*) */
template <class... Membs>
void rpcRead(Stream& io, Tuple<Membs...>* data) {
  rpcRead(io, &(*data).head);
  rpcRead(io, &(*data).tail);
}


/*! \ingroup read
 * \copydoc rpcRead(Stream&, T*) */
template <class... Membs>
void rpcRead(Stream& io, Object<Membs...>* data) {
  rpcRead(io, dynamic_cast<Tuple<Membs...>*>(data));
}
