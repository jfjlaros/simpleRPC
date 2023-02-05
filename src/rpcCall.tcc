#pragma once

#include "del.tcc"
#include "read.tcc"
#include "write.tcc"

//! \defgroup call


/*!
 * Execute a plain function.
 *
 * \param io Stream.
 * \param - Dummy function pointer.
 * \param f Function pointer.
 * \param args Parameter pack for `f`.
 */
template <class T, class... Ts, class... Us>
void call_(Stream& io, void (*)(), T (*f)(Ts...), Us&... args) {
  /*
   * All parameters have been collected since function pointer `*f_` has no
   * parameter types. All values are now present in the `args` parameter pack.
   */
  T data {f(args...)};
  rpcWrite(io, &data);
}

/*!
 * Execute a class method.
 *
 * \param io Stream.
 * \param - Dummy function pointer.
 * \param t Tuple consisting of a pointer to a class instance and a pointer
 *   to a class method.
 * \param args Parameter pack for `f`.
 */
template <class C, class P, class T, class... Ts, class... Us>
void call_(
    Stream& io, void (*)(), Tuple<C*, T (P::*)(Ts...)> t, Us&... args) {
  T data {(*t.head.*t.tail.head)(args...)};
  rpcWrite(io, &data);
}

//! \copydoc call_(Stream&, void (*)(), T (*)(Ts...), Us&...)
template <class... Ts, class... Us>
void call_(Stream&, void (*)(), void (*f)(Ts...), Us&... args) {
  f(args...);
}

//! \copydoc call_(Stream&, void (*)(), T (*)(Ts...), Us&...)
template <class C, class P, class... Ts, class... Us>
void call_(
    Stream&, void (*)(), Tuple<C*, void (P::*)(Ts...)> t, Us&... args) {
  (*t.head.*t.tail.head)(args...);
}


/*!
 * Collect parameters of a function.
 *
 * \param io Stream.
 * \param - Dummy function pointer.
 * \param f Function pointer.
 * \param args Parameter pack for `f`.
 */
template <class T, class... Ts, class F, class... Us>
void call_(Stream& io, void (*)(T, Ts...), F f, Us&... args) {
  /* 
   * The first parameter type `T` is isolated from the function pointer. This
   * type is used to instantiate the variable `data`, which is used to receive
   * `sizeof(T)` bytes. This value is passed recursively to `call_()` function,
   * adding it to the `args` parameter pack. The first parameter type `T` is
   * removed from the function pointer in the recursive call.
   */ 
  T data;
  rpcRead(io, &data);

  void (*f_)(Ts...) {};
  call_(io, f_, f, args..., data);
  rpcDel(&data);
}

//! \copydoc call_(Stream&, void (*)(T, Ts...), F, Us&...)
template <class T, class... Ts, class F, class... Us>
void call_(Stream& io, void (*)(T&, Ts...), F f, Us&... args) {
  void (*f_)(T, Ts...) {};
  call_(io, f_, f, args...);
}


/*! \ingroup call
 * Call a function.
 *
 * Parameter values for `f` are read from `io`, after which `f` is called. Any
 * return value is written back to `io`.
 *
 * \param io Stream.
 * \param f Function pointer.
 */
template <class T, class... Ts>
void rpcCall(Stream& io, T (*f)(Ts...)) {
  /*
   * A dummy function pointer is prepared, which will be used to isolate
   * parameter types. The return type of this function pointer is removed to
   * avoid unneeded template expansion.
   */
  void (*f_)(Ts...) {};
  call_(io, f_, f);
}

/*! \ingroup call
 * Call a class method.
 *
 * \sa rpcCall(Stream&, T (*)(Ts...))
 *
 * \param io Stream.
 * \param t Tuple consisting of a pointer to a class instance and a pointer
 *   to a class method.
 */
template <class C, class P, class T, class... Ts>
void rpcCall(Stream& io, Tuple<C*, T (P::*)(Ts...)> t) {
  void (*f_)(Ts...) {};
  call_(io, f_, t);
}
