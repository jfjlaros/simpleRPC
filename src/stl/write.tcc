#ifndef SIMPLE_RPC_STL_WRITE_TCC_
#define SIMPLE_RPC_STL_WRITE_TCC_

//! \defgroup STLWrite


/*! \ingroup STLWrite
 * \copydoc rpcWrite(Stream&, T*) */
inline void rpcWrite(Stream& io, std::string* data) {
  rpcPrint(io, *data, '\0');
}


//! Recursion terminator for `rpcWrite(std::tuple*)`.
template<std::size_t i = 0, class... Membs>
typename std::enable_if<i == sizeof...(Membs), void>::type
    rpcWrite(Stream&, std::tuple<Membs...>*) {}

/*! \ingroup STLread
 * \copydoc rpcWrite(Stream&, T*) */
template<std::size_t i = 0, class... Membs>
typename std::enable_if<i < sizeof...(Membs), void>::type
    rpcWrite(Stream& io, std::tuple<Membs...>* data) {
  rpcWrite(io, &std::get<i>(*data));
  rpcWrite<i + 1, Membs...>(io, data);
}


/*! \ingroup STLWrite
 * \copydoc rpcWrite(Stream&, T*) */
template <class T>
void rpcWrite(Stream& io, std::vector<T>* data) {
  size_t size = (*data).size();

  rpcWrite(io, &size);

  for (size_t i = 0; i < (*data).size(); i++) {
    rpcWrite(io, &(*data)[i]);
  }
}

/*! \ingroup STLWrite
 * \copydoc rpcWrite(Stream&, T*) */
template <class T, std::size_t N>
void rpcWrite(Stream& io, std::array<T, N>* data) {
  size_t size = (*data).size();

  rpcWrite(io, &size);

  for (size_t i = 0; i < (*data).size(); i++) {
    rpcWrite(io, &(*data)[i]);
  }
}

/*! \ingroup STLWrite
 * \copydoc rpcWrite(Stream&, T*) */
template <class T>
void rpcWrite(Stream& io, std::list<T>* data) {
  size_t size = (*data).size();

  rpcWrite(io, &size);

  typename std::list<T>::iterator it;
  T element;
  for (it = (*data).begin(); it != (*data).end(); it++) {
    element = *it;
    rpcWrite(io, &element);
  }
}

/*! \ingroup STLWrite
 * \copydoc rpcWrite(Stream&, T*) */
template <class T>
void rpcWrite(Stream& io, std::forward_list<T>* data) {
  size_t size = 0;

  typename std::forward_list<T>::iterator it;
  for (it = (*data).begin(); it != (*data).end(); it++) {
    size++;
  }
  rpcWrite(io, &size);

  T element;
  for (it = (*data).begin(); it != (*data).end(); it++) {
    element = *it;
    rpcWrite(io, &element);
  }
}

#endif
