#ifndef __SIMPLE_RPC_SIGNATURE_TCC__
#define __SIMPLE_RPC_SIGNATURE_TCC__
// TODO: Isolate types.

#include "tuple.tcc"


/*
 * Prototypes needed for recursive definitions.
 */
template<class T>
  String _typeof(Vector <T>);


/*
 * Type encoding functions.
 *
 * For more information about the encoding:
 * https://docs.python.org/3.5/library/struct.html#format-strings
 */
inline String _typeof(bool) {
  return "?";
}

inline String _typeof(char) {
  return "c";
}

inline String _typeof(signed char) {
  return "b";
}

inline String _typeof(unsigned char) {
  return "B";
}

inline String _typeof(short int) {
  return "<h";
}

inline String _typeof(unsigned short int) {
  return "<H";
}

inline String _typeof(long int) {
  return "<l";
}

inline String _typeof(unsigned long int) {
  return "<L";
}

inline String _typeof(long long int) {
  return "<q";
}

inline String _typeof(unsigned long long int) {
  return "<Q";
}

inline String _typeof(float) {
  return "<f";
}

/*
 * The {int} and {double} type sizes vary between boards, see:
 * https://www.arduino.cc/reference/en/language/variables/data-types/
 */
inline String _typeof(int) {
  if (sizeof(int) == 2) {
    return "<h";
  }
  return "<i";
}

inline String _typeof(unsigned int) {
  if (sizeof(unsigned int) == 2) {
    return "<H";
  }
  return "<I";
}

inline String _typeof(double) {
  if (sizeof(double) == 4) {
    return "<f";
  }
  return "<d";
}


/*
 * String types.
 */
inline String _typeof(char *) {
  return "s";
}

inline String _typeof(const char *) {
  return "s";
}


/*
 * List types.
 */
template<class T>
String _typeof(const T *) {
  T x;

  return _typeof(x) + "*";
}

template<class T>
String _typeof(T *) {
  T x;

  return _typeof(x) + "*";
}


/**
 * Recursion terminator for {_typeof(Tuple)}.
 */
inline String _typeof(Tuple <>) {
  return "";
}

/**
 * Get the types of all members of a tuple.
 *
 * @return {String} - Tuple member types.
 */
template<class... Args>
String _typeof(Tuple <Args...>t) {
  return _typeof(t.head) + _typeof(t.tail);
}


/**
 * Get the types of all members of an object.
 *
 * @return {String} - Object member types.
 */
template<class... Args>
String _typeof(Object <Args...>t) {
  return "[" + _typeof(t.members) + "]";
}


/**
 * Vector type.
 */
template<class T>
String _typeof(Vector <T>) {
  T x;

  return "v" + _typeof(x);
}


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
 * @arg {void (*)(T, Args...)} f_ - Dummy function pointer.
 *
 * @return {String} - Space separated parameter types.
 */
template<class T, class... Args>
String _parameterTypes(void (*f_)(T, Args...)) {
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
 * @arg {R (*)(Args...)} f - Function pointer.
 *
 * @return {String} - Function signature.
 */
template<class R, class... Args>
String signature(R (*f)(Args...)) {
  R data;

  return _typeof(data) + ":" + _parameterTypes((void (*)(Args...))f);
}

// Void function.
template<class... Args>
String signature(void (*f)(Args...)) {
  return ":" + _parameterTypes(f);
}

// Class member function.
template<class R, class C, class... Args>
String signature(R (C::*f)(Args...)) {
  R data;

  return _typeof(data) + ":" + _parameterTypes((void (*)(Args...))f);
}

// Void class member function.
template<class C, class... Args>
String signature(void (C::*f)(Args...)) {
  return ":" + _parameterTypes((void (*)(Args...))f);
}

#endif
