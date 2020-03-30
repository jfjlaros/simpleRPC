#ifndef SIMPLE_RPC_TYPES_TCC_
#define SIMPLE_RPC_TYPES_TCC_

/**
 * Type analysis and encoding.
 */

#include "tuple.tcc"
#include "vector.tcc"


/*
 * Type encoding functions.
 *
 * For more information about the encoding:
 * https://docs.python.org/3.5/library/struct.html#format-strings
 */
inline String rpcTypeOf(bool) {
  return "?";
}

inline String rpcTypeOf(char) {
  return "c";
}

inline String rpcTypeOf(signed char) {
  return "b";
}

inline String rpcTypeOf(unsigned char) {
  return "B";
}

inline String rpcTypeOf(short int) {
  return "h";
}

inline String rpcTypeOf(unsigned short int) {
  return "H";
}

inline String rpcTypeOf(long int) {
  return "l";
}

inline String rpcTypeOf(unsigned long int) {
  return "L";
}

inline String rpcTypeOf(long long int) {
  return "q";
}

inline String rpcTypeOf(unsigned long long int) {
  return "Q";
}

inline String rpcTypeOf(float) {
  return "f";
}

inline String rpcTypeOf(String&) {
  return "s";
}

inline String rpcTypeOf(char*) {
  return "s";
}

inline String rpcTypeOf(const char*) {
  return "s";
}

/*
 * The @a int and @a double type sizes vary between boards, see:
 * https://www.arduino.cc/reference/en/language/variables/data-types/
 */
inline String rpcTypeOf(int) {
  if (sizeof(int) == 2) {
    return "h";
  }
  return "i";
}

inline String rpcTypeOf(unsigned int) {
  if (sizeof(unsigned int) == 2) {
    return "H";
  }
  return "I";
}

inline String rpcTypeOf(double) {
  if (sizeof(double) == 4) {
    return "f";
  }
  return "d";
}


/**
 * Recursion terminator for @a rpcTypeOf(Tuple&).
 *
 * @private
 */
inline String rpcTypeOf(Tuple<>&) {
  return "";
}

/**
 * Get the types of all members of a tuple.
 *
 * @return Tuple member types.
 */
template <class... Args>
String rpcTypeOf(Tuple<Args...>& t) {
  return rpcTypeOf(t.head) + rpcTypeOf(t.tail);
}


/**
 * Get the types of all members of an object.
 *
 * @return Object member types.
 */
template <class... Args>
String rpcTypeOf(Object<Args...>& o) {
  return "(" + rpcTypeOf((Tuple<Args...>&)o) + ")";
}


/**
 * Vector type.
 */
template <class T>
String rpcTypeOf(Vector<T>&) {
  T x;

  return "[" + rpcTypeOf(x) + "]";
}


/**
 * Determine endianness and type of @a size_t.
 *
 * @return Endianness and type of @a size_t;
 */
inline String _hardwareDefs(void) {
  size_t i = 0xff;

  if (((unsigned char*)&i)[0] == 0xff) {
    return "<" + rpcTypeOf(i);
  }
  return ">" + rpcTypeOf(i);
}

#endif
