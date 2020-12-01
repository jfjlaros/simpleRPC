#ifndef SIMPLE_RPC_PRINT_TCC_
#define SIMPLE_RPC_PRINT_TCC_

#include "defs.h"

//! \defgroup print


/*! \ingroup print
 * Print a value to an Input / output object.
 *
 * \param io Input / output object.
 * \param data Data.
 */
template <class T>
void rpcPrint(Stream& io, T data) {
  io.write((uint8_t*)&data, sizeof(T));
}


/*! \ingroup print
 * \copydoc rpcPrint(Stream&, T) */
inline void rpcPrint(Stream& io, char* data) {
  size_t i = 0;

  while (data[i]) {
    rpcPrint(io, data[i]);
    i++;
  }
}

/*! \ingroup print
 * \copydoc rpcPrint(Stream&, T) */
inline void rpcPrint(Stream& io, char const* data) {
  rpcPrint(io, (char*)data);
}

/*! \ingroup print
 * \copydoc rpcPrint(Stream&, T) */
inline void rpcPrint(Stream& io, String& data) {
  rpcPrint(io, data.c_str());
}

/*! \ingroup print
 * \copydoc rpcPrint(Stream&, T) */
inline void rpcPrint(Stream& io, __FlashStringHelper const* data) {
  char const* p = (char const*)data;
  uint8_t c = pgm_read_byte(p);

  while (c) {
    rpcPrint(io, c);
    p++;
    c = pgm_read_byte(p);
  }
}


/*! \ingroup print
 * Print any number of values.
 *
 * \param io Stream / output object.
 * \param data Value to be printed.
 * \param args Remaining values.
 */
template <class H, class... Tail>
void rpcPrint(Stream& io, H data, Tail... args) {
  rpcPrint(io, data);
  rpcPrint(io, args...);
}

#endif
