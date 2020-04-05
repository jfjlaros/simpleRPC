#ifndef SIMPLE_RPC_SIGNATURE_TCC_
#define SIMPLE_RPC_SIGNATURE_TCC_

#include "types.tcc"

//! \defgroup signature


//! Recursion terminator for `_parameterTypes()`.
inline String _parameterTypes(void (*)(void)) {
  return "";
}

/*!
 * Get the types of all function parameters.
 *
 * \param f_ Dummy function pointer.
 *
 * \return Space separated parameter types.
 */
template <class H, class... Tail>
String _parameterTypes(void (*f_)(H, Tail...)) {
  /*
   * The first parameter type `H` is isolated from function pointer `*f_`. This
   * type is used to instantiate the variable `data`, which is passed to
   * `rpcTypeOf()` to encode its type. The first parameter type `H` is removed
   * from function pointer `*f_` in the recursive call.
   */
  H data;

  return " " + rpcTypeOf(data) + _parameterTypes((void (*)(Tail...))f_);
}

//! \copydoc _parameterTypes(void (*)(H, Tail...))
template <class H, class... Tail>
String _parameterTypes(void (*f_)(H&, Tail...)) {
  return _parameterTypes((void (*)(H, Tail...))f_);
}


/*! \ingroup signature
 * Get the signature of a function.
 *
 * \param f Function pointer.
 *
 * \return Function signature.
 */
template <class R, class... FArgs>
String signature(R (*f)(FArgs...)) {
  /* 
   * A dummy function pointer is prepared, referred to as `f_` in the template
   * functions above, which will be used to isolate parameter types. The return
   * type of this function pointer is removed to avoid unneeded template
   * expansion.
   */
  R data;

  return rpcTypeOf(data) + ":" + _parameterTypes((void (*)(FArgs...))f);
}

/*! \ingroup signature
 * \copydoc signature(R (*)(FArgs...)) */
template <class R, class C, class... FArgs>
String signature(R (C::*f)(FArgs...)) {
  return signature((R (*)(FArgs...))f);
}

/*! \ingroup signature
 * \copydoc signature(R (*)(FArgs...)) */
template <class... FArgs>
String signature(void (*f)(FArgs...)) {
  return ":" + _parameterTypes(f);
}

/*! \ingroup signature
 * \copydoc signature(R (*)(FArgs...)) */
template <class C, class... FArgs>
String signature(void (C::*f)(FArgs...)) {
  return signature((void (*)(FArgs...))f);
}

#endif
