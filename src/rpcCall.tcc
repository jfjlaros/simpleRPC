#ifndef SIMPLE_RPC_RPCCALL_TCC_
#define SIMPLE_RPC_RPCCALL_TCC_

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
void _call(Stream& io, void (*)(void), R (*f)(FArgs...), Args&... args) {
  /*
   * All parameters have been collected since function pointer `*f_` has no
   * parameter types. All values are now present in the `args` parameter pack.
   */
  R data = f(args...);

  rpcWrite(io, &data);
}

/*!
 * Execute a class method.
 *
 * \param io Stream.
 * \param - Dummy function pointer.
 * \param t Internal Tuple consisting of a pointer to a class instance and a
 *   pointer to a class method.
 * \param args Parameter pack for `f`.
 */
template <class C, class P, class R, class... FArgs, class... Args>
void _call(
    Stream& io, void (*)(void), _Tuple<C*, R (P::*)(FArgs...)> t,
    Args&... args) {
  R data = (*t.head.*t.tail.head)(args...);

  rpcWrite(io, &data);
}

//! \copydoc _call(Stream&, void (*)(void), R (*)(FArgs...), Args&...)
template <class... FArgs, class... Args>
void _call(Stream&, void (*)(void), void (*f)(FArgs...), Args&... args) {
  f(args...);
}

//! \copydoc _call(Stream&, void (*)(void), R (*)(FArgs...), Args&...)
template <class C, class P, class... FArgs, class... Args>
void _call(
    Stream&, void (*)(void), _Tuple<C*, void (P::*)(FArgs...)> t,
    Args&... args) {
  (*t.head.*t.tail.head)(args...);
}


/*!
 * Collect parameters of a function.
 *
 * \param io Stream.
 * \param f_ Dummy function pointer.
 * \param f Function pointer.
 * \param args Parameter pack for `f`.
 */
template <class H, class... Tail, class F, class... Args>
void _call(Stream& io, void (*f_)(H, Tail...), F f, Args&... args) {
  /* 
   * The first parameter type `H` is isolated from function pointer `*f_`. This
   * type is used to instantiate the variable `data`, which is used to receive
   * `sizeof(H)` bytes. This value is passed recursively to `_call()` function,
   * adding it to the `args` parameter pack. The first parameter type `H` is
   * removed from function pointer `*f_` in the recursive call.
   */ 
  H data;

  rpcRead(io, &data);
  _call(io, (void (*)(Tail...))f_, f, args..., data);
  rpcDel(&data);
}

//! \copydoc _call(Stream&, void (*)(H, Tail...), F, Args&...)
template <class H, class... Tail, class F, class... Args>
void _call(Stream& io, void (*f_)(H&, Tail...), F f, Args&... args) {
  _call(io, (void (*)(H, Tail...))f_, f, args...);
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
   * A dummy function pointer is prepared, referred to as `f_` in the template
   * functions above, which will be used to isolate parameter types. The return
   * type of this function pointer is removed to avoid unneeded template
   * expansion.
   */
  _call(io, (void (*)(FArgs...))f, f);
}

/*! \ingroup call
 * Call a class method.
 *
 * \sa rpcCall(Stream&, R (*)(FArgs...))
 *
 * \param io Stream.
 * \param t Internal Tuple consisting of a pointer to a class instance and a
 *   pointer to a class method.
 */
template <class C, class P ,class R, class... FArgs>
void rpcCall(Stream& io, _Tuple<C*, R (P::*)(FArgs...)> t) {
  _call(io, (void (*)(FArgs...))t.tail.head, t);
}

#endif
