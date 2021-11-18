#ifndef SIMPLE_RPC_STL_WRITE_TCC_
#define SIMPLE_RPC_STL_WRITE_TCC_

//! \defgroup STLWrite


/*! \ingroup STLWrite
 * \copydoc rpcWrite(Stream&, T*) */
inline void rpcWrite(Stream& io, std::string* data) {
  rpcWrite(io, (String*)data);
}


/*! \ingroup STLWrite
 * \copydoc rpcWrite(Stream&, T*) */
template <class... Membs>
void rpcWrite(Stream& io, std::tuple<Membs...>* data) {
  rpcWrite(io, (Tuple<Membs...>*)data);
}


/*! \ingroup STLWrite
 * \copydoc rpcWrite(Stream&, T*) */
template <class T>
void rpcWrite(Stream& io, std::vector<T>* data) {
  rpcWrite(io, (Vector<T>*)data);
}

/*! \ingroup STLWrite
 * \copydoc rpcWrite(Stream&, T*) */
template <class T, std::size_t N>
void rpcWrite(Stream& io, std::array<T, N>* data) {
  rpcWrite(io, (Vector<T>*)data);
}

#endif
