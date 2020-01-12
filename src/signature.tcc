#ifndef SIMPLE_RPC_SIGNATURE_TCC_
#define SIMPLE_RPC_SIGNATURE_TCC_

/**
 * @file signature.tcc
 *
 * Function signature analysis and encoding to a string.
 */

#include "types.tcc"


/**
 * Recursion terminator for @a _parameterTypes().
 *
 * @private
 */
inline String _parameterTypes(void (*)(void)) {
  return "";
}

/**
 * Get the types of all function parameters.
 *
 * We isolate the first parameter type @a T from function pointer @a *f_. This
 * type is used to instantiate the variable @a data, which is passed to
 * @a typeof() to encode its type. The first parameter type @a T is removed
 * from function pointer @a *f_ in the recursive call.
 *
 * @param f_ Dummy function pointer.
 *
 * @return Space separated parameter types.
 *
 * @private
 */
template <class T, class... Args>
String _parameterTypes(void (*f_)(T, Args...)) {
  T data;

  return " " + typeof(data) + _parameterTypes((void (*)(Args...))f_);
}

/// @private Parameter of type @a T&.
template <class T, class... Args>
String _parameterTypes(void (*f_)(T&, Args...)) {
  T data;

  return " " + typeof(data) + _parameterTypes((void (*)(Args...))f_);
}


/**
 * Get the signature of a function.
 *
 * We prepare a dummy function pointer, referred to as @a f_ in the template
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

  return typeof(data) + ":" + _parameterTypes((void (*)(Args...))f);
}

/// Void function.
template <class... Args>
String signature(void (*f)(Args...)) {
  return ":" + _parameterTypes(f);
}

/// Class member function.
template <class R, class C, class... Args>
String signature(R (C::*f)(Args...)) {
  R data;

  return typeof(data) + ":" + _parameterTypes((void (*)(Args...))f);
}

/// Void class member function.
template <class C, class... Args>
String signature(void (C::*f)(Args...)) {
  return ":" + _parameterTypes((void (*)(Args...))f);
}

#endif
