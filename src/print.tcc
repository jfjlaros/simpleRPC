#pragma once

#include "defs.h"

//! \defgroup print


/*! \ingroup print
 * Print a value to a stream.
 *
 * \param io Stream.
 * \param data Data.
 */
template <class T>
void rpcPrint(Stream& io, T data) {
  io.write(reinterpret_cast<uint8_t*>(&data), sizeof(T));
}


/*! \ingroup print
 * \copydoc rpcPrint(Stream&, T) */
inline void rpcPrint(Stream& io, char const* data) {
  for (size_t i {0}; data[i]; ++i) {
    rpcPrint(io, data[i]);
  }
}

/*! \ingroup print
 * \copydoc rpcPrint(Stream&, T) */
inline void rpcPrint(Stream& io, char* data) {
  rpcPrint(io, const_cast<char const*>(data));
}

/*! \ingroup print
 * \copydoc rpcPrint(Stream&, T) */
inline void rpcPrint(Stream& io, String& data) {
  rpcPrint(io, data.c_str());
}

/*! \ingroup print
 * \copydoc rpcPrint(Stream&, T) */
inline void rpcPrint(Stream& io, __FlashStringHelper const* data) {
  char const* p {reinterpret_cast<char const*>(data)};
  for (uint8_t c {pgm_read_byte(p)}; c; c = pgm_read_byte(++p)) {
    rpcPrint(io, c);
  }
}


/*! \ingroup print
 * Print any number of values.
 *
 * \param io Stream.
 * \param data Value to be printed.
 * \param args Remaining values.
 */
template <class T, class... Ts>
void rpcPrint(Stream& io, T data, Ts... args) {
  rpcPrint(io, data);
  rpcPrint(io, args...);
}
