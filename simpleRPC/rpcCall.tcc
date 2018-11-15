#ifndef __SIMPLE_RPC_RPCCALL_TCC__
#define __SIMPLE_RPC_RPCCALL_TCC__

#include "print.tcc"
#include "tuple.tcc"


/**
 * Write a return value to serial.
 *
 * @arg {T} data - Data.
 */
template<class T>
void _return(T data) {
  Serial.write((byte *)&data, sizeof(T));
}

// Write a return value of type {char *}.
void _return(char *data) {
  multiPrint(data, _END_OF_STRING);
}

// Write a return value of type {const char *}.
void _return(const char *data) {
  multiPrint(data, _END_OF_STRING);
}

/**
 * Execute a function.
 *
 * All parameters have been collected since function pointer {*f_} has no
 * parameter types. All values are now present in the {args} parameter pack.
 *
 * @arg {void (*)(void)} - Dummy function pointer.
 * @arg {R (*)(Tail...)} f - Function pointer.
 * @arg {Args...} args... - Parameter pack for {f}.
 */
template<class R, class... Tail, class... Args>
void _call(void (*)(void), R (*f)(Tail...), Args... args) {
  _return(f(args...));
}

// Void function.
template<class... Tail, class... Args>
void _call(void (*)(void), void (*f)(Tail...), Args... args) {
  f(args...);
}

// Class member function.
template<class C, class R, class... Tail, class... Args>
void _call(void (*)(void), Tuple <C, R (C::*)(Tail...)>t, Args... args) {
  _return(((t.head).*t.tail.head)(args...));
}

// Void class member function.
template<class C, class... Tail, class... Args>
void _call(void (*)(void), Tuple <C, void (C::*)(Tail...)>t, Args... args) {
  ((t.head).*t.tail.head)(args...);
}

/**
 * Collect parameters of a function from serial.
 *
 * We isolate the first parameter type {T} from function pointer {*f_}. This
 * type is used to instantiate the variable {data}, which is used to receive
 * {sizeof(T)} bytes from the serial stream. This value is passed recursively
 * to {_call}, adding it to the {args} parameter pack. The first parameter type
 * {T} is removed from function pointer {*f_} in the recursive call.
 *
 * @arg {void (*)(T, Tail...)} f_ - Dummy function pointer.
 * @arg {F} f - Function pointer.
 * @arg {Args...} args... - Parameter pack for {f}.
 */
template<class T, class... Tail, class F, class... Args>
void _call(void (*f_)(T, Tail...), F f, Args... args) {
  T data;

  Serial.readBytes((char *)&data, sizeof(T));
  _call((void (*)(Tail...))f_, f, args..., data);
}

// Parameter of type {char *}.
template<class... Tail, class F, class... Args>
void _call(void (*f_)(char *, Tail...), F f, Args... args) {
  _call(
    (void (*)(Tail...))f_, f, args...,
    (char *)Serial.readStringUntil(_END_OF_STRING).c_str());
}

// Parameter of type {const char *}.
template<class... Tail, class F, class... Args>
void _call(void (*f_)(const char *, Tail...), F f, Args... args) {
  _call(
    (void (*)(Tail...))f_, f, args...,
    (const char *)Serial.readStringUntil(_END_OF_STRING).c_str());
}

/**
 * Set up function parameter collection, execution and writing to serial.
 *
 * We prepare a dummy function pointer, referred to as {f_} in the template
 * functions above, which will be used to isolate parameter types. The return
 * type of this function pointer is removed to avoid unneeded template
 * expansion.
 *
 * @arg {R (*)(Args...)} f - Function pointer.
 */
template<class R, class... Args>
void rpcCall(R (*f)(Args...)) {
  _call((void (*)(Args...))f, f);
}

// Class member function.
template<class C, class R, class... Args>
void rpcCall(Tuple <C, R (C::*)(Args...)>t) {
  _call((void (*)(Args...))t.tail.head, t);
}

#endif
