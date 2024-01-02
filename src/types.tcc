#pragma once

#include "print.tcc"
#include "tuple.tcc"
#include "vector.tcc"
#include "array.tcc"

//! \defgroup types


/*! \ingroup types
 * Type encoding.
 *
 * \param io Stream.
 * \param - Value.
 */
inline void rpcTypeOf(Stream& io, bool) {
  rpcPrint(io, '?');
}

/*! \ingroup types
 * \copydoc rpcTypeOf(Stream&, bool) */
inline void rpcTypeOf(Stream& io, char) {
  rpcPrint(io, 'c');
}

/*! \ingroup types
 * \copydoc rpcTypeOf(Stream&, bool) */
inline void rpcTypeOf(Stream& io, signed char) {
  rpcPrint(io, 'b');
}

/*! \ingroup types
 * \copydoc rpcTypeOf(Stream&, bool) */
inline void rpcTypeOf(Stream& io, unsigned char) {
  rpcPrint(io, 'B');
}

/*! \ingroup types
 * \copydoc rpcTypeOf(Stream&, bool) */
inline void rpcTypeOf(Stream& io, short int) {
  rpcPrint(io, 'h');
}

/*! \ingroup types
 * \copydoc rpcTypeOf(Stream&, bool) */
inline void rpcTypeOf(Stream& io, unsigned short int) {
  rpcPrint(io, 'H');
}

/*! \ingroup types
 * \copydoc rpcTypeOf(Stream&, bool) */
inline void rpcTypeOf(Stream& io, long int) {
  rpcPrint(io, 'l');
}

/*! \ingroup types
 * \copydoc rpcTypeOf(Stream&, bool) */
inline void rpcTypeOf(Stream& io, unsigned long int) {
  rpcPrint(io, 'L');
}

/*! \ingroup types
 * \copydoc rpcTypeOf(Stream&, bool) */
inline void rpcTypeOf(Stream& io, long long int) {
  rpcPrint(io, 'q');
}

/*! \ingroup types
 * \copydoc rpcTypeOf(Stream&, bool) */
inline void rpcTypeOf(Stream& io, unsigned long long int) {
  rpcPrint(io, 'Q');
}

/*! \ingroup types
 * \copydoc rpcTypeOf(Stream&, bool) */
inline void rpcTypeOf(Stream& io, float) {
  rpcPrint(io, 'f');
}

/*! \ingroup types
 * \copydoc rpcTypeOf(Stream&, bool) */
inline void rpcTypeOf(Stream& io, String&) {
  rpcPrint(io, 's');
}

/*! \ingroup types
 * \copydoc rpcTypeOf(Stream&, bool) */
inline void rpcTypeOf(Stream& io, char*) {
  rpcPrint(io, 's');
}

/*! \ingroup types
 * \copydoc rpcTypeOf(Stream&, bool) */
inline void rpcTypeOf(Stream& io, char const*) {
  rpcPrint(io, 's');
}

/*
 * The `int` and `double` type sizes vary between boards, see:
 * https://www.arduino.cc/reference/en/language/variables/data-types/
 */

/*! \ingroup types
 * \copydoc rpcTypeOf(Stream&, bool) */
inline void rpcTypeOf(Stream& io, int) {
  if (sizeof(int) == 2) {
    rpcPrint(io, 'h');
    return;
  }
  rpcPrint(io, 'i');
}

/*! \ingroup types
 * \copydoc rpcTypeOf(Stream&, bool) */
inline void rpcTypeOf(Stream& io, unsigned int) {
  if (sizeof(unsigned int) == 2) {
    rpcPrint(io, 'H');
    return;
  }
  rpcPrint(io, 'I');
}

/*! \ingroup types
 * \copydoc rpcTypeOf(Stream&, bool) */
inline void rpcTypeOf(Stream& io, double) {
  if (sizeof(double) == 4) {
    rpcPrint(io, 'f');
    return;
  }
  rpcPrint(io, 'd');
}


//! Recursion terminator for `rpcTypeOf_(Tuple&)`.
inline void rpcTypeOf_(Stream&, Tuple<>&) {}

/*! \ingroup types
 * Get the types of all members of a Tuple.
 *
 * \param io Stream.
 * \param t Tuple.
 */
template <class... Ts>
void rpcTypeOf_(Stream& io, Tuple<Ts...>& t) {
  rpcTypeOf(io, t.head);
  rpcTypeOf_(io, t.tail);
}

template <class... Ts>
void rpcTypeOf(Stream& io, Tuple<Ts...>& t) {
  rpcPrint(io, '(');
  rpcTypeOf_(io, t);
  rpcPrint(io, ')');
}


/*! \ingroup types
 * \copydoc rpcTypeOf(Stream&, bool) */
template <class T>
void rpcTypeOf(Stream& io, Vector<T>&) {
  rpcPrint(io, '[');
  T x {};
  rpcTypeOf(io, x);
  rpcPrint(io, ']');
}

/*! \ingroup types
 * \copydoc rpcTypeOf(Stream&, bool) */
template <class T, size_t n>
void rpcTypeOf(Stream& io, Array<T, n>&) {
  rpcPrint(io, '[');
  T x {};
  rpcTypeOf(io, x);
  rpcPrint(io, ']');
}

/*! \ingroup types
 * \copydoc rpcTypeOf(Stream&, bool) */
template <class T>
void rpcTypeOf(Stream& io, T*) {
  rpcPrint(io, '[');
  T x {};
  rpcTypeOf(io, x);
  rpcPrint(io, ']');
}

// TODO: References to arrays can be returned, e.g., int (&test())[10] {}


/*! \ingroup types
 * Determine endianness and type of `size_t`.
 *
 * \param io Stream.
 */
inline void hardwareDefs(Stream& io) {
  size_t i {0xff};

  if (reinterpret_cast<uint8_t*>(&i)[0] == 0xff) {
    rpcPrint(io, '<');
  }
  else {
    rpcPrint(io, '>');
  }

  rpcTypeOf(io, i);
  rpcPrint(io, '\0');
}
