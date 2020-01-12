#ifndef SIMPLE_RPC_PRINT_TCC_
#define SIMPLE_RPC_PRINT_TCC_

#include "defs.h"


template <class I, class T>
void rpcPrint(I& io, T data) {
  io.write((byte*)&data, sizeof(T));
}

template <class I>
void rpcPrint(I& io, const char* data) {
  size_t i = 0;

  while (data[i] != _END_OF_STRING) {
    rpcPrint(io, data[i]);
    i++;
  }
}

template <class I>
void rpcPrint(I& io, String& data) {
  rpcPrint(io, data.c_str());
}

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

template <class I, class H, class... Tail>
void rpcPrint(I& io, H data, Tail... tail) {
  rpcPrint(io, data);
  rpcPrint(io, tail...);
}

#endif
