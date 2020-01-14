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
#include "plugins/ethernet/io.h"
#include "plugins/hardwareserial/io.h"
#include "plugins/softwareserial/io.h"
#include "plugins/wire/io.h"


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
  rpcInterface(io, args...);
}

/**
 * Recursion terminator for @a interface().
 *
 * @private
 */
template <class... Args>
void interface(Tuple<>, Args...) {}

/**
 * Multiple RPC interfaces.
 *
 * @param t Tuple of input / output objects.
 * @param args Parameter pairs (function pointer, documentation).
 */
template <class H, class... Tail, class... Args>
void interface(Tuple<H, Tail...> t, Args... args) {
  rpcInterface(*t.head, args...);
  interface(t.tail, args...);
}

#endif
