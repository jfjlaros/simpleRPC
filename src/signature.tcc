#pragma once

#include "types.tcc"

//! \defgroup signature


//! Recursion terminator for `parameterTypes_()`.
inline void parameterTypes_(Stream&, void (*)()) {}

/*!
 * Get the types of all function parameters.
 *
 * \param io Stream.
 * \param - Dummy function pointer.
 *
 * \return Space separated parameter types.
 */
template <class T, class... Ts>
void parameterTypes_(Stream& io, void (*)(T, Ts...)) {
  /*
   * The first parameter type `T` is isolated from function pointer. This type
   * is used to instantiate the variable `data`, which is passed to
   * `rpcTypeOf()` to encode its type. The first parameter type `T` is removed
   * from the function pointer in the recursive call.
   */
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
 * \param io Stream.
 * \param - Function pointer.
 *
 * \return Function signature.
 */
template <class T, class... Ts>
void signature(Stream& io, T (*)(Ts...)) {
  /*
   * A dummy function pointer is prepared, which will be used to isolate
   * parameter types. The return type of this function pointer is removed to
   * avoid unneeded template expansion.
   */
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
