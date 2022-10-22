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
template <class H, class... Tail>
void parameterTypes_(Stream& io, void (*)(H, Tail...)) {
  /*
   * The first parameter type `H` is isolated from function pointer. This type
   * is used to instantiate the variable `data`, which is passed to
   * `rpcTypeOf()` to encode its type. The first parameter type `H` is removed
   * from the function pointer in the recursive call.
   */
  H data{};
  rpcPrint(io, ' ');
  rpcTypeOf(io, data);

  void (*f_)(Tail...){};
  parameterTypes_(io, f_);
}

//! \copydoc parameterTypes_(Stream&, void (*)(H, Tail...))
template <class H, class... Tail>
void parameterTypes_(Stream& io, void (*)(H&, Tail...)) {
  void (*f_)(H, Tail...){};
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
template <class R, class... FArgs>
void signature(Stream& io, R (*)(FArgs...)) {
  /*
   * A dummy function pointer is prepared, which will be used to isolate
   * parameter types. The return type of this function pointer is removed to
   * avoid unneeded template expansion.
   */
  R data{};
  rpcTypeOf(io, data);
  rpcPrint(io, ':');

  void (*f_)(FArgs...){};
  parameterTypes_(io, f_);
}

/*! \ingroup signature
 * \copydoc signature(Stream&, R (*)(FArgs...)) */
template <class R, class C, class... FArgs>
void signature(Stream& io, R (C::*)(FArgs...)) {
  R (*f_)(FArgs...){};
  signature(io, f_);
}

/*! \ingroup signature
 * \copydoc signature(Stream&, R (*)(FArgs...)) */
template <class... FArgs>
void signature(Stream& io, void (*f)(FArgs...)) {
  rpcPrint(io, ':');
  parameterTypes_(io, f);
}

/*! \ingroup signature
 * \copydoc signature(Stream&, R (*)(FArgs...)) */
template <class C, class... FArgs>
void signature(Stream& io, void (C::*)(FArgs...)) {
  void (*f_)(FArgs...){};
  signature(io, f_);
}
