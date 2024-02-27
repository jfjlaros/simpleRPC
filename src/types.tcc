#pragma once

#include "rpcPrint.tcc"
#include "atomic_types.tcc"
#include "tuple.tcc"
#include "array.tcc"
#include "rolling_buffer.tcc"
#include "PString.h"
#include "TString.tcc"

//! \defgroup types

template<class T>
struct RPCType
{
  static void print(Stream& io)
  {
    rpcPrint(io, RpcAtomicType<T>::getType());
  }
};

template<class T, size_t S>
struct RPCType<RollingBuffer<T,S>>
{
  static void print(Stream& io)
  {
    if(RpcAtomicTypeHelper<T>::isAtomicType()){
      rpcPrint(io, "{");
      RPCType<T>::print(io);
      rpcPrint(io, "}");
    } else {
      rpcPrint(io, "[");
      RPCType<T>::print(io);
      rpcPrint(io, "]");
    }
  }
};

template<class T, size_t S>
struct RPCType<RollingBuffer<T,S>&>
{
  static void print(Stream& io)
  {
    if(RpcAtomicTypeHelper<T>::isAtomicType()){
      rpcPrint(io, "{");
      RPCType<T>::print(io);
      rpcPrint(io, "}");
    } else {
      rpcPrint(io, "[");
      RPCType<T>::print(io);
      rpcPrint(io, "]");
    }
  }
};

template<class T, size_t S>
struct RPCType<Array<T,S>>
{
  static void print(Stream& io)
  {
    if(RpcAtomicTypeHelper<T>::isAtomicType()){
      rpcPrint(io, "{");
      RPCType<T>::print(io);
      rpcPrint(io, "}");
    } else {
      rpcPrint(io, "[");
      RPCType<T>::print(io);
      rpcPrint(io, "]");
    }
  }
};

template<class T>
struct RPCType<Vector<T>>
{
  static void print(Stream& io)
  {
    if(RpcAtomicTypeHelper<T>::isAtomicType()){
      rpcPrint(io, "{");
      RPCType<T>::print(io);
      rpcPrint(io, "}");
    } else {
      rpcPrint(io, "[");
      RPCType<T>::print(io);
      rpcPrint(io, "]");
    }
  }
};

template<class T>
struct RPCType<T*>
{
  static void print(Stream& io)
  {
    if(RpcAtomicTypeHelper<T>::isAtomicType()){
      rpcPrint(io, "{");
      RPCType<T>::print(io);
      rpcPrint(io, "}");
    } else {
      rpcPrint(io, "[");
      RPCType<T>::print(io);
      rpcPrint(io, "]");
    }
  }
};

template<class H>
struct RPCType<_Tuple<H>>
{
  static void print(Stream& io)
  {
    RPCType<H>::print(io);
  }
};

template<class H, class... Membs>
struct RPCType<_Tuple<H, Membs...>>
{
  static void print(Stream& io)
  {
    RPCType<H>::print(io);
    RPCType<_Tuple<Membs...>>::print(io);
  }
};

template<class... Membs>
struct RPCType<Tuple<Membs...>>
{
  static void print(Stream& io)
  {
    rpcPrint(io, '(');
    RPCType<_Tuple<Membs...>>::print(io);
    rpcPrint(io, ')');
  }
};








/*! \ingroup types
 * Determine endianness and type of `size_t`.
 *
 * \param io Input / output object.
 */
inline void hardwareDefs(Stream& io)
{
  size_t i = 0xff;

  if (((uint8_t*)&i)[0] == 0xff)
  {
    rpcPrint(io, "<");
  }
  else
  {
    rpcPrint(io, ">");
  }

  RPCType<size_t>::print(io);
  rpcPrint(io, '\0');
}