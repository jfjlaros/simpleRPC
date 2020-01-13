#ifndef SIMPLE_RPC_H_
#define SIMPLE_RPC_H_

/**
 * @file simpleRPC.h
 *
 * RPC interface.
 */

#include "defs.h"
#include "interface.tcc"

// IO plugins.
#include "plugins/hardwareserial/io.h"
#include "plugins/softwareserial/io.h"
#include "plugins/wire/io.h"


/// @private
inline byte _ping(byte data) {
  return data;
}


/**
 * RPC interface.
 *
 * This function expects parameter pairs (function pointer, documentation).
 *
 * @param io Input / output object.
 * @param args Parameter pairs (function pointer, documentation).
 */
template <class I, class... Args>
void interface(I& io, Args... args) {
  rpcInterface(
    io,
    _ping, F("ping: Echo a value. @data: Value. @return: Value of data."),
    args...);
}

#endif
