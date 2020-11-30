#ifndef SIMPLE_RPC_TYPES_TCC_
#define SIMPLE_RPC_TYPES_TCC_

#include "print.tcc"
#include "tuple.tcc"
#include "vector.tcc"

//! \defgroup types


/*! \ingroup types
 * Type encoding.
 *
 * \param io Input / output object.
 * \param - Value.
 */
inline void rpcTypeOf(Stream& io, bool) {
  rpcPrint(io, "?");
}

/*! \ingroup types
 * \copydoc rpcTypeOf(Stream&, bool) */
inline void rpcTypeOf(Stream& io, char) {
  rpcPrint(io, "c");
}

/*! \ingroup types
 * \copydoc rpcTypeOf(Stream&, bool) */
inline void rpcTypeOf(Stream& io, signed char) {
  rpcPrint(io, "b");
}

/*! \ingroup types
 * \copydoc rpcTypeOf(Stream&, bool) */
inline void rpcTypeOf(Stream& io, unsigned char) {
  rpcPrint(io, "B");
}

/*! \ingroup types
 * \copydoc rpcTypeOf(Stream&, bool) */
inline void rpcTypeOf(Stream& io, short int) {
  rpcPrint(io, "h");
}

/*! \ingroup types
 * \copydoc rpcTypeOf(Stream&, bool) */
inline void rpcTypeOf(Stream& io, unsigned short int) {
  rpcPrint(io, "H");
}

/*! \ingroup types
 * \copydoc rpcTypeOf(Stream&, bool) */
inline void rpcTypeOf(Stream& io, long int) {
  rpcPrint(io, "l");
}

/*! \ingroup types
 * \copydoc rpcTypeOf(Stream&, bool) */
inline void rpcTypeOf(Stream& io, unsigned long int) {
  rpcPrint(io, "L");
}

/*! \ingroup types
 * \copydoc rpcTypeOf(Stream&, bool) */
inline void rpcTypeOf(Stream& io, long long int) {
  rpcPrint(io, "q");
}

/*! \ingroup types
 * \copydoc rpcTypeOf(Stream&, bool) */
inline void rpcTypeOf(Stream& io, unsigned long long int) {
  rpcPrint(io, "Q");
}

/*! \ingroup types
 * \copydoc rpcTypeOf(Stream&, bool) */
inline void rpcTypeOf(Stream& io, float) {
  rpcPrint(io, "f");
}

/*! \ingroup types
 * \copydoc rpcTypeOf(Stream&, bool) */
inline void rpcTypeOf(Stream& io, String&) {
  rpcPrint(io, "s");
}

/*! \ingroup types
 * \copydoc rpcTypeOf(Stream&, bool) */
inline void rpcTypeOf(Stream& io, char*) {
  rpcPrint(io, "s");
}

/*! \ingroup types
 * \copydoc rpcTypeOf(Stream&, bool) */
inline void rpcTypeOf(Stream& io, char const*) {
  rpcPrint(io, "s");
}

/*
 * The `int` and `double` type sizes vary between boards, see:
 * https://www.arduino.cc/reference/en/language/variables/data-types/
 */

/*! \ingroup types
 * \copydoc rpcTypeOf(Stream&, bool) */
inline void rpcTypeOf(Stream& io, int) {
  if (sizeof(int) == 2) {
    rpcPrint(io, "h");
    return;
  }
  rpcPrint(io, "i");
}

/*! \ingroup types
 * \copydoc rpcTypeOf(Stream&, bool) */
inline void rpcTypeOf(Stream& io, unsigned int) {
  if (sizeof(unsigned int) == 2) {
    rpcPrint(io, "H");
    return;
  }
  rpcPrint(io, "I");
}

/*! \ingroup types
 * \copydoc rpcTypeOf(Stream&, bool) */
inline void rpcTypeOf(Stream& io, double) {
  if (sizeof(double) == 4) {
    rpcPrint(io, "f");
    return;
  }
  rpcPrint(io, "d");
}


//! Recursion terminator for `rpcTypeOf(Tuple&)`.
inline void rpcTypeOf(Stream&, Tuple<>&) {}

/*! \ingroup types
 * Get the types of all members of a Tuple.
 *
 * \param io Input / output object.
 * \param t Tuple.
 */
template <class... Membs>
void rpcTypeOf(Stream& io, Tuple<Membs...>& t) {
  rpcTypeOf(io, t.head);
  rpcTypeOf(io, t.tail);
}


/*! \ingroup types
 * Get the types of all members of an Object.
 *
 * \param io Input / output object.
 * \param t Object.
 */
template <class... Membs>
void rpcTypeOf(Stream& io, Object<Membs...>& o) {
  rpcPrint(io, "(");
  rpcTypeOf(io, (Tuple<Membs...>&)o);
  rpcPrint(io, ")");
}


/*! \ingroup types
 * \copydoc rpcTypeOf(Stream&, bool) */
template <class T>
void rpcTypeOf(Stream& io, Vector<T>&) {
  T x;

  rpcPrint(io, "[");
  rpcTypeOf(io, x);
  rpcPrint(io, "]");
}

/*! \ingroup types
 * \copydoc rpcTypeOf(Stream&, bool) */
template <class T>
void rpcTypeOf(Stream& io, T*) {
  T x;

  rpcPrint(io, "[");
  rpcTypeOf(io, x);
  rpcPrint(io, "]");
}


/*! \ingroup types
 * Determine endianness and type of `size_t`.
 *
 * \param io Input / output object.
 */
inline void hardwareDefs(Stream& io) {
  size_t i = 0xff;

  if (((uint8_t*)&i)[0] == 0xff) {
    rpcPrint(io, "<");
  }
  else {
    rpcPrint(io, ">");
  }
  rpcTypeOf(io, i);
  rpcPrint(io, '\0');
}

#endif
