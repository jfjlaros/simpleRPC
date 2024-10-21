#pragma once

#include "types.tcc"

//! \defgroup signature


//! Recursion terminator for `parameterTypes_()`.
inline void parameterTypes_(Stream&, void (*)()) {}

/*! Get the types of all function parameters.
 *
 * \tparam T First function pointer parameter type.
 * \tparam Ts... Remaining function pointer parameters types.
 *
 * \param io Stream.
 * \param - Dummy function pointer.
 *
 * \return Space separated parameter types.
 */
template <class T, class... Ts>
void parameterTypes_(Stream& io, void (*)(T, Ts...)) {
  T data {};
  rpcWrite(io, ' ');
  rpcTypeOf(io, data);

  void (*f_)(Ts...) {};
  parameterTypes_(io, f_);
}

//! \copydoc parameterTypes_(Stream&, void (*)(T, Ts...))
template <class T, class... Ts>
void parameterTypes_(Stream& io, void (*)(T&, Ts...)) {
  void (*f_)(T, Ts...) {};
  parameterTypes_(io, f_);
}


/*! \ingroup signature
 * Get the signature of a function.
 *
 * \tparam T Function pointer return type.
 * \tparam Ts... Function pointer parameter types.
 *
 * \param io Stream.
 * \param - Function pointer.
 *
 * \return Function signature.
 */
template <class T, class... Ts>
void signature(Stream& io, T (*)(Ts...)) {
  T data {};
  rpcTypeOf(io, data);
  rpcWrite(io, ':');

  void (*f_)(Ts...) {};
  parameterTypes_(io, f_);
}

/*! \ingroup signature
 * \copydoc signature(Stream&, T (*)(Ts...)) */
template <class T, class C, class... Ts>
void signature(Stream& io, T (C::*)(Ts...)) {
  T (*f_)(Ts...) {};
  signature(io, f_);
}

/*! \ingroup signature
 * \copydoc signature(Stream&, T (*)(Ts...)) */
template <class... Ts>
void signature(Stream& io, void (*f)(Ts...)) {
  rpcWrite(io, ':');
  parameterTypes_(io, f);
}

/*! \ingroup signature
 * \copydoc signature(Stream&, T (*)(Ts...)) */
template <class C, class... Ts>
void signature(Stream& io, void (C::*)(Ts...)) {
  void (*f_)(Ts...) {};
  signature(io, f_);
}
