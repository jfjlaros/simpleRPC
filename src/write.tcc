#ifndef SIMPLE_RPC_WRITE_TCC_
#define SIMPLE_RPC_WRITE_TCC_

#include "print.tcc"
#include "tuple.tcc"
#include "vector.tcc"

//! \defgroup write


/*! \ingroup write
 * Write a value to an Input / output object.
 *
 * \param io Input / output object.
 * \param data Data.
 */
template <class I, class T>
void rpcWrite(I& io, T* data) {
  io.write((uint8_t*)data, sizeof(T));
}


/*! \ingroup write
 * \copydoc rpcWrite(I&, T*) */
template <class I>
void rpcWrite(I& io, char** data) {
  rpcPrint(io, *data, '\0');
}

/*! \ingroup write
 * \copydoc rpcWrite(I&, T*) */
template <class I>
void rpcWrite(I& io, char const** data) {
  rpcWrite(io, (char**)data);
}

/*! \ingroup write
 * \copydoc rpcWrite(I&, T*) */
template <class I>
void rpcWrite(I& io, String* data) {
  rpcPrint(io, *data, '\0');
}


/*! \ingroup write
 * \copydoc rpcWrite(I&, T*) */
template <class I, class T>
void rpcWrite(I& io, Vector<T>* data) {
  rpcWrite(io, &(*data).size);

  for (size_t i = 0; i < (*data).size; i++) {
    rpcWrite(io, &(*data)[i]);
  }
}


//! Recursion terminator for `rpcWrite(Tuple*)()`.
template <class I>
void rpcWrite(I&, Tuple<>*) {}

/*! \ingroup write
 * \copydoc rpcWrite(I&, T*) */
template <class I, class... Membs>
void rpcWrite(I& io, Tuple<Membs...>* data) {
  rpcWrite(io, &(*data).head);
  rpcWrite(io, &(*data).tail);
}


/*! \ingroup write
 * \copydoc rpcWrite(I&, T*) */
template <class I, class... Membs>
void rpcWrite(I& io, Object<Membs...>* data) {
  rpcWrite(io, (Tuple<Membs...>*)data);
}

#endif
