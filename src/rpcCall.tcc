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
template <class R, class... FArgs, class... Args>
void call_(Stream& io, void (*)(), R (*f)(FArgs...), Args&... args) {
  /*
   * All parameters have been collected since function pointer `*f_` has no
   * parameter types. All values are now present in the `args` parameter pack.
   */
  R data {f(args...)};

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
template <class C, class P, class R, class... FArgs, class... Args>
void call_(
    Stream& io, void (*)(), Tuple<C*, R (P::*)(FArgs...)> t, Args&... args) {
  R data {(*t.head.*t.tail.head)(args...)};

  rpcWrite(io, &data);
}

//! \copydoc call_(Stream&, void (*)(), R (*)(FArgs...), Args&...)
template <class... FArgs, class... Args>
void call_(Stream&, void (*)(), void (*f)(FArgs...), Args&... args) {
  f(args...);
}

//! \copydoc call_(Stream&, void (*)(), R (*)(FArgs...), Args&...)
template <class C, class P, class... FArgs, class... Args>
void call_(
    Stream&, void (*)(), Tuple<C*, void (P::*)(FArgs...)> t, Args&... args) {
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
template <class H, class... Tail, class F, class... Args>
void call_(Stream& io, void (*)(H, Tail...), F f, Args&... args) {
  /* 
   * The first parameter type `H` is isolated from the function pointer. This
   * type is used to instantiate the variable `data`, which is used to receive
   * `sizeof(H)` bytes. This value is passed recursively to `call_()` function,
   * adding it to the `args` parameter pack. The first parameter type `H` is
   * removed from the function pointer in the recursive call.
   */ 
  H data;
  rpcRead(io, &data);

  void (*f_)(Tail...) {};
  call_(io, f_, f, args..., data);
  rpcDel(&data);
}

//! \copydoc call_(Stream&, void (*)(H, Tail...), F, Args&...)
template <class H, class... Tail, class F, class... Args>
void call_(Stream& io, void (*)(H&, Tail...), F f, Args&... args) {
  void (*f_)(H, Tail...) {};
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
template <class R, class... FArgs>
void rpcCall(Stream& io, R (*f)(FArgs...)) {
  /*
   * A dummy function pointer is prepared, which will be used to isolate
   * parameter types. The return type of this function pointer is removed to
   * avoid unneeded template expansion.
   */
  void (*f_)(FArgs...) {};
  call_(io, f_, f);
}

/*! \ingroup call
 * Call a class method.
 *
 * \sa rpcCall(Stream&, R (*)(FArgs...))
 *
 * \param io Stream.
 * \param t Tuple consisting of a pointer to a class instance and a pointer
 *   to a class method.
 */
template <class C, class P ,class R, class... FArgs>
void rpcCall(Stream& io, Tuple<C*, R (P::*)(FArgs...)> t) {
  void (*f_)(FArgs...) {};
  call_(io, f_, t);
}
