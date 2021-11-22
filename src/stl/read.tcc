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
  size_t size;

  rpcRead(io, &size);

  for (size_t i = 0; i < size; i++) {
    rpcRead(io, &(*data)[i]);
  }
}

/*! \ingroup STLRead
 * \copydoc rpcRead(Stream&, T*) */
template <class T>
void rpcRead(Stream& io, std::list<T>* data) {
  size_t size;

  rpcRead(io, &size);

  for (size_t _ = 0; _ < size; _++) {
    T element;

    rpcRead(io, &element);
    (*data).push_back(element);
  }
}

/*! \ingroup STLRead
 * \copydoc rpcRead(Stream&, T*) */
template <class T>
void rpcRead(Stream& io, std::forward_list<T>* data) {
  size_t size;

  rpcRead(io, &size);

  typename std::forward_list<T>::iterator it = (*data).before_begin();
  for (size_t _ = 0; _ < size; _++) {
    T element;

    rpcRead(io, &element);
    it = (*data).insert_after(it, element);
  }
}


/*! \ingroup STLRead
 * \copydoc rpcRead(Stream&, T*) */
template <class T>
void rpcRead(Stream& io, std::set<T>* data) {
  size_t size;

  rpcRead(io, &size);

  for (size_t _ = 0; _ < size; _++) {
    T element;

    rpcRead(io, &element);
    (*data).insert(element);
  }
}

/*! \ingroup STLRead
 * \copydoc rpcRead(Stream&, T*) */
template <class T>
void rpcRead(Stream& io, std::unordered_set<T>* data) {
  size_t size;

  rpcRead(io, &size);

  for (size_t _ = 0; _ < size; _++) {
    T element;

    rpcRead(io, &element);
    (*data).insert(element);
  }
}

#endif
