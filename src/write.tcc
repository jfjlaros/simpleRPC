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
template <class T>
void rpcWrite(Stream& io, T* data) {
  io.write((uint8_t*)data, sizeof(T));
}


/*! \ingroup write
 * \copydoc rpcWrite(Stream&, T*) */
inline void rpcWrite(Stream& io, char** data) {
  rpcPrint(io, *data, '\0');
}

/*! \ingroup write
 * \copydoc rpcWrite(Stream&, T*) */
inline void rpcWrite(Stream& io, char const** data) {
  rpcWrite(io, (char**)data);
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
  rpcWrite(io, (Tuple<Membs...>*)data);
}

#endif
