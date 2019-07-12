#ifndef __SIMPLE_RPC_SIGNATURE_TCC__
#define __SIMPLE_RPC_SIGNATURE_TCC__

#include "types.tcc"


/**
 * Recursion terminator for {_parameterTypes()}.
 */
inline String _parameterTypes(void (*)(void)) {
  return "";
}

/**
 * Get the types of all function parameters.
 *
 * We isolate the first parameter type {T} from function pointer {*f_}. This
 * type is used to instantiate the variable {data}, which is passed to
 * {_typeof()} to encode its type. The first parameter type {T} is removed from
 * function pointer {*f_} in the recursive call.
 *
 * @param f_ Dummy function pointer.
 *
 * @return Space separated parameter types.
 */
template <class T, class... Args>
String _parameterTypes(void (*f_)(T, Args...)) {
  T data;

  return " " + _typeof(data) + _parameterTypes((void (*)(Args...))f_);
}

// Parameter of type {T&}.
template <class T, class... Args>
String _parameterTypes(void (*f_)(T&, Args...)) {
  T data;

  return " " + _typeof(data) + _parameterTypes((void (*)(Args...))f_);
}


/**
 * Get the signature of a function.
 *
 * We prepare a dummy function pointer, referred to as {f_} in the template
 * functions above, which will be used to isolate parameter types. The return
 * type of this function pointer is removed to avoid unneeded template
 * expansion.
 *
 * @param f Function pointer.
 *
 * @return Function signature.
 */
template <class R, class... Args>
String signature(R (*f)(Args...)) {
  R data;

  return _typeof(data) + ":" + _parameterTypes((void (*)(Args...))f);
}

// Void function.
template <class... Args>
String signature(void (*f)(Args...)) {
  return ":" + _parameterTypes(f);
}

// Class member function.
template <class R, class C, class... Args>
String signature(R (C::*f)(Args...)) {
  R data;

  return _typeof(data) + ":" + _parameterTypes((void (*)(Args...))f);
}

// Void class member function.
template <class C, class... Args>
String signature(void (C::*f)(Args...)) {
  return ":" + _parameterTypes((void (*)(Args...))f);
}

#endif
