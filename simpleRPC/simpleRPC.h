#ifndef __SIMPLE_RPC_H__
#define __SIMPLE_RPC_H__

#include "interface.tcc"

#define _VERSION "2.0.1"


char *_version(void) {
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
    _version, "version: Protocol version. @return: Version number.",
    _ping, "ping: Echo a value. @data: Value. @return: Value of data.",
    args...);
}

#endif
