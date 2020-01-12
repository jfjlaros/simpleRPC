#ifndef SIMPLE_RPC_INTERFACE_TCC_
#define SIMPLE_RPC_INTERFACE_TCC_

/**
 * @file interface.tcc
 *
 * Template library for exporting native C and C++ functions as remote
 * procedure calls.
 *
 * For more information about (variadic) templates:
 * @li http://www.drdobbs.com/cpp/extracting-function-parameter-and-return/240000586
 * @li https://eli.thegreenplace.net/2014/variadic-templates-in-c/
 * @li https://en.cppreference.com/w/cpp/language/parameter_pack
 */

#include "rpcCall.tcc"
#include "signature.tcc"


/**
 * Write the signature and documentation of a function.
 *
 * @param io Input / output object.
 * @param f Function pointer.
 * @param doc Function documentation.
 *
 * @private
 */
template <class I, class F, class D>
void _writeDescription(I& io, F f, D doc) {
  rpcPrint(io, signature(f), ';', doc, _END_OF_STRING);
}


/**
 * Recursion terminator for @a _describe().
 *
 * @private
 */
template <class I>
void _describe(I&) {}

/**
 * Describe a list of functions.
 *
 * We isolate the first two parameters @a f and @a doc, pass these to
 * @a _writeDescription() and make a recursive call to process the remaining
 * parameters.
 *
 * @param io Input / output object.
 * @param f Function pointer.
 * @param doc Function documentation.
 * @param args Remaining parameters.
 *
 * @private
 */
template <class I, class F, class D, class... Args>
void _describe(I& io, F f, D doc, Args... args) {
  _writeDescription(io, f, doc);
  _describe(io, args...);
}

/**
 * Class member function.
 *
 * @private
 */
template <class I, class U, class V, class D, class... Args>
void _describe(I& io, Tuple<U, V> t, D doc, Args... args) {
  _writeDescription(io, t.tail.head, doc);
  _describe(io, args...);
}


/**
 * Recursion terminator for @a _select().
 *
 * @private
 */
template <class I>
void _select(I&, byte, byte) {}

/**
 * Select and call a function indexed by @a number.
 *
 * We isolate the parameter @a f and its documentation string, discarding the
 * latter. If we have arrived at the selected function (i.e., if @a depth
 * equals @a number), we call function @a f. Otherwise, we try again
 * recursively.
 *
 * @param io Input / output object.
 * @param number Function index.
 * @param depth Current index.
 * @param f Function pointer.
 * @param - Function documentation.
 * @param args Remaining parameters.
 *
 * @private
 */
template <class I, class F, class D, class... Args>
void _select(I& io, byte number, byte depth, F f, D, Args... args) {
  if (depth == number) {
    rpcCall(io, f);
    return;
  }
  _select(io, number, depth + 1, args...);
}


/**
 * RPC interface.
 *
 * This function expects parameter pairs (function pointer, documentation).
 *
 * One byte is read into @a command, if the value equals @a _LIST_REQ, we
 * describe the list of functions. Otherwise, we call the function indexed by
 * @a command.
 *
 * @param io Input / output object.
 * @param args Parameter pairs (function pointer, documentation).
 */
template <class I, class... Args>
void rpcInterface(I& io, Args... args) {
  byte command;

  if (io.available()) {
    rpcRead(io, &command);

    if (command == _LIST_REQ) {
      rpcPrint(io, _PROTOCOL, _END_OF_STRING);
      rpcPrint(io, _VERSION[0], _VERSION[1], _VERSION[2]);
      rpcPrint(io, _hardwareDefs(), _END_OF_STRING);
      _describe(io, args...);
      rpcPrint(io, _END_OF_STRING);
      return;
    }
    _select(io, command, 0, args...);
  }
}

#endif
