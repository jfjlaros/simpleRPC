#ifndef __SIMPLE_RPC_TYPES_TCC__
#define __SIMPLE_RPC_TYPES_TCC__

#include "tuple.tcc"
#include "vector.tcc"


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
  return "h";
}

inline String _typeof(unsigned short int) {
  return "H";
}

inline String _typeof(long int) {
  return "l";
}

inline String _typeof(unsigned long int) {
  return "L";
}

inline String _typeof(long long int) {
  return "q";
}

inline String _typeof(unsigned long long int) {
  return "Q";
}

inline String _typeof(float) {
  return "f";
}

inline String _typeof(String) {
  return "s";
}

/*
 * The {int} and {double} type sizes vary between boards, see:
 * https://www.arduino.cc/reference/en/language/variables/data-types/
 */
inline String _typeof(int) {
  if (sizeof(int) == 2) {
    return "h";
  }
  return "i";
}

inline String _typeof(unsigned int) {
  if (sizeof(unsigned int) == 2) {
    return "H";
  }
  return "I";
}

inline String _typeof(double) {
  if (sizeof(double) == 4) {
    return "f";
  }
  return "d";
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
String _typeof(Object <Args...>o) {
  return "(" + _typeof((Tuple <Args...>)o) + ")";
}


/**
 * Vector type.
 */
template<class T>
String _typeof(Vector <T>) {
  T x;

  return "[" + _typeof(x) + "]";
}


/**
 * Determine endianness and type of {size_t}.
 *
 * @return {String} - Endianness and type of {size_t};
 */
inline String _hardwareDefs(void) {
  size_t i = 0xff;

  if (((unsigned char *)&i)[0] == 0xff) {
    return "<" + _typeof(i);
  }
  return ">" + _typeof(i);
}

#endif
