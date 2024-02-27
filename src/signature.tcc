#pragma once

#include "types.tcc"
#include "helper.tcc"


//! \defgroup signature


//! Recursion terminator for `_parameterTypes()`.
inline void _parameterTypes(Stream&, void (*)(void)) {}

/*!
 * Get the types of all function parameters.
 *
 * \param io Input / output object.
 * \param f_ Dummy function pointer.
 *
 * \return Space separated parameter types.
 */
template <class H, class... Tail>
void _parameterTypes(Stream& io, void (*f_)(H, Tail...)) {
  /*
   * The first parameter type `H` is isolated from function pointer `*f_`. This
   * type is used to instantiate the variable `data`, which is passed to
   * `rpcTypeOf()` to encode its type. The first parameter type `H` is removed
   * from function pointer `*f_` in the recursive call.
   */
  // H data{};

  RPCType<H>().print(io);
  rpcPrint(io, " ");
  // rpcTypeOf(io, data);
  _parameterTypes(io, (void (*)(Tail...))f_);
}

//! \copydoc _parameterTypes(Stream&, void (*)(H, Tail...))
template <class H, class... Tail>
void _parameterTypes(Stream& io, void (*f_)(H&, Tail...)) {
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
template <class R, class... FArgs>
void signature(Stream& io, R (*f)(FArgs...)) {
  /* 
   * A dummy function pointer is prepared, referred to as `f_` in the template
   * functions above, which will be used to isolate parameter types. The return
   * type of this function pointer is removed to avoid unneeded template
   * expansion.
   */
  RPCType<R>::print(io);
  rpcPrint(io, ":");
  _parameterTypes(io, (void (*)(FArgs...))f);
}

// specialization for reference return types
template <class R, class... FArgs>
void signature(Stream& io, R& (*f)(FArgs...)) {
  /* 
   * A dummy function pointer is prepared, referred to as `f_` in the template
   * functions above, which will be used to isolate parameter types. The return
   * type of this function pointer is removed to avoid unneeded template
   * expansion.
   */
  RPCType<R>::print(io);
  rpcPrint(io, ":");
  _parameterTypes(io, (void (*)(FArgs...))f);
}

template <class R, size_t S, class... FArgs>
void signature(Stream& io, const RollingBuffer<R, S>& (*f)(FArgs...))
{
  static_assert(always_false<R>::value, "Don't use const qualifier for RollingBuffer<T,S> as return type. use RollingBuffer<T,S>& fun(...)");
}

template <class R, size_t S, class... FArgs>
void signature(Stream& io, RollingBuffer<R, S>* (*f)(FArgs...))
{
  static_assert(always_false<R>::value, "Return RollingBuffer<T,S> only as a reference type: RollingBuffer<T,S>& fun(...)");
}

template <class R, size_t S, class... FArgs>
void signature(Stream& io, const RollingBuffer<R, S>* (*f)(FArgs...))
{
  static_assert(always_false<R>::value, "Return RollingBuffer<T,S> only as a reference type: RollingBuffer<T,S>& fun(...)");
}

template <class R, size_t S, class... FArgs>
void signature(Stream& io, RollingBuffer<R, S> (*f)(FArgs...))
{
  static_assert(always_false<R>::value, "Return RollingBuffer<T,S> only as a reference type: RollingBuffer<T,S>& fun(...)");
}

/*! \ingroup signature
 * \copydoc signature(Stream&, R (*)(FArgs...)) */
template <class R, class C, class... FArgs>
void signature(Stream& io, R (C::*)(FArgs...)) {
  R (*f)(FArgs...) {};
  signature(io, f);
}

/*! \ingroup signature
 * \copydoc signature(Stream&, R (*)(FArgs...)) */
template <class... FArgs>
void signature(Stream& io, void (*f)(FArgs...)) {
  rpcPrint(io, ":");
  _parameterTypes(io, f);
}

/*! \ingroup signature
 * \copydoc signature(Stream&, R (*)(FArgs...)) */
template <class C, class... FArgs>
void signature(Stream& io, void (C::*)(FArgs...)) {
  void (*f)(FArgs...) {};
  signature(io, f);
}
