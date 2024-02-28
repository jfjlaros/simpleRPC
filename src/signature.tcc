#pragma once

#include "types.tcc"
#include "helper.tcc"

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
  rpcPrint(io, ' ');
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
  rpcPrint(io, ':');

  void (*f_)(Ts...) {};
  parameterTypes_(io, f_);
}

// specialization for reference return types
template <class T, class... Ts>
void signature(Stream& io, T& (*)(Ts...)) {
  /* 
   * A dummy function pointer is prepared, referred to as `f_` in the template
   * functions above, which will be used to isolate parameter types. The return
   * type of this function pointer is removed to avoid unneeded template
   * expansion.
   */
  T data {};
  rpcTypeOf(io, data);
  rpcPrint(io, ":");
  void (*f_)(Ts...) {};
  parameterTypes_(io, f_);
}

template <class F, size_t S, class... Ts>
void signature(Stream& io, const RollingBuffer<F, S>& (*f)(Ts...))
{
  static_assert(always_false<F>::value, "Don't use const qualifier for RollingBuffer<F,S> as return type. use RollingBuffer<F,S>& fun(...)");
}

template <class F, size_t S, class... Ts>
void signature(Stream& io, RollingBuffer<F, S>* (*f)(Ts...))
{
  static_assert(always_false<F>::value, "Return RollingBuffer<F,S> only as a reference type: RollingBuffer<F,S>& fun(...)");
}

template <class F, size_t S, class... Ts>
void signature(Stream& io, const RollingBuffer<F, S>* (*f)(Ts...))
{
  static_assert(always_false<F>::value, "Return RollingBuffer<F,S> only as a reference type: RollingBuffer<F,S>& fun(...)");
}

template <class F, size_t S, class... Ts>
void signature(Stream& io, RollingBuffer<F, S> (*f)(Ts...))
{
  static_assert(always_false<F>::value, "Return RollingBuffer<F,S> only as a reference type: RollingBuffer<F,S>& fun(...)");
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
  rpcPrint(io, ':');
  parameterTypes_(io, f);
}

/*! \ingroup signature
 * \copydoc signature(Stream&, T (*)(Ts...)) */
template <class C, class... Ts>
void signature(Stream& io, void (C::*)(Ts...)) {
  void (*f_)(Ts...) {};
  signature(io, f_);
}
