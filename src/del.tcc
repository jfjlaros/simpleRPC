#ifndef SIMPLE_RPC_DEL_TCC_
#define SIMPLE_RPC_DEL_TCC_

#include "tuple.tcc"

//! \defgroup del


/*! \ingroup del
 * Delete a value.
 *
 * \param data Data.
 */
template <class T>
void rpcDel(T* data) {}


/*! \ingroup del
 * \copydoc rpcDel(T*) */
template <class T>
void rpcDel(T** data) {
  free(*data);
}

/*! \ingroup del
 * \copydoc rpcDel(T*) */
template <class T>
void rpcDel(T const** data) {
  rpcDel((T**)data);
}

/*! \ingroup del
 * \copydoc rpcDel(T*) */
template <class T>
void rpcDel(T*** data) {
  for (size_t i = 0; (*data)[i]; i++) {
    rpcDel(&(*data)[i]);
  }

  free(*data);
}

/*! \ingroup del
 * \copydoc rpcDel(T*) */
template <class T>
void rpcDel(T const*** data) {
  rpcDel((T***)data);
}


//! Recursion terminator for `rpcDel(Tuple*)`.
inline void rpcDel(Tuple<>*) {}

/*! \ingroup del
 * \copydoc rpcDel(T*) */
template <class... Membs>
void rpcDel(Tuple<Membs...>* data) {
  rpcDel(&(*data).head);
  rpcDel(&(*data).tail);
}


/*! \ingroup del
 * \copydoc rpcDel(T*) */
template <class... Membs>
void rpcDel(Object<Membs...>* data) {
  rpcDel((Tuple<Membs...>*)data);
}

#endif
