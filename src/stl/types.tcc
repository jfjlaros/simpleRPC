#ifndef SIMPLE_RPC_STL_TYPES_TCC_
#define SIMPLE_RPC_STL_TYPES_TCC_

/*
  TODO

  C++ type            | Python type       | struct | implemented
  --------------------+-------------------+--------+------------
  string              | str               | s      | yes
  array               | list              | []     | yes
  vector              | list              | []     | yes
  deque               | list              | []     | no
  forward_list        | list              | []     | no
  list                | list              | []     | yes
  tuple               | tuple             | ()     | yes
  --------------------+-------------------+--------+------------
  set                 | set               | ‹›     | no
  multiset            | Counter           | «»     | no
  map                 | dict              | <>     | no
  multimap            | defaultdict(list) | ≤≥     | no
  --------------------+-------------------+--------+------------
  unordered_set       | set               | ‹›     | no
  unordered_multiset  | Counter           | «»     | no
  unordered_map       | dict              | <>     | no
  unordered_multimap  | defaultdict(list) | ≤≥     | no
*/

//! \defgroup STLTypes


/*! \ingroup STLTypes
 * \copydoc rpcTypeOf(Stream&, bool) */
inline void rpcTypeOf(Stream& io, std::string& t) {
  rpcTypeOf(io, (String&)t);
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

/*! \ingroup STLTypes
 * \copydoc rpcTypeOf(Stream&, bool) */
template <class T>
void rpcTypeOf(Stream& io, std::list<T>& t) {
  rpcTypeOf(io, (Vector<T>&)t);
}

/*! \ingroup STLTypes
 * \copydoc rpcTypeOf(Stream&, bool) */
template <class T>
void rpcTypeOf(Stream& io, std::forward_list<T>& t) {
  rpcTypeOf(io, (Vector<T>&)t);
}

#endif
