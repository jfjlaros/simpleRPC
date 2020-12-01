#ifndef SIMPLE_RPC_READ_TCC_
#define SIMPLE_RPC_READ_TCC_

#include "defs.h"
#include "tuple.tcc"
#include "vector.tcc"

//! \defgroup read


/*! \ingroup read
 * Read a value from an Input / output object.
 *
 * \param io Input / output object.
 * \param data Data.
 */
template <class T>
void rpcRead(Stream& io, T* data) {
  io.readBytes((char*)data, sizeof(T));
}


/*! \ingroup read
 * \copydoc rpcRead(Stream&, T*) */
inline void rpcRead(Stream& io, char** data) {
  *data = (char*)malloc(sizeof(char));
  rpcRead(io, &(*data)[0]);

  for (size_t size = 1; (*data)[size - 1]; size++) {
    *data = (char*)realloc((void*)(*data), (size + 1) * sizeof(char));
    rpcRead(io, &(*data)[size]);
  }
}

/*! \ingroup read
 * \copydoc rpcRead(Stream&, T*) */
inline void rpcRead(Stream& io, char const** data) {
  rpcRead(io, (char**)data);
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

  for (size_t i = 0; i < (*data).size; i++) {
    rpcRead(io, &(*data)[i]);
  }
}

/*! \ingroup read
 * \copydoc rpcRead(Stream&, T*) */
template <class T>
void rpcRead(Stream& io, T** data) {
  size_t size;

  rpcRead(io, &size);
  *data = (T*)malloc(size * sizeof(T));

  for (size_t i = 0; i < size; i++) {
    rpcRead(io, &(*data)[i]);
  }
}

/*! \ingroup read
 * \copydoc rpcRead(Stream&, T*) */
template <class T>
void rpcRead(Stream& io, T*** data) {
  size_t size;

  rpcRead(io, &size);
  *data = (T**)malloc((size + 1) * sizeof(T*));

  for (size_t i = 0; i < size; i++) {
    rpcRead(io, &(*data)[i]);
  }
  (*data)[size] = NULL;
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
  rpcRead(io, (Tuple<Membs...>*)data);
}

#endif
