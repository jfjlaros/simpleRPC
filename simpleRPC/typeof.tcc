#ifndef __SIMPLE_RPC_TYPEOF_TCC__
#define __SIMPLE_RPC_TYPEOF_TCC__

#include "print.tcc"


/*
 * Type encoding functions.
 *
 * See https://docs.python.org/2/library/struct.html for an explanation of the
 * encoding.
 */

const char *_typeof(char) {
  return "c";
}

const char *_typeof(signed char) {
  return "b";
}

const char *_typeof(unsigned char) {
  return "B";
}

const char *_typeof(short int) {
  return "<h";
}

const char *_typeof(unsigned short int) {
  return "<H";
}

const char *_typeof(int) {
  return "<i";
}

const char *_typeof(unsigned int) {
  return "<I";
}

const char *_typeof(long int) {
  return "<l";
}

const char *_typeof(unsigned long int) {
  return "<L";
}

const char *_typeof(long long int) {
  return "<q";
}

const char *_typeof(unsigned long long int) {
  return "<Q";
}

const char *_typeof(float) {
  return "<f";
}

const char *_typeof(double) {
  return "<d";
}


/*
 * Recursion terminator for {_getParameterTypes}.
 */
void _getParameterTypes(void (*)(void)) {}

/**
 * Get the types of all function parameters.
 *
 * We isolate the first parameter type {T} from function pointer {*f_}. This
 * type is used to instantiate the variable {data}, which is passed to
 * {_typeof()} to encode its type. The first parameter type {T} is removed from
 * function pointer {*f_} in the recursive call.
 *
 * @arg {void (*)(T, Args...)} f_ - Dummy function pointer.
 */
template<class T, class... Args>
void _getParameterTypes(void (*f_)(T, Args...)) {
  T data;

  _print(" ", _typeof(data));
  _getParameterTypes((void (*)(Args...))f_);
}


/**
 * Get the signature of a function that does not return a value.
 *
 * @arg {void (*)(Args...)} f - Function pointer.
 */
template<class... Args>
void signature(void (*f)(Args...)) {
  _print(":");
  _getParameterTypes(f);
}

/**
 * Get the signature of a function that does return a value.
 *
 * We prepare a dummy function pointer, referred to as {f_} in the template
 * functions above, which will be used to isolate parameter types. The return
 * type of this function pointer is removed to avoid unneeded template
 * expansion.
 *
 * @arg {R (*)(Args...)} f - Function pointer.
 */
template<class R, class... Args>
void signature(R (*f)(Args...)) {
  R data;

  _print(_typeof(data), ":");
  _getParameterTypes((void (*)(Args...))f);
}

#endif
