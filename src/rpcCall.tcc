#pragma once

#include "read.tcc"
#include "write.tcc"

//! \defgroup call


/*! Execute a plain function.
 *
 * \tparam T Function pointer return type.
 * \tparam Ts... Function pointer parameter types.
 * \tparam Us... Function argument types.
 *
 * \param io Stream.
 * \param - Dummy function pointer.
 * \param f Function pointer.
 * \param args Parameter pack for `f`.
 */
template <class T, class... Ts, class... Us>
void call_(Stream& io, void (*)(), T (*f)(Ts...), Us&... args) {
  T data {f(args...)};
  rpcWrite(io, &data);
}

/*! TODO: const member functions.
 * Execute a class method.
 *
 * \tparam C Class instance type.
 * \tparam P Class instance parent type.
 * \tparam T Class member function pointer return type.
 * \tparam Ts... Class member function pointer parameter types.
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
void call_(Stream& io, void (*)(), void (*f)(Ts...), Us&... args) {
  f(args...);

  uint8_t data {0};
  rpcWrite(io, &data);
}

//! \copydoc call_(Stream&, void (*)(), T (*)(Ts...), Us&...)
template <class C, class P, class... Ts, class... Us>
void call_(
    Stream& io, void (*)(), Tuple<C*, void (P::*)(Ts...)> t, Us&... args) {
  (*t.head.*t.tail.head)(args...);

  uint8_t data {0};
  rpcWrite(io, &data);
}


/*! Collect parameters of a function.
 *
 * \tparam T Function pointer return type.
 * \tparam Ts... Function pointer parameter types.
 * \tparam F Function pointer type.
 * \tparam Us... Function argument types.
 *
 * \param io Stream.
 * \param - Dummy function pointer.
 * \param f Function pointer.
 * \param args Parameter pack for `f`.
 */
template <class T, class... Ts, class F, class... Us>
void call_(Stream& io, void (*)(T, Ts...), F f, Us&... args) {
  T data;
  rpcRead(io, &data);

  void (*f_)(Ts...) {};
  call_(io, f_, f, args..., data);
}

//! \copydoc call_(Stream&, void (*)(T, Ts...), F, Us&...)
template <class T, class... Ts, class F, class... Us>
void call_(Stream& io, void (*)(T&, Ts...), F f, Us&... args) {
  void (*f_)(T, Ts...) {};
  call_(io, f_, f, args...);
}

//! \copydoc call_(Stream&, void (*)(T, Ts...), F, Us&...)
template <class T, class... Ts, class F, class... Us>
void call_(Stream& io, void (*)(T const*, Ts...), F f, Us&... args) {
  Vector<T> data;
  rpcRead(io, &data);

  void (*f_)(Ts...) {};
  T* data_ {data.data()};
  call_(io, f_, f, args..., data_);
}

//! \copydoc call_(Stream&, void (*)(T, Ts...), F, Us&...)
template <class... Ts, class F, class... Us>
void call_(Stream& io, void (*)(char const*, Ts...), F f, Us&... args) {
  String_ data;
  rpcRead(io, &data);

  void (*f_)(Ts...) {};
  char* data_ {data.data()};
  call_(io, f_, f, args..., data_);
}

//! \copydoc call_(Stream&, void (*)(T, Ts...), F, Us&...)
template <class... Ts, class F, class... Us>
void call_(Stream& io, void (*)(String&, Ts...), F f, Us&... args) {
  String data;
  rpcRead(io, &data);

  void (*f_)(Ts...) {};
  call_(io, f_, f, args..., data);
}

//! \copydoc call_(Stream&, void (*)(T, Ts...), F, Us&...)
template <class T, class... Ts, class F, class... Us>
void call_(Stream& io, void (*)(T*, Ts...), F f, Us&... args) {
  void (*f_)(T const*, Ts...) {};
  call_(io, f_, f, args...);
}


/*! \ingroup call
 * Call a function.
 *
 * Parameter values for `f` are read from `io`, after which `f` is called.
 * Any return value is written back to `io`.
 *
 * \tparam T Function pointer return type.
 * \tparam Ts... Function pointer parameter types.
 *
 * \param io Stream.
 * \param f Function pointer.
 */
template <class T, class... Ts>
void rpcCall(Stream& io, T (*f)(Ts...)) {
  void (*f_)(Ts...) {};
  call_(io, f_, f);
}

/*! \ingroup call
 * Call a class method.
 *
 * \sa rpcCall(Stream&, T (*)(Ts...))
 *
 * \tparam C Class instance type.
 * \tparam P Class instance parent type.
 * \tparam T Class member function pointer return type.
 * \tparam Ts... Class member function pointer parameter types.
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
