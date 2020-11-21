#ifndef SIMPLE_RPC_TYPES_TCC_
#define SIMPLE_RPC_TYPES_TCC_

#include "tuple.tcc"
#include "vector.tcc"

//! \defgroup types


/*! \ingroup types
 * Type encoding.
 *
 * \param io Input / output object.
 * \param - Value.
 */
template <class I>
void rpcTypeOf(I& io, bool) {
  rpcPrint(io, "?");
}

/*! \ingroup types
 * \copydoc rpcTypeOf(I&, bool) */
template <class I>
void rpcTypeOf(I& io, char) {
  rpcPrint(io, "c");
}

/*! \ingroup types
 * \copydoc rpcTypeOf(I&, bool) */
template <class I>
void rpcTypeOf(I& io, signed char) {
  rpcPrint(io, "b");
}

/*! \ingroup types
 * \copydoc rpcTypeOf(I&, bool) */
template <class I>
void rpcTypeOf(I& io, unsigned char) {
  rpcPrint(io, "B");
}

/*! \ingroup types
 * \copydoc rpcTypeOf(I&, bool) */
template <class I>
void rpcTypeOf(I& io, short int) {
  rpcPrint(io, "h");
}

/*! \ingroup types
 * \copydoc rpcTypeOf(I&, bool) */
template <class I>
void rpcTypeOf(I& io, unsigned short int) {
  rpcPrint(io, "H");
}

/*! \ingroup types
 * \copydoc rpcTypeOf(I&, bool) */
template <class I>
void rpcTypeOf(I& io, long int) {
  rpcPrint(io, "l");
}

/*! \ingroup types
 * \copydoc rpcTypeOf(I&, bool) */
template <class I>
void rpcTypeOf(I& io, unsigned long int) {
  rpcPrint(io, "L");
}

/*! \ingroup types
 * \copydoc rpcTypeOf(I&, bool) */
template <class I>
void rpcTypeOf(I& io, long long int) {
  rpcPrint(io, "q");
}

/*! \ingroup types
 * \copydoc rpcTypeOf(I&, bool) */
template <class I>
void rpcTypeOf(I& io, unsigned long long int) {
  rpcPrint(io, "Q");
}

/*! \ingroup types
 * \copydoc rpcTypeOf(I&, bool) */
template <class I>
void rpcTypeOf(I& io, float) {
  rpcPrint(io, "f");
}

/*! \ingroup types
 * \copydoc rpcTypeOf(I&, bool) */
template <class I>
void rpcTypeOf(I& io, String&) {
  rpcPrint(io, "s");
}

/*! \ingroup types
 * \copydoc rpcTypeOf(I&, bool) */
template <class I>
void rpcTypeOf(I& io, char*) {
  rpcPrint(io, "s");
}

/*! \ingroup types
 * \copydoc rpcTypeOf(I&, bool) */
template <class I>
void rpcTypeOf(I& io, char const*) {
  rpcPrint(io, "s");
}

/*
 * The `int` and `double` type sizes vary between boards, see:
 * https://www.arduino.cc/reference/en/language/variables/data-types/
 */

/*! \ingroup types
 * \copydoc rpcTypeOf(I&, bool) */
template <class I>
void rpcTypeOf(I& io, int) {
  if (sizeof(int) == 2) {
    rpcPrint(io, "h");
    return;
  }
  rpcPrint(io, "i");
}

/*! \ingroup types
 * \copydoc rpcTypeOf(I&, bool) */
template <class I>
void rpcTypeOf(I& io, unsigned int) {
  if (sizeof(unsigned int) == 2) {
    rpcPrint(io, "H");
    return;
  }
  rpcPrint(io, "I");
}

/*! \ingroup types
 * \copydoc rpcTypeOf(I&, bool) */
template <class I>
void rpcTypeOf(I& io, double) {
  if (sizeof(double) == 4) {
    rpcPrint(io, "f");
    return;
  }
  rpcPrint(io, "d");
}


//! Recursion terminator for `rpcTypeOf(Tuple&)`.
template <class I>
void rpcTypeOf(I&, Tuple<>&) {}

/*! \ingroup types
 * Get the types of all members of a Tuple.
 *
 * \param io Input / output object.
 * \param t Tuple.
 */
template <class I, class... Membs>
void rpcTypeOf(I& io, Tuple<Membs...>& t) {
  rpcTypeOf(io, t.head);
  rpcTypeOf(io, t.tail);
}


/*! \ingroup types
 * Get the types of all members of an Object.
 *
 * \param io Input / output object.
 * \param t Object.
 */
template <class I, class... Membs>
void rpcTypeOf(I& io, Object<Membs...>& o) {
  rpcPrint(io, "(");
  rpcTypeOf(io, (Tuple<Membs...>&)o);
  rpcPrint(io, ")");
}


/*! \ingroup types
 * \copydoc rpcTypeOf(I&, bool) */
template <class I, class T>
void rpcTypeOf(I& io, Vector<T>&) {
  T x;

  rpcPrint(io, "[");
  rpcTypeOf(io, x);
  rpcPrint(io, "]");
}

/*! \ingroup types
 * \copydoc rpcTypeOf(I&, bool) */
template <class I, class T>
void rpcTypeOf(I& io, T*) {
  // TODO: Merge with Vector?
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
template <class I>
void hardwareDefs(I& io) {
  size_t i = 0xff;

  if (((uint8_t*)&i)[0] == 0xff) {
    rpcPrint(io, "<");
  }
  else {
    rpcPrint(io, ">");
  }
  rpcTypeOf(io, i);
}

#endif
