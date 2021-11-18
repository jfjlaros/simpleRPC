#ifndef SIMPLE_RPC_STL_READ_TCC_
#define SIMPLE_RPC_STL_READ_TCC_

//! \defgroup STLRead


/*! \ingroup STLRead
 * \copydoc rpcRead(Stream&, T*) */
inline void rpcRead(Stream& io, std::string* data) {
  rpcRead(io, (String*)data);
}


/*! \ingroup STLRead
 * \copydoc rpcRead(Stream&, T*) */
template <class... Membs>
void rpcRead(Stream& io, std::tuple<Membs...>* data) {
  rpcRead(io, (Tuple<Membs...>*)data);
}


/*! \ingroup STLRead
 * \copydoc rpcRead(Stream&, T*) */
template <class T>
void rpcRead(Stream& io, std::vector<T>* data) {
  rpcRead(io, (Vector<T>*)data);
}

/*! \ingroup STLRead
 * \copydoc rpcRead(Stream&, T*) */
template <class T, std::size_t N>
void rpcRead(Stream& io, std::array<T, N>* data) {
  rpcRead(io, (Vector<T>*)data);
}

#endif
