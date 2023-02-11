#pragma once

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
 * Tuple.
 *
 * \tparam T First element type.
 * \tparam Ts... Remaining elements types.
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
  using type = T;
};

//! \copydoc ElemTypeHolder_
template <size_t k, class T, class... Ts>
struct ElemTypeHolder_<k, Tuple<T, Ts...> > {
  using type = typename ElemTypeHolder_<k - 1, Tuple<Ts...> >::type;
};


/*! \ingroup tuplehelper
 * Get the *k*-th element of a Tuple.
 *
 * This can be used for both retrieval as well as assignment.
 *
 * \tparam k Element index.
 * \tparam Ts... Elements types.
 *
 * \param t A Tuple.
 *
 * \return Reference to the *k*-th element in `t`.
 */
template <size_t k, class... Ts>
//! \cond
typename enableIf<
    not k, typename ElemTypeHolder_<0, Tuple<Ts...> >::type&>::type
//! \endcond
    get(Tuple<Ts...>& t) {
  return t.head;
}

template <size_t k, class... Ts>
//! \cond
typename enableIf<
    k, typename ElemTypeHolder_<k, Tuple<Ts...> >::type&>::type
//! \endcond
    get(Tuple<Ts...>& t) {
  return get<k - 1>(t.tail);
}


/*! \ingroup tuplehelper
 * Make a Tuple from a parameter pack.
 *
 * \tparam Ts... Elements types.
 *
 * \param args Values to store in a Tuple.
 *
 * \return Tuple containing `args`.
 */
template <class... Ts>
Tuple<Ts...> makeTuple(Ts... args) {
  Tuple<Ts...> t {args...};
  return t;
}
