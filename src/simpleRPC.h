#ifndef __SIMPLE_RPC_H__
#define __SIMPLE_RPC_H__

#include "defs.h"
#include "interface.tcc"


String _version(void) {
  return _VERSION;
}

byte _ping(byte data) {
  return data;
}


/**
 * RPC interface.
 *
 * This function expects parameter pairs (function pointer, documentation).
 *
 * @arg {Args...} args - Parameter pairs (function pointer, documentation).
 */
template<class... Args>
void interface(Args... args) {
  rpcInterface(
    _version, F("version: Protocol version. @return: Version string."),
    _ping, F("ping: Echo a value. @data: Value. @return: Value of data."),
    args...);
}

#endif
