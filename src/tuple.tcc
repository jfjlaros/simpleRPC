#pragma once

#include "defs.h"
#include "helper.tcc"

//! \defgroup tuple
//! \defgroup object
//! \defgroup tuplehelper


/*! \ingroup tuple
 * Empty Tuple.
 */
template <class...>
class Tuple {};

/*! \ingroup tuple
 * Non-empty Tuple.
 */
template <class T, class... Ts>
class Tuple<T, Ts...> {
public:
  Tuple() = default;
  Tuple(T h, Ts... t);

  T head {};             //!< First element.
  Tuple<Ts...> tail {};  //!< Remaining elements.
};


template <class T, class... Ts>
Tuple<T, Ts...>::Tuple(T h, Ts... t) : head {h}, tail {t...} {}


/*!
 * Access the type of the *k*-th element in a Tuple.
 *
 * https://eli.thegreenplace.net/2014/variadic-templates-in-c/#id5
 */
template <size_t, class>
struct ElemTypeHolder_;

//! \copydoc ElemTypeHolder_
template <class T, class... Ts>
struct ElemTypeHolder_<0, Tuple<T, Ts...> > {
  typedef T type;
};

//! \copydoc ElemTypeHolder_
template <size_t k, class T, class... Ts>
struct ElemTypeHolder_<k, Tuple<T, Ts...> > {
  typedef typename ElemTypeHolder_<k - 1, Tuple<Ts...> >::type type;
};


/*! \ingroup tuplehelper
 * Get the *k*-th element of a Tuple.
 *
 * This can be used for both retrieval as well as assignment.
 *
 * \param t A Tuple.
 *
 * \return Reference to the *k*-th element in `t`.
 */
template <size_t k, class... Ts>
//! \cond
typename enableIf<
    k == 0, typename ElemTypeHolder_<0, Tuple<Ts...> >::type&>::type
//! \endcond
    get(Tuple<Ts...>& t) {
  return t.head;
}

template <size_t k, class... Ts>
//! \cond
typename enableIf<
    k != 0, typename ElemTypeHolder_<k, Tuple<Ts...> >::type&>::type
//! \endcond
    get(Tuple<Ts...>& t) {
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
Tuple<Args...> makeTuple(Args... args) {
  Tuple<Args...> t {args...};
  return t;
}
