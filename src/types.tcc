#ifndef SIMPLE_RPC_TYPES_TCC_
#define SIMPLE_RPC_TYPES_TCC_

#include "tuple.tcc"
#include "vector.tcc"

//! \defgroup types


/*! \ingroup types
 * Type encoding.
 *
 * \param - Value.
 *
 * \return Encoded type of `Value`.
 */
inline String rpcTypeOf(bool) {
  return "?";
}

/*! \ingroup types
 * \copydoc rpcTypeOf(bool) */
inline String rpcTypeOf(char) {
  return "c";
}

/*! \ingroup types
 * \copydoc rpcTypeOf(bool) */
inline String rpcTypeOf(signed char) {
  return "b";
}

/*! \ingroup types
 * \copydoc rpcTypeOf(bool) */
inline String rpcTypeOf(unsigned char) {
  return "B";
}

/*! \ingroup types
 * \copydoc rpcTypeOf(bool) */
inline String rpcTypeOf(short int) {
  return "h";
}

/*! \ingroup types
 * \copydoc rpcTypeOf(bool) */
inline String rpcTypeOf(unsigned short int) {
  return "H";
}

/*! \ingroup types
 * \copydoc rpcTypeOf(bool) */
inline String rpcTypeOf(long int) {
  return "l";
}

/*! \ingroup types
 * \copydoc rpcTypeOf(bool) */
inline String rpcTypeOf(unsigned long int) {
  return "L";
}

/*! \ingroup types
 * \copydoc rpcTypeOf(bool) */
inline String rpcTypeOf(long long int) {
  return "q";
}

/*! \ingroup types
 * \copydoc rpcTypeOf(bool) */
inline String rpcTypeOf(unsigned long long int) {
  return "Q";
}

/*! \ingroup types
 * \copydoc rpcTypeOf(bool) */
inline String rpcTypeOf(float) {
  return "f";
}

/*! \ingroup types
 * \copydoc rpcTypeOf(bool) */
inline String rpcTypeOf(String&) {
  return "s";
}

/*! \ingroup types
 * \copydoc rpcTypeOf(bool) */
inline String rpcTypeOf(char*) {
  return "s";
}

/*! \ingroup types
 * \copydoc rpcTypeOf(bool) */
inline String rpcTypeOf(char const*) {
  return "s";
}

/*
 * The `int` and `double` type sizes vary between boards, see:
 * https://www.arduino.cc/reference/en/language/variables/data-types/
 */

/*! \ingroup types
 * \copydoc rpcTypeOf(bool) */
inline String rpcTypeOf(int) {
  if (sizeof(int) == 2) {
    return "h";
  }
  return "i";
}

/*! \ingroup types
 * \copydoc rpcTypeOf(bool) */
inline String rpcTypeOf(unsigned int) {
  if (sizeof(unsigned int) == 2) {
    return "H";
  }
  return "I";
}

/*! \ingroup types
 * \copydoc rpcTypeOf(bool) */
inline String rpcTypeOf(double) {
  if (sizeof(double) == 4) {
    return "f";
  }
  return "d";
}


//! Recursion terminator for `rpcTypeOf(Tuple&)`.
inline String rpcTypeOf(Tuple<>&) {
  return "";
}

/*! \ingroup types
 * Get the types of all members of a Tuple.
 *
 * \param t Tuple.
 *
 * \return Tuple member types.
 */
template <class... Membs>
String rpcTypeOf(Tuple<Membs...>& t) {
  return rpcTypeOf(t.head) + rpcTypeOf(t.tail);
}


/*! \ingroup types
 * Get the types of all members of an Object.
 *
 * \param t Object.
 *
 * \return Object member types.
 */
template <class... Membs>
String rpcTypeOf(Object<Membs...>& o) {
  return "(" + rpcTypeOf((Tuple<Membs...>&)o) + ")";
}


/*! \ingroup types
 * \copydoc rpcTypeOf(bool) */
template <class T>
String rpcTypeOf(Vector<T>&) {
  T x;

  return "[" + rpcTypeOf(x) + "]";
}

/*! \ingroup types
 * \copydoc rpcTypeOf(bool) */
template <class T>
String rpcTypeOf(T*) {
  T x;

  return "[" + rpcTypeOf(x) + "]";
}


/*! \ingroup types
 * Determine endianness and type of `size_t`.
 *
 * \return Endianness and type of `size_t`.
 */
inline String hardwareDefs(void) {
  size_t i = 0xff;

  if (((uint8_t*)&i)[0] == 0xff) {
    return "<" + rpcTypeOf(i);
  }
  return ">" + rpcTypeOf(i);
}

#endif
