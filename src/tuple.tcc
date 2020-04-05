#ifndef SIMPLE_RPC_TUPLE_TCC_
#define SIMPLE_RPC_TUPLE_TCC_

#include "helper.tcc"

//! \defgroup tuple
//! \defgroup object
//! \defgroup tuplehelper


/*! \ingroup tuple
 * Empty Tuple.
 */
template <class... Membs>
struct Tuple {};

/*! \ingroup tuple
 * Non-empty Tuple.
 */
template <class H, class... Tail>
struct Tuple<H, Tail...> {
  H head;              //!< First element.
  Tuple<Tail...> tail; //!< Remaining elements.
};

/*! \ingroup object
 * Object.
 */
template <class... Membs>
struct Object : Tuple<Membs...> {
  /*
   * Preferably this would have been an alias, but this is not supported in the
   * current version of Arduino C++.
   */
  Object(void) {}
  Object(Membs... args) : Tuple<Membs...>({args...}) {}
};


/*!
 * Access the type of the *k*-th element in a Tuple.
 *
 * https://eli.thegreenplace.net/2014/variadic-templates-in-c/#id5
 */
template <size_t, class>
struct _ElemTypeHolder;

//! \copydoc _ElemTypeHolder
template <class H, class... Tail>
struct _ElemTypeHolder<0, Tuple<H, Tail...> > {
  typedef H type;
};

//! \copydoc _ElemTypeHolder
template <size_t k, class H, class... Tail>
struct _ElemTypeHolder<k, Tuple<H, Tail...> > {
  typedef typename _ElemTypeHolder<k - 1, Tuple<Tail...> >::type type;
};


/*! \ingroup tuplehelper
 * Get the *k*-th element of a Tuple or Object.
 *
 * This can be used for both retrieval as well as assignment.
 *
 * \param t A Tuple.
 *
 * \return Reference to the *k*-th element in `t`.
 */
template <size_t k, class... Membs>
//! \cond
typename enableIf<
    k == 0, typename _ElemTypeHolder<0, Tuple<Membs...> >::type&>::type
//! \endcond
    get(Tuple<Membs...>& t) {
  return t.head;
}

template <size_t k, class... Membs>
//! \cond
typename enableIf<
    k != 0, typename _ElemTypeHolder<k, Tuple<Membs...> >::type&>::type
//! \endcond
    get(Tuple<Membs...>& t) {
  return get<k - 1>(t.tail);
}


/*! \ingroup tuplehelper
 * Make a Tuple from a parameter pack.
 *
 * \param args Values to store in a Tuple.
 *
 * \return Tuple containing `args`.
 */
template <class... Args>
Tuple<Args...> pack(Args... args) {
  Tuple<Args...> t = {args...};

  return t;
}

/*! \ingroup tuplehelper
 * Cast a `struct` to a Tuple.
 *
 * \param s Struct.
 *
 * \return Tuple representation of `s`.
 */
template <class... Membs, class T>
Tuple<Membs...> castStruct(T& s) {
  Tuple<Membs...>* t = (Tuple<Membs...>*)&s;

  return *t;
}

#endif
