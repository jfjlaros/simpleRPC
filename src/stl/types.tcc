#ifndef SIMPLE_RPC_STL_TYPES_TCC_
#define SIMPLE_RPC_STL_TYPES_TCC_

//! \defgroup STLTypes


/*! \ingroup STLTypes
 * \copydoc rpcTypeOf(Stream&, bool) */
inline void rpcTypeOf(Stream& io, std::string& t) {
  rpcPrint(io, (String&)t);
}


/*! \ingroup STLTypes
 * \copydoc rpcTypeOf(Stream&, Tuple<Membs...>&) */
template <class... Membs>
void rpcTypeOf(Stream& io, std::tuple<Membs...>& t) {
  rpcTypeOf(io, (Tuple<Membs...>&)t);
}


/*! \ingroup STLTypes
 * \copydoc rpcTypeOf(Stream&, bool) */
template <class T>
void rpcTypeOf(Stream& io, std::vector<T>& t) {
  rpcTypeOf(io, (Vector<T>&)t);
}

/*! \ingroup STLTypes
 * \copydoc rpcTypeOf(Stream&, bool) */
template <class T, std::size_t N>
void rpcTypeOf(Stream& io, std::array<T, N>& t) {
  rpcTypeOf(io, (Vector<T>&)t);
}

#endif
