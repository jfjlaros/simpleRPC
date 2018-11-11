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
 * TODO: Use a namespace if possible.
 * TODO: Add support for multiple serial devices.
 * TODO: Add support for lists / strings.
 * TODO: Add support for structs.
 */
#include <Arduino.h>

#include "print.tcc"
#include "typeof.tcc"

#define _LIST_REQ 0xff
#define _END_OF_STRING '\0'


/*
 * The following three template functions are required because the template
 * function in this comment causes an ambiguity. The same overloading seems to
 * work for the setup template function {_call} though.
 *
 * See the {_call} function family for documentation.
 *
template<class... Args>
void _call(void (*)(void), void (*f)(Args...), Args... args) {
  f(args...);
}
 */

template<class... Args>
void _call_void(void (*)(void), void (*f)(Args...), Args... args) {
  f(args...);
}

template<class T, class... Tail, class F, class... Args>
void _call_void(void (*f_)(T, Tail...), F f, Args... args) {
  T data;

  Serial.readBytes((char *)&data, sizeof(T));
  _call_void((void (*)(Tail...))f_, f, args..., data);
}

template<class... Args>
void _call(void (*f)(Args...)) {
  _call_void(f, f);
}

/**
 * Execute a function and write return value to serial.
 *
 * All parameters have been collected since function pointer {*f_} has no
 * parameter types. All values are now present in the {args} parameter pack.
 *
 * We use the return type {T} of function pointer {*f} to instantiate the
 * variable {data}, which receives the result of {f(args...}. This result is
 * written in {sizeof(T)} bytes to the serial stream.
 *
 * @arg {void (*)(void)} - Dummy function pointer.
 * @arg {T (*)(Args...)} f - Function pointer.
 * @arg {Args...} args... - Parameter pack for {f}.
 */
template<class T, class... Args>
void _call(void (*)(void), T (*f)(Args...), Args... args) {
  T data = f(args...);

  if (_typeof(data) == "s") {
    _print(data, _END_OF_STRING);
    return;
  }
  Serial.write((byte *)&data, sizeof(T));
}

/**
 * Collect parameters of a function from serial.
 *
 * We isolate the first parameter type {T} from function pointer {*f_}. This
 * type is used to instantiate the variable {data}, which is used to receive
 * {sizeof(T)} bytes from the serial stream. This value is passed recursively
 * to {_call}, adding it to the {args} parameter pack. The first parameter type
 * {T} is removed from function pointer {*f_} in the recursive call.
 *
 * @arg {void (*)(T, Tail...)} f_ - Dummy function pointer.
 * @arg {F} f - Function pointer.
 * @arg {Args...} args... - Parameter pack for {f}.
 */
template<class T, class... Tail, class F, class... Args>
void _call(void (*f_)(T, Tail...), F f, Args... args) {
  T data;

  Serial.readBytes((char *)&data, sizeof(T));
  _call((void (*)(Tail...))f_, f, args..., data);
}

/*
 * Parameter collection for strings.
 */
template<class... Tail, class F, class... Args>
void _call(void (*f_)(char *, Tail...), F f, Args... args) {
  _call(
    (void (*)(Tail...))f_, f, args...,
    (char *)Serial.readStringUntil(_END_OF_STRING).c_str());
}

template<class... Tail, class F, class... Args>
void _call(void (*f_)(const char *, Tail...), F f, Args... args) {
  _call(
    (void (*)(Tail...))f_, f, args...,
    (const char *)Serial.readStringUntil(_END_OF_STRING).c_str());
}

/**
 * Set up function parameter collection, execution and writing to serial.
 *
 * We prepare a dummy function pointer, referred to as {f_} in the template
 * functions above, which will be used to isolate parameter types. The return
 * type of this function pointer is removed to avoid unneeded template
 * expansion.
 *
 * @arg {T (*)(Args...)} f - Function pointer.
 */
template<class T, class... Args>
void _call(T (*f)(Args...)) {
  _call((void (*)(Args...))f, f);
}


/**
 * Write the signature and documentation of a function to serial.
 *
 * @arg {F} f - Function pointer.
 * @arg {const char *} doc - Function documentation.
 */
template<class F>
void _writeDescription(F f, const char *doc) {
  describeSignature(f);
  _print(";", doc, _END_OF_STRING);
}


/**
 * Recursion terminator for {_describe}.
 */
void _describe(void) {}

/**
 * Describe a list of functions.
 *
 * We isolate the first two parameters {f} and {doc}, pass these to
 * {__writeDescription} and make a recursive call to process the remaining
 * parameters.
 *
 * @arg {F} f - Function pointer.
 * @arg {const char *} doc - Function documentation.
 * @arg {Args...} args - Remaining parameters.
 */
template<class F, class... Args>
void _describe(F f, const char *doc, Args... args) {
  _writeDescription(f, doc);
  _describe(args...);
}


/**
 * Recursion terminator for {_select}.
 */
void _select(byte, byte) {}

/**
 * Select and call a function indexed by {number}.
 *
 * We isolate the parameter {f} and its documentation string, discarding the
 * latter. If we have arrived at the selected function (i.e., if {depth} equals
 * {number}, we call function {f}. Otherwise, we try again recursively.
 *
 * @arg {byte} number - Function index.
 * @arg {byte} depth - Current index.
 * @arg {F} f - Function pointer.
 * @arg {const char *} - Function documentation.
 * @arg {Args...} args - Remaining parameters.
 */
template<class F, class... Args>
void _select(byte number, byte depth, F f, const char *, Args... args) {
  if (depth == number) {
    _call(f);
    return;
  }
  _select(number, depth + 1, args...);
}


/**
 * RPC interface.
 *
 * This function expects a list of tuples (function pointer, documentation) as
 * parameters.
 *
 * Read one byte from serial into {command}, if the value is {_LIST_REQ}, we
 * describe the list of functions. Otherwise, we call the function indexed by
 * {command}.
 *
 * @arg {Args...} args - Tuples of (function pointer, documentation).
 */
template<class... Args>
void _interface(Args... args) {
  byte command;

  if (Serial.available()) {
    command = Serial.read();

    if (command == _LIST_REQ) {
      _describe(args...);
      _print(_END_OF_STRING); // Empty string marks end of list.
      return;
    }
    _select(command, 0, args...);
  }
}

#endif
