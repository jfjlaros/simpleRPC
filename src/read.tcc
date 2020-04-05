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
template <class I, class T>
void rpcRead(I& io, T* data) {
  io.read((byte*)data, sizeof(T));
}


/*! \ingroup read
 * \copydoc rpcRead(I&, T*) */
template <class I>
void rpcRead(I& io, char** data) {
  size_t size = 1;

  *data = (char*)malloc(sizeof(char));
  io.read((byte*)(*data), sizeof(char));

  while ((*data)[size - 1] != _END_OF_STRING) {
    size++;
    *data = (char*)realloc((void*)(*data), size * sizeof(char));
    io.read(((byte*)&(*data)[size - 1]), sizeof(char));
  }
}

/*! \ingroup read
 * \copydoc rpcRead(I&, T*) */
template <class I>
void rpcRead(I& io, const char** data) {
  rpcRead(io, (char**)data);
}

/*! \ingroup read
 * \copydoc rpcRead(I&, T*) */
template <class I>
void rpcRead(I& io, String* data) {
  char character;

  io.read(((byte*)&character), sizeof(char));

  while (character != _END_OF_STRING) {
    *data += character;
    io.read(((byte*)&character), sizeof(char));
  }
}


/*! \ingroup read
 * \copydoc rpcRead(I&, T*) */
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


//! Recursion terminator for `rpcRead(Tuple*)`.
template <class I>
void rpcRead(I&, Tuple<>*) {}

/*! \ingroup read
 * \copydoc rpcRead(I&, T*) */
template <class I, class... Membs>
void rpcRead(I& io, Tuple<Membs...>* data) {
  rpcRead(io, &(*data).head);
  rpcRead(io, &(*data).tail);
}


/*! \ingroup read
 * \copydoc rpcRead(I&, T*) */
template <class I, class... Membs>
void rpcRead(I& io, Object<Membs...>* data) {
  rpcRead(io, (Tuple<Membs...>*)data);
}

#endif
