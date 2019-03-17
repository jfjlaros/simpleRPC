#ifndef __SIMPLE_RPC_INTERFACE_TCC__
#define __SIMPLE_RPC_INTERFACE_TCC__

/*
 * Template library for exporting native C functions as remote procedure calls.
 *
 * For more information about (variadic) templates:
 * http://www.drdobbs.com/cpp/extracting-function-parameter-and-return/240000586
 * https://eli.thegreenplace.net/2014/variadic-templates-in-c/
 * https://en.cppreference.com/w/cpp/language/parameter_pack
 *
 * TODO: Add support for multiple serial devices.
 */
#include "rpcCall.tcc"
#include "signature.tcc"

#define _LIST_REQ (byte)0xff


/**
 * Write the signature and documentation of a function to serial.
 *
 * @arg {F} f - Function pointer.
 * @arg {D} doc - Function documentation.
 */
template<class F, class D>
void _writeDescription(F f, D doc) {
  multiPrint(signature(f).c_str(), ";", doc, _END_OF_STRING);
}


/**
 * Recursion terminator for {_describe()}.
 */
inline void _describe(void) {}

/**
 * Describe a list of functions.
 *
 * We isolate the first two parameters {f} and {doc}, pass these to
 * {_writeDescription} and make a recursive call to process the remaining
 * parameters.
 *
 * @arg {F} f - Function pointer.
 * @arg {D} doc - Function documentation.
 * @arg {Args...} args - Remaining parameters.
 */
template<class F, class D, class... Args>
void _describe(F f, D doc, Args... args) {
  _writeDescription(f, doc);
  _describe(args...);
}

// Class member function.
template<class U, class V, class D, class... Args>
void _describe(Tuple <U, V>t, D doc, Args... args) {
  _writeDescription(t.tail.head, doc);
  _describe(args...);
}


/**
 * Recursion terminator for {_select()}.
 */
inline void _select(byte, byte) {}

/**
 * Select and call a function indexed by {number}.
 *
 * We isolate the parameter {f} and its documentation string, discarding the
 * latter. If we have arrived at the selected function (i.e., if {depth} equals
 * {number}), we call function {f}. Otherwise, we try again recursively.
 *
 * @arg {byte} number - Function index.
 * @arg {byte} depth - Current index.
 * @arg {F} f - Function pointer.
 * @arg {D} - Function documentation.
 * @arg {Args...} args - Remaining parameters.
 */
template<class F, class D, class... Args>
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
 * One byte is read from serial into {command}, if the value is {_LIST_REQ}, we
 * describe the list of functions. Otherwise, we call the function indexed by
 * {command}.
 *
 * @arg {Args...} args - Parameter pairs (function pointer, documentation).
 */
template<class... Args>
void rpcInterface(Args... args) {
  byte command;

  if (Serial.available()) {
    command = Serial.read();

    if (command == _LIST_REQ) {
      // TODO: Use _hardwareDefs and remove all '<' from types.tcc.
      //multiPrint(_hardwareDefs());
      _describe(args...);
      multiPrint(_END_OF_STRING); // Empty string marks end of list.
      return;
    }
    _select(command, 0, args...);
  }
}

#endif
