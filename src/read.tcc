#pragma once

#include "defs.h"
#include "tuple.tcc"
#include "vector.tcc"
#include "array.tcc"
#include "TString.tcc"
#include "PString.h"
#include "types.tcc"
#include "atomic_types.tcc"

//! \defgroup read

/*! \ingroup read
 * Read a value from an Input / output object.
 *
 * \param io Input / output object.
 * \param data Data.
 */
template <class T>
void rpcRead(Stream& io, T* data)
{
  io.readBytes((char*)data, sizeof(T));
}

/*! \ingroup read
 * \copydoc rpcRead(Stream&, T*) */
inline void rpcRead(Stream& io, String* data)
{
  char character;
  rpcRead(io, &character);

  while (character)
  {
    *data += character;
    rpcRead(io, &character);
  }
}

/*! \ingroup read
 * \copydoc rpcRead(Stream&, T*) */
template<size_t S>
inline void rpcRead(Stream& io, TString<S>* data)
{
  char character;
  rpcRead(io, &character);

  while (character)
  {
    *data += character;
    rpcRead(io, &character);
  }
}

/*! \ingroup read
 * \copydoc rpcRead(Stream&, T*) */
inline void rpcRead(Stream& io, PString* data)
{
  char character;
  rpcRead(io, &character);

  while (character)
  {
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

  for (size_t i {0}; i < size; ++i) {
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

  for (size_t i {0}; i < size; ++i) {
    rpcRead(io, *data + i);
  }
}

/*! \ingroup read
 * \copydoc rpcRead(Stream&, T*) */
template <class T, size_t n>
void rpcRead(Stream& io, Array<T, n>* data) {
  size_t size;
  rpcRead(io, &size);

  for (size_t i {0}; i < min(size, n); ++i) {
    rpcRead(io, &(*data)[i]);
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

  for (size_t i {0}; i < size; ++i) {
    rpcRead(io, *data + i);
  }
  (*data)[size] = nullptr;
}

//! Recursion terminator for `rpcRead(_Tuple*)`.
inline void rpcRead(Stream&, _Tuple<>*) {}

/*! \ingroup read
 * \copydoc rpcRead(Stream&, T*) */
template <class... Membs>
void rpcRead(Stream& io, _Tuple<Membs...>* data)
{
  rpcRead(io, &(*data).head);
  rpcRead(io, &(*data).tail);
}


/*! \ingroup read
 * \copydoc rpcRead(Stream&, T*) */
template <class... Membs>
void rpcRead(Stream& io, Tuple<Membs...>* data)
{
  rpcRead(io, (_Tuple<Membs...>*)data);
}