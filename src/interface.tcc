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

#include "serial/io.h"

#include "print.tcc"
#include "rpcCall.tcc"
#include "signature.tcc"


/**
 * Write the signature and documentation of a function to serial.
 *
 * @param f Function pointer.
 * @param doc Function documentation.
 *
 * @private
 */
template <class F, class D>
void _writeDescription(F f, D doc) {
  //multiPrint(signature(f).c_str(), ";", doc, _END_OF_STRING);
  xrite(signature(f).c_str(), ";", doc, _END_OF_STRING);
}


/**
 * Recursion terminator for @a _describe().
 *
 * @private
 */
inline void _describe(void) {}

/**
 * Describe a list of functions.
 *
 * We isolate the first two parameters @a f and @a doc, pass these to
 * @a _writeDescription() and make a recursive call to process the remaining
 * parameters.
 *
 * @param f Function pointer.
 * @param doc Function documentation.
 * @param args Remaining parameters.
 *
 * @private
 */
template <class F, class D, class... Args>
void _describe(F f, D doc, Args... args) {
  _writeDescription(f, doc);
  _describe(args...);
}

/**
 * Class member function.
 *
 * @private
 */
template <class U, class V, class D, class... Args>
void _describe(Tuple<U, V> t, D doc, Args... args) {
  _writeDescription(t.tail.head, doc);
  _describe(args...);
}


/**
 * Recursion terminator for @a _select().
 *
 * @private
 */
inline void _select(byte, byte) {}

/**
 * Select and call a function indexed by @a number.
 *
 * We isolate the parameter @a f and its documentation string, discarding the
 * latter. If we have arrived at the selected function (i.e., if @a depth
 * equals @a number), we call function @a f. Otherwise, we try again
 * recursively.
 *
 * @param number Function index.
 * @param depth Current index.
 * @param f Function pointer.
 * @param - Function documentation.
 * @param args Remaining parameters.
 *
 * @private
 */
template <class F, class D, class... Args>
void _select(byte number, byte depth, F f, D, Args... args) {
  if (depth == number) {
    rpcCall(f);
    return;
  }
  _select(number, depth + 1, args...);
}


/**
 * RPC interface.
 *
 * This function expects parameter pairs (function pointer, documentation).
 *
 * One byte is read from serial into @a command, if the value equals
 * @a _LIST_REQ, we describe the list of functions. Otherwise, we call the
 * function indexed by @a command.
 *
 * @param args Parameter pairs (function pointer, documentation).
 */
template <class... Args>
void rpcInterface(Args... args) {
  byte command;

  if (Serial.available()) {
    command = Serial.read();

    if (command == _LIST_REQ) {
      xrite(_PROTOCOL, _END_OF_STRING);
      xrite(_VERSION[0], _VERSION[1], _VERSION[2]);
      xrite(_hardwareDefs(), _END_OF_STRING);
      _describe(args...);
      xrite(_END_OF_STRING);

      //multiPrint(_PROTOCOL, _END_OF_STRING);
      //multiPrint(_VERSION[0], _VERSION[1], _VERSION[2]);
      //multiPrint(_hardwareDefs().c_str(), _END_OF_STRING);
      //_describe(args...);
      //multiPrint(_END_OF_STRING); // Empty string marks end of list.
      return;
    }
    _select(command, 0, args...);
  }
}

#endif
