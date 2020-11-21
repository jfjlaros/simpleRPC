#ifndef SIMPLE_RPC_SIGNATURE_TCC_
#define SIMPLE_RPC_SIGNATURE_TCC_

#include "types.tcc"

//! \defgroup signature


//! Recursion terminator for `_parameterTypes()`.
template <class I>
void _parameterTypes(I&, void (*)(void)) {}

/*!
 * Get the types of all function parameters.
 *
 * \param io Input / output object.
 * \param f_ Dummy function pointer.
 *
 * \return Space separated parameter types.
 */
template <class I, class H, class... Tail>
void _parameterTypes(I& io, void (*f_)(H, Tail...)) {
  /*
   * The first parameter type `H` is isolated from function pointer `*f_`. This
   * type is used to instantiate the variable `data`, which is passed to
   * `rpcTypeOf()` to encode its type. The first parameter type `H` is removed
   * from function pointer `*f_` in the recursive call.
   */
  H data;

  rpcPrint(io, " ");
  rpcTypeOf(io, data);
  _parameterTypes(io, (void (*)(Tail...))f_);
}

//! \copydoc _parameterTypes(I&, void (*)(H, Tail...))
template <class I, class H, class... Tail>
void _parameterTypes(I& io, void (*f_)(H&, Tail...)) {
  _parameterTypes(io, (void (*)(H, Tail...))f_);
}


/*! \ingroup signature
 * Get the signature of a function.
 *
 * \param io Input / output object.
 * \param f Function pointer.
 *
 * \return Function signature.
 */
template <class I, class R, class... FArgs>
void signature(I& io, R (*f)(FArgs...)) {
  /* 
   * A dummy function pointer is prepared, referred to as `f_` in the template
   * functions above, which will be used to isolate parameter types. The return
   * type of this function pointer is removed to avoid unneeded template
   * expansion.
   */
  R data;

  rpcTypeOf(io, data);
  rpcPrint(io, ":");
  _parameterTypes(io, (void (*)(FArgs...))f);
}

/*! \ingroup signature
 * \copydoc signature(I&, R (*)(FArgs...)) */
template <class I, class R, class C, class... FArgs>
void signature(I& io, R (C::*f)(FArgs...)) {
  signature(io, (R (*)(FArgs...))f);
}

/*! \ingroup signature
 * \copydoc signature(I&, R (*)(FArgs...)) */
template <class I, class... FArgs>
void signature(I& io, void (*f)(FArgs...)) {
  rpcPrint(io, ":");
  _parameterTypes(io, f);
}

/*! \ingroup signature
 * \copydoc signature(I&, R (*)(FArgs...)) */
template <class I, class C, class... FArgs>
void signature(I& io, void (C::*f)(FArgs...)) {
  signature(io, (void (*)(FArgs...))f);
}

#endif
