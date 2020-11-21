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
 */
inline void rpcTypeOf(Collector& col, bool) {
  col.add("?");
}

/*! \ingroup types
 * \copydoc rpcTypeOf(bool) */
inline void rpcTypeOf(Collector& col, char) {
  col.add("c");
}

/*! \ingroup types
 * \copydoc rpcTypeOf(bool) */
inline void rpcTypeOf(Collector& col, signed char) {
  col.add("b");
}

/*! \ingroup types
 * \copydoc rpcTypeOf(bool) */
inline void rpcTypeOf(Collector& col, unsigned char) {
  col.add("B");
}

/*! \ingroup types
 * \copydoc rpcTypeOf(bool) */
inline void rpcTypeOf(Collector& col, short int) {
  col.add("h");
}

/*! \ingroup types
 * \copydoc rpcTypeOf(bool) */
inline void rpcTypeOf(Collector& col, unsigned short int) {
  col.add("H");
}

/*! \ingroup types
 * \copydoc rpcTypeOf(bool) */
inline void rpcTypeOf(Collector& col, long int) {
  col.add("l");
}

/*! \ingroup types
 * \copydoc rpcTypeOf(bool) */
inline void rpcTypeOf(Collector& col, unsigned long int) {
  col.add("L");
}

/*! \ingroup types
 * \copydoc rpcTypeOf(bool) */
inline void rpcTypeOf(Collector& col, long long int) {
  col.add("q");
}

/*! \ingroup types
 * \copydoc rpcTypeOf(bool) */
inline void rpcTypeOf(Collector& col, unsigned long long int) {
  col.add("Q");
}

/*! \ingroup types
 * \copydoc rpcTypeOf(bool) */
inline void rpcTypeOf(Collector& col, float) {
  col.add("f");
}

/*! \ingroup types
 * \copydoc rpcTypeOf(bool) */
inline void rpcTypeOf(Collector& col, String&) {
  col.add("s");
}

/*! \ingroup types
 * \copydoc rpcTypeOf(bool) */
inline void rpcTypeOf(Collector& col, char*) {
  col.add("s");
}

/*! \ingroup types
 * \copydoc rpcTypeOf(bool) */
inline void rpcTypeOf(Collector& col, char const*) {
  col.add("s");
}

/*
 * The `int` and `double` type sizes vary between boards, see:
 * https://www.arduino.cc/reference/en/language/variables/data-types/
 */

/*! \ingroup types
 * \copydoc rpcTypeOf(bool) */
inline void rpcTypeOf(Collector& col, int) {
  if (sizeof(int) == 2) {
    col.add("h");
    return;
  }
  col.add("i");
}

/*! \ingroup types
 * \copydoc rpcTypeOf(bool) */
inline void rpcTypeOf(Collector& col, unsigned int) {
  if (sizeof(unsigned int) == 2) {
    col.add("H");
    return;
  }
  col.add("I");
}

/*! \ingroup types
 * \copydoc rpcTypeOf(bool) */
inline void rpcTypeOf(Collector& col, double) {
  if (sizeof(double) == 4) {
    col.add("f");
    return;
  }
  col.add("d");
}


//! Recursion terminator for `rpcTypeOf(Tuple&)`.
inline void rpcTypeOf(Collector&, Tuple<>&) {}

/*! \ingroup types
 * Get the types of all members of a Tuple.
 *
 * \param t Tuple.
 */
template <class... Membs>
void rpcTypeOf(Collector& col, Tuple<Membs...>& t) {
  rpcTypeOf(col, t.head);
  rpcTypeOf(col, t.tail);
}


/*! \ingroup types
 * Get the types of all members of an Object.
 *
 * \param t Object.
 */
template <class... Membs>
void rpcTypeOf(Collector& col, Object<Membs...>& o) {
  col.add("(");
  rpcTypeOf(col, (Tuple<Membs...>&)o);
  col.add(")");
}


/*! \ingroup types
 * \copydoc rpcTypeOf(bool) */
template <class T>
void rpcTypeOf(Collector& col, Vector<T>&) {
  T x;

  col.add("[");
  rpcTypeOf(col, x);
  col.add("]");
}

/*! \ingroup types
 * \copydoc rpcTypeOf(bool) */
template <class T>
void rpcTypeOf(Collector& col, T*) {
  T x;

  col.add("[");
  rpcTypeOf(col, x);
  col.add("]");
}


/*! \ingroup types
 * Determine endianness and type of `size_t`.
 */
inline void hardwareDefs(Collector& col) {
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
