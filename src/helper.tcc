#ifndef SIMPLE_RPC_HELPER_TCC_
#define SIMPLE_RPC_HELPER_TCC_

/*!
 * Compile-time switch for templates.
 *
 * https://www.boost.org/doc/libs/1_55_0/libs/utility/enable_if.html
 */
template <bool, class T=void>
struct enableIf {};

template <class T>
struct enableIf<true, T> {
  typedef T type;
};

#endif
