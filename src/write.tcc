#pragma once

#include "rpcPrint.tcc"
#include "tuple.tcc"
#include "vector.tcc"
#include "array.tcc"
#include "TString.tcc"
#include "PString.h"
#include "rolling_buffer.tcc"

//! \defgroup write


/*! \ingroup write
 * Write a value to an Input / output object.
 *
 * \param io Input / output object.
 * \param data Data.
 */
template <class T>
void rpcWrite(Stream& io, T* data) {
  io.write((uint8_t*)data, sizeof(T));
}


/*! \ingroup write
 * \copydoc rpcWrite(Stream&, T*) */
inline void rpcWrite(Stream& io, char** data) {
  rpcPrint(io, *data, '\0');
}

/*! \ingroup write
 * \copydoc rpcWrite(Stream&, T*) */
inline void rpcWrite(Stream& io, char const** data) {
  rpcWrite(io, (char**)data);
}

/*! \ingroup write
 * \copydoc rpcWrite(Stream&, T*) */
inline void rpcWrite(Stream& io, String* data) {
  rpcPrint(io, *data, '\0');
}

/*! \ingroup write
 * \copydoc rpcWrite(Stream&, T*) */
inline void rpcWrite(Stream& io, PString* data)
{
  const char* str = *data;
  rpcPrint(io, str);
}

/*! \ingroup write
 * \copydoc rpcWrite(Stream&, T*) */
template<size_t S>
inline void rpcWrite(Stream& io, TString<S>* data)
{
  const char* str = *data;
  rpcPrint(io, str);
}

/*! \ingroup write
 * \copydoc rpcWrite(Stream&, T*) */
template <class T, size_t S>
void rpcWrite(Stream& io, Array<T, S>* data) {
  
  rpcWrite(io, &data->size);
  for (size_t i = 0; i < data->size; i++)
  {
    rpcWrite(io, &(*data)[i]);
  }
}

/*! \ingroup write
 * \copydoc rpcWrite(Stream&, T*) */
template <class T, size_t S>
void rpcWrite(Stream& io, Vector<T>* data) {
  
  rpcWrite(io, &data->size);
  for (size_t i = 0; i < data->size; i++)
  {
    rpcWrite(io, &(*data)[i]);
  }
}

/*! \ingroup write
 * \copydoc rpcWrite(Stream&, T*) */
template <class T, size_t S>
void rpcWrite(Stream& io, RollingBuffer<T, S>* data)
{
  size_t size = data->begin_read();
  rpcWrite(io, &size);
  for (size_t i = 0; i < size; i++)
  {
    rpcWrite(io, (T*)data->pop());
  }
  data->end_read();
}

//! Recursion terminator for `rpcWrite(_Tuple*)()`.
inline void rpcWrite(Stream&, _Tuple<>*) {}

/*! \ingroup write
 * \copydoc rpcWrite(Stream&, T*) */
template <class... Membs>
void rpcWrite(Stream& io, _Tuple<Membs...>* data) {
  rpcWrite(io, &(*data).head);
  rpcWrite(io, &(*data).tail);
}


/*! \ingroup write
 * \copydoc rpcWrite(Stream&, T*) */
template <class... Membs>
void rpcWrite(Stream& io, Tuple<Membs...>* data)
{
  rpcWrite(io, (_Tuple<Membs...>*)data);
}
