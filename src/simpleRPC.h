#ifndef SIMPLE_RPC_H_
#define SIMPLE_RPC_H_

/**
 * @file simpleRPC.h
 *
 * RPC interface.
 */

#include "defs.h"
#include "interface.tcc"


/// @private
byte _ping(byte data) {
  return data;
}


/**
 * RPC interface.
 *
 * This function expects parameter pairs (function pointer, documentation).
 *
 * @param args Parameter pairs (function pointer, documentation).
 */
template <class... Args>
void interface(Args... args) {
  rpcInterface(
    _ping, F("ping: Echo a value. @data: Value. @return: Value of data."),
    args...);
}

#endif
