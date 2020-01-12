#ifndef SIMPLE_RPC_TYPES_TCC_
#define SIMPLE_RPC_TYPES_TCC_

/**
 * Type analysis and encoding.
 */

#include "tuple.tcc"
#include "vector.tcc"

/*
 * Prototypes needed for recursive definitions.
 */
template <class T>
  String typeof(Vector<T>&);


/*
 * Type encoding functions.
 *
 * For more information about the encoding:
 * https://docs.python.org/3.5/library/struct.html#format-strings
 */
inline String typeof(bool) {
  return "?";
}

inline String typeof(char) {
  return "c";
}

inline String typeof(signed char) {
  return "b";
}

inline String typeof(unsigned char) {
  return "B";
}

inline String typeof(short int) {
  return "h";
}

inline String typeof(unsigned short int) {
  return "H";
}

inline String typeof(long int) {
  return "l";
}

inline String typeof(unsigned long int) {
  return "L";
}

inline String typeof(long long int) {
  return "q";
}

inline String typeof(unsigned long long int) {
  return "Q";
}

inline String typeof(float) {
  return "f";
}

inline String typeof(String) {
  return "s";
}

/*
 * The @a int and @a double type sizes vary between boards, see:
 * https://www.arduino.cc/reference/en/language/variables/data-types/
 */
inline String typeof(int) {
  if (sizeof(int) == 2) {
    return "h";
  }
  return "i";
}

inline String typeof(unsigned int) {
  if (sizeof(unsigned int) == 2) {
    return "H";
  }
  return "I";
}

inline String typeof(double) {
  if (sizeof(double) == 4) {
    return "f";
  }
  return "d";
}


/**
 * Recursion terminator for @a typeof(Tuple&).
 *
 * @private
 */
inline String typeof(Tuple<>&) {
  return "";
}

/**
 * Get the types of all members of a tuple.
 *
 * @return Tuple member types.
 */
template <class... Args>
String typeof(Tuple<Args...>& t) {
  return typeof(t.head) + typeof(t.tail);
}


/**
 * Get the types of all members of an object.
 *
 * @return Object member types.
 */
template <class... Args>
String typeof(Object<Args...>& o) {
  return "(" + typeof((Tuple<Args...>&)o) + ")";
}


/**
 * Vector type.
 */
template <class T>
String typeof(Vector<T>&) {
  T x;

  return "[" + typeof(x) + "]";
}


/**
 * Determine endianness and type of @a size_t.
 *
 * @return Endianness and type of @a size_t;
 */
inline String _hardwareDefs(void) {
  size_t i = 0xff;

  if (((unsigned char*)&i)[0] == 0xff) {
    return "<" + typeof(i);
  }
  return ">" + typeof(i);
}

#endif
