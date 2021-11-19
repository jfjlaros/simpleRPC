#ifndef SIMPLE_RPC_STL_READ_TCC_
#define SIMPLE_RPC_STL_READ_TCC_

//! \defgroup STLRead


/*! \ingroup STLRead
 * \copydoc rpcRead(Stream&, T*) */
inline void rpcRead(Stream& io, std::string* data) {
  char character;

  rpcRead(io, &character);

  while (character) {
    *data += character;
    rpcRead(io, &character);
  }
}


//! Recursion terminator for `rpcRead(std::tuple*)`.
template<std::size_t i = 0, class... Membs>
typename std::enable_if<i == sizeof...(Membs), void>::type
    rpcRead(Stream&, std::tuple<Membs...>*) {}

/*! \ingroup STLread
 * \copydoc rpcRead(Stream&, T*) */
template<std::size_t i = 0, class... Membs>
typename std::enable_if<i < sizeof...(Membs), void>::type
    rpcRead(Stream& io, std::tuple<Membs...>* data) {
  rpcRead(io, &std::get<i>(*data));
  rpcRead<i + 1, Membs...>(io, data);
}


/*! \ingroup STLRead
 * \copydoc rpcRead(Stream&, T*) */
template <class T>
void rpcRead(Stream& io, std::vector<T>* data) {
  size_t size;

  rpcRead(io, &size);
  (*data).resize(size);

  for (size_t i = 0; i < (*data).size(); i++) {
    rpcRead(io, &(*data)[i]);
  }
}

/*! \ingroup STLRead
 * \copydoc rpcRead(Stream&, T*) */
template <class T, std::size_t N>
void rpcRead(Stream& io, std::array<T, N>* data) {
  rpcRead(io, (Vector<T>*)data);
}

#endif
