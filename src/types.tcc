#pragma once

#include "array.tcc"
#include "tuple.tcc"
#include "vector.tcc"
#include "write.tcc"

//! \defgroup types


/*! \ingroup types
 * Type encoding.
 *
 * \param io Stream.
 * \param - Value.
 */
inline void rpcTypeOf(Stream& io, bool) {
  rpcWrite(io, '?');
}

/*! \ingroup types
 * \copydoc rpcTypeOf(Stream&, bool) */
inline void rpcTypeOf(Stream& io, char) {
  rpcWrite(io, 'c');
}

/*! \ingroup types
 * \copydoc rpcTypeOf(Stream&, bool) */
inline void rpcTypeOf(Stream& io, signed char) {
  rpcWrite(io, 'b');
}

/*! \ingroup types
 * \copydoc rpcTypeOf(Stream&, bool) */
inline void rpcTypeOf(Stream& io, unsigned char) {
  rpcWrite(io, 'B');
}

/*! \ingroup types
 * \copydoc rpcTypeOf(Stream&, bool) */
inline void rpcTypeOf(Stream& io, short int) {
  rpcWrite(io, 'h');
}

/*! \ingroup types
 * \copydoc rpcTypeOf(Stream&, bool) */
inline void rpcTypeOf(Stream& io, unsigned short int) {
  rpcWrite(io, 'H');
}

/*! \ingroup types
 * \copydoc rpcTypeOf(Stream&, bool) */
inline void rpcTypeOf(Stream& io, long int) {
  rpcWrite(io, 'l');
}

/*! \ingroup types
 * \copydoc rpcTypeOf(Stream&, bool) */
inline void rpcTypeOf(Stream& io, unsigned long int) {
  rpcWrite(io, 'L');
}

/*! \ingroup types
 * \copydoc rpcTypeOf(Stream&, bool) */
inline void rpcTypeOf(Stream& io, long long int) {
  rpcWrite(io, 'q');
}

/*! \ingroup types
 * \copydoc rpcTypeOf(Stream&, bool) */
inline void rpcTypeOf(Stream& io, unsigned long long int) {
  rpcWrite(io, 'Q');
}

/*! \ingroup types
 * \copydoc rpcTypeOf(Stream&, bool) */
inline void rpcTypeOf(Stream& io, float) {
  rpcWrite(io, 'f');
}

/*! \ingroup types
 * \copydoc rpcTypeOf(Stream&, bool) */
inline void rpcTypeOf(Stream& io, String&) {
  rpcWrite(io, 's');
}

/*! \ingroup types
 * \copydoc rpcTypeOf(Stream&, bool) */
inline void rpcTypeOf(Stream& io, char*) {
  rpcWrite(io, 's');
}

/*! \ingroup types
 * \copydoc rpcTypeOf(Stream&, bool) */
inline void rpcTypeOf(Stream& io, char const*) {
  rpcWrite(io, 's');
}

/*! \ingroup types
 * \copydoc rpcTypeOf(Stream&, bool) */
inline void rpcTypeOf(Stream& io, int) {
  if (sizeof(int) == 2) {
    rpcWrite(io, 'h');
    return;
  }
  rpcWrite(io, 'i');
}

/*! \ingroup types
 * \copydoc rpcTypeOf(Stream&, bool) */
inline void rpcTypeOf(Stream& io, unsigned int) {
  if (sizeof(unsigned int) == 2) {
    rpcWrite(io, 'H');
    return;
  }
  rpcWrite(io, 'I');
}

/*! \ingroup types
 * \copydoc rpcTypeOf(Stream&, bool) */
inline void rpcTypeOf(Stream& io, double) {
  if (sizeof(double) == 4) {
    rpcWrite(io, 'f');
    return;
  }
  rpcWrite(io, 'd');
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
  rpcWrite(io, '(');
  rpcTypeOf_(io, t);
  rpcWrite(io, ')');
}


/*! \ingroup types
 * \copydoc rpcTypeOf(Stream&, bool) */
template <class T>
void rpcTypeOf(Stream& io, Vector<T>&) {
  rpcWrite(io, '[');
  T x {};
  rpcTypeOf(io, x);
  rpcWrite(io, ']');
}

/*! \ingroup types
 * \copydoc rpcTypeOf(Stream&, bool) */
template <class T, size_t n>
void rpcTypeOf(Stream& io, Array<T, n>&) {
  rpcWrite(io, '[');
  size_t n_ {n};
  rpcWrite(io, n_);
  T x {};
  rpcTypeOf(io, x);
  rpcWrite(io, ']');
}

/*! \ingroup types
 * \copydoc rpcTypeOf(Stream&, bool) */
template <class T>
void rpcTypeOf(Stream& io, T*) {
  rpcWrite(io, '[');
  T x {};
  rpcTypeOf(io, x);
  rpcWrite(io, ']');
}


/*! \ingroup types
 * Determine endianness and type of `size_t`.
 *
 * \param io Stream.
 */
inline void hardwareDefs(Stream& io) {
  size_t i {0xff};

  if (reinterpret_cast<uint8_t*>(&i)[0] == 0xff) {
    rpcWrite(io, '<');
  }
  else {
    rpcWrite(io, '>');
  }

  rpcTypeOf(io, i);
  rpcWrite(io, '\0');
}
