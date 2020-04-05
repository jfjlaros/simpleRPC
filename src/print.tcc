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
template <class I, class T>
void rpcPrint(I& io, T data) {
  io.write((byte*)&data, sizeof(T));
}


/*! \ingroup print
 * \copydoc rpcPrint(I&, T) */
template <class I>
void rpcPrint(I& io, char* data) {
  size_t i = 0;

  while (data[i] != _END_OF_STRING) {
    rpcPrint(io, data[i]);
    i++;
  }
}

/*! \ingroup print
 * \copydoc rpcPrint(I&, T) */
template <class I>
void rpcPrint(I& io, const char* data) {
  rpcPrint(io, (char*)data);
}

/*! \ingroup print
 * \copydoc rpcPrint(I&, T) */
template <class I>
void rpcPrint(I& io, String& data) {
  rpcPrint(io, data.c_str());
}

/*! \ingroup print
 * \copydoc rpcPrint(I&, T) */
template <class I>
void rpcPrint(I& io, const __FlashStringHelper* data) {
  const char* p = (const char*)data;
  byte c = pgm_read_byte(p);

  while (c) {
    rpcPrint(io, c);
    p++;
    c = pgm_read_byte(p);
  }
}


/*! \ingroup print
 * Print any number of values.
 *
 * \param io Input / output object.
 * \param data Value to be printed.
 * \param args Remaining values.
 */
template <class I, class H, class... Tail>
void rpcPrint(I& io, H data, Tail... args) {
  rpcPrint(io, data);
  rpcPrint(io, args...);
}

#endif
