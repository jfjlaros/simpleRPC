#pragma once

#include "helper.tcc"

//! \defgroup tuple
//! \defgroup tuplehelper


/*! \ingroup tuple
 * Empty _Tuple.
 */
template <class... Membs>
struct _Tuple {};

/*! \ingroup tuple
 * Non-empty _Tuple.
 */
template <class H, class... Tail>
struct _Tuple<H, Tail...>
{
  H head;              //!< First element.
  _Tuple<Tail...> tail; //!< Remaining elements.
};

/*! \ingroup tuple
 * Tuple.
 */
template <class... Membs>
struct Tuple : _Tuple<Membs...>
{
  /*
   * Preferably this would have been an alias, but this is not supported in the
   * current version of Arduino C++.
   */
  Tuple(void) {

  }
  Tuple(Membs... args) : _Tuple<Membs...>({args...}) {}
};


/*!
 * Access the type of the *k*-th element in a _Tuple.
 *
 * https://eli.thegreenplace.net/2014/variadic-templates-in-c/#id5
 */
template <size_t, class>
struct _ElemTypeHolder;

//! \copydoc _ElemTypeHolder
template <class H, class... Tail>
struct _ElemTypeHolder<0, _Tuple<H, Tail...> > {
  typedef H type;
};

//! \copydoc _ElemTypeHolder
template <size_t k, class H, class... Tail>
struct _ElemTypeHolder<k, _Tuple<H, Tail...> > {
  typedef typename _ElemTypeHolder<k - 1, _Tuple<Tail...> >::type type;
};


/*! \ingroup tuplehelper
 * Get the *k*-th element of a _Tuple or Tuple.
 *
 * This can be used for both retrieval as well as assignment.
 *
 * \param t A _Tuple.
 *
 * \return Reference to the *k*-th element in `t`.
 */
template <size_t k, class... Membs>
//! \cond
typename enableIf<
    k == 0, typename _ElemTypeHolder<0, _Tuple<Membs...> >::type&>::type
//! \endcond
    get(_Tuple<Membs...>& t) {
  return t.head;
}

template <size_t k, class... Membs>
//! \cond
typename enableIf<
    k != 0, typename _ElemTypeHolder<k, _Tuple<Membs...> >::type&>::type
//! \endcond
    get(_Tuple<Membs...>& t) {
  return get<k - 1>(t.tail);
}


/*! \ingroup tuplehelper
 * Make a _Tuple from a parameter pack.
 *
 * \param args Values to store in a _Tuple.
 *
 * \return _Tuple containing `args`.
 */
template <class... Args>
_Tuple<Args...> pack(Args... args) {
  _Tuple<Args...> t = {args...};

  return t;
}

/*! \ingroup tuplehelper
 * Cast a `struct` to a _Tuple.
 *
 * \param s Struct.
 *
 * \return _Tuple representation of `s`.
 */
template <class... Membs, class T>
_Tuple<Membs...> castStruct(T& s)
{
  _Tuple<Membs...>* t = (_Tuple<Membs...>*)&s;

  return *t;
}