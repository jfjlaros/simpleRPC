#ifndef SIMPLE_RPC_TYPES_TCC_
#define SIMPLE_RPC_TYPES_TCC_

#include "collect.tcc"
#include "tuple.tcc"
#include "vector.tcc"

//! \defgroup types


/*! \ingroup types
 * Type encoding.
 *
 * \param - Value.
 *
 * \col.add(Encoded type of `Value`.
 */
inline void rpcTypeOf(Collection& col, bool) {
  col.add("?");
}

/*! \ingroup types
 * \copydoc rpcTypeOf(bool) */
inline void rpcTypeOf(Collection& col, char) {
  col.add("c");
}

/*! \ingroup types
 * \copydoc rpcTypeOf(bool) */
inline void rpcTypeOf(Collection& col, signed char) {
  col.add("b");
}

/*! \ingroup types
 * \copydoc rpcTypeOf(bool) */
inline void rpcTypeOf(Collection& col, unsigned char) {
  col.add("B");
}

/*! \ingroup types
 * \copydoc rpcTypeOf(bool) */
inline void rpcTypeOf(Collection& col, short int) {
  col.add("h");
}

/*! \ingroup types
 * \copydoc rpcTypeOf(bool) */
inline void rpcTypeOf(Collection& col, unsigned short int) {
  col.add("H");
}

/*! \ingroup types
 * \copydoc rpcTypeOf(bool) */
inline void rpcTypeOf(Collection& col, long int) {
  col.add("l");
}

/*! \ingroup types
 * \copydoc rpcTypeOf(bool) */
inline void rpcTypeOf(Collection& col, unsigned long int) {
  col.add("L");
}

/*! \ingroup types
 * \copydoc rpcTypeOf(bool) */
inline void rpcTypeOf(Collection& col, long long int) {
  col.add("q");
}

/*! \ingroup types
 * \copydoc rpcTypeOf(bool) */
inline void rpcTypeOf(Collection& col, unsigned long long int) {
  col.add("Q");
}

/*! \ingroup types
 * \copydoc rpcTypeOf(bool) */
inline void rpcTypeOf(Collection& col, float) {
  col.add("f");
}

/*! \ingroup types
 * \copydoc rpcTypeOf(bool) */
inline void rpcTypeOf(Collection& col, String&) {
  col.add("s");
}

/*! \ingroup types
 * \copydoc rpcTypeOf(bool) */
inline void rpcTypeOf(Collection& col, char*) {
  col.add("s");
}

/*! \ingroup types
 * \copydoc rpcTypeOf(bool) */
inline void rpcTypeOf(Collection& col, char const*) {
  col.add("s");
}

/*
 * The `int` and `double` type sizes vary between boards, see:
 * https://www.arduino.cc/reference/en/language/variables/data-types/
 */

/*! \ingroup types
 * \copydoc rpcTypeOf(bool) */
inline void rpcTypeOf(Collection& col, int) {
  if (sizeof(int) == 2) {
    col.add("h");
    return;
  }
  col.add("i");
}

/*! \ingroup types
 * \copydoc rpcTypeOf(bool) */
inline void rpcTypeOf(Collection& col, unsigned int) {
  if (sizeof(unsigned int) == 2) {
    col.add("H");
    return;
  }
  col.add("I");
}

/*! \ingroup types
 * \copydoc rpcTypeOf(bool) */
inline void rpcTypeOf(Collection& col, double) {
  if (sizeof(double) == 4) {
    col.add("f");
    return;
  }
  col.add("d");
}


//! Recursion terminator for `rpcTypeOf(Tuple&)`.
inline void rpcTypeOf(Collection& col, Tuple<>&) {
  col.add("");
}

/*! \ingroup types
 * Get the types of all members of a Tuple.
 *
 * \param t Tuple.
 *
 * \col.add(Tuple member types.
 */
template <class... Membs>
void rpcTypeOf(Collection& col, Tuple<Membs...>& t) {
  rpcTypeOf(col, t.head);
  rpcTypeOf(col, t.tail);
}


/*! \ingroup types
 * Get the types of all members of an Object.
 *
 * \param t Object.
 *
 * \col.add(Object member types.
 */
template <class... Membs>
void rpcTypeOf(Collection& col, Object<Membs...>& o) {
  col.add("(");
  rpcTypeOf(col, (Tuple<Membs...>&)o);
  col.add(")");
}


/*! \ingroup types
 * \copydoc rpcTypeOf(bool) */
template <class T>
void rpcTypeOf(Collection& col, Vector<T>&) {
  T x;

  col.add("[");
  rpcTypeOf(col, x);
  col.add("]");
}

/*! \ingroup types
 * \copydoc rpcTypeOf(bool) */
template <class T>
void rpcTypeOf(Collection& col, T*) {
  T x;

  col.add("[");
  rpcTypeOf(col, x);
  col.add("]");
}


/*! \ingroup types
 * Determine endianness and type of `size_t`.
 *
 * \col.add(Endianness and type of `size_t`.
 */
inline void hardwareDefs(Collection& col) {
  size_t i = 0xff;

  if (((uint8_t*)&i)[0] == 0xff) {
    col.add("<");
    rpcTypeOf(col, i);
    return;
  }
  col.add(">");
  rpcTypeOf(col, i);
}

#endif
