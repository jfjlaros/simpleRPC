#ifndef __SIMPLE_RPC_H__
#define __SIMPLE_RPC_H__

#include "interface.tcc"

#define _VERSION 2


byte _version(void) {
  return _VERSION;
}

byte _ping(byte data) {
  return data;
}


/**
 * RPC interface.
 *
 * This function expects a list of tuples (function pointer, documentation) as
 * parameters.
 *
 * @arg {Args...} args - Tuples of (function pointer, documentation).
 */
template<class... Args>
void interface(Args... args) {
  _interface(
    _version, "version: Protocol version. @R:Version number.",
    _ping, "ping: Receive a value and echo it back. @P:Value. @R:Value.",
    args...);
}

#endif
