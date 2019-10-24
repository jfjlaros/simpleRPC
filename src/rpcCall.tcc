#ifndef SIMPLE_RPC_RPCCALL_TCC_
#define SIMPLE_RPC_RPCCALL_TCC_

/**
 * @file rpcCall.tcc
 *
 * Read values from serial, execute a function and write the result back to
 * serial.
 */

#include "read.tcc"
#include "tuple.tcc"
#include "write.tcc"


/**
 * Execute a function.
 *
 * All parameters have been collected since function pointer @a *f_ has no
 * parameter types. All values are now present in the @a args parameter pack.
 *
 * @param - Dummy function pointer.
 * @param f Function pointer.
 * @param args Parameter pack for @a f.
 *
 * @private
 */
template <class R, class... Tail, class... Args>
void _call(void (*)(void), R (*f)(Tail...), Args&... args) {
  R data = f(args...);

  _write(&data);
}

/// @private Void function.
template <class... Tail, class... Args>
void _call(void (*)(void), void (*f)(Tail...), Args&... args) {
  f(args...);
}

/// @private Class member function.
template <class C, class P, class R, class... Tail, class... Args>
void _call(void (*)(void), Tuple<C*, R (P::*)(Tail...)> t, Args&... args) {
  R data =(*t.head.*t.tail.head)(args...);

  _write(&data);
}

/// @private Void class member function.
template <class C, class P, class... Tail, class... Args>
void _call(void (*)(void), Tuple<C*, void (P::*)(Tail...)> t, Args&... args) {
  (*t.head.*t.tail.head)(args...);
}


/**
 * Collect parameters of a function from serial.
 *
 * We isolate the first parameter type @a T from function pointer @a *f_. This
 * type is used to instantiate the variable @a data, which is used to receive
 * @a sizeof(T) bytes from the serial stream. This value is passed recursively
 * to @a _call() function, adding it to the @a args parameter pack. The first
 * parameter type @a T is removed from function pointer @a *f_ in the recursive
 * call.
 *
 * @param f_ Dummy function pointer.
 * @param f Function pointer.
 * @param args Parameter pack for @a f.
 *
 * @private
 */
template <class T, class... Tail, class F, class... Args>
void _call(void (*f_)(T, Tail...), F f, Args&... args) {
  T data;

  _read(&data);
  _call((void (*)(Tail...))f_, f, args..., data);
}

/// @private Parameter of type @a T&.
template <class T, class... Tail, class F, class... Args>
void _call(void (*f_)(T&, Tail...), F f, Args&... args) {
  T data;

  _read(&data);
  _call((void (*)(Tail...))f_, f, args..., data);
}


/**
 * Set up function parameter collection, execution and writing to serial.
 *
 * We prepare a dummy function pointer, referred to as @a f_ in the template
 * functions above, which will be used to isolate parameter types. The return
 * type of this function pointer is removed to avoid unneeded template
 * expansion.
 *
 * @param f Function pointer.
 */
template <class R, class... Args>
void rpcCall(R (*f)(Args...)) {
  _call((void (*)(Args...))f, f);
}

/**
 * Class member function.
 *
 * @param t @a Tuple consisting of a pointer to a class instance and a pointer
 *   to a class method.
 */
template <class C, class P ,class R, class... Args>
void rpcCall(Tuple<C*, R (P::*)(Args...)> t) {
  _call((void (*)(Args...))t.tail.head, t);
}

#endif
