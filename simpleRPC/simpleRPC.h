#ifndef __SIMPLE_RPC_H__
#define __SIMPLE_RPC_H__

/*
 * Template library for exporting native C functions as remote procedure calls.
 *
 * For more information about (variadic) templates:
 * http://www.drdobbs.com/cpp/extracting-function-parameter-and-return/240000586
 * https://eli.thegreenplace.net/2014/variadic-templates-in-c/
 * https://en.cppreference.com/w/cpp/language/parameter_pack
 *
 * NOTE: We use the __PRETTY_FUNCTION__ macro, we could do without at the
 * expense of defining a lot of functions (one per native type).
 *
 * NOTE: We currently rely on the client knowing the native types and type
 * sizes. We could also communicate the latter to the client.
 *
 * TODO: Add protocol version.
 */

#include <Arduino.h>

#define _LIST_REQ 0xff


/*
 * The following three template functions are requires because the template
 * function in this comment causes an ambiguity. The same overloading seems to
 * work for the setup template function {_call} though.
 *
 * See the {_call} function family for documentation.
 *
template<class... Args>
void _call(void (*f_)(void), void (*f)(Args...), Args... args) {
  f(args...);
}
 */

template<class... Args>
void _call_void(void (*f_)(void), void (*f)(Args...), Args... args) {
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
 * @arg {void (*)(void)} f_ - Dummy function pointer.
 * @arg {T (*)(Args...)} f - Function pointer.
 * @arg {Args...} args... - Parameter pack for {f}.
 */
template<class T, class... Args>
void _call(void (*f_)(void), T (*f)(Args...), Args... args) {
  T data = f(args...);

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
 * Write the signature and description of a function to serial.
 *
 * @arg {F} f - Function pointer.
 * @arg {const char *} description - Function description.
 */
template<class F>
void _writeDescription(F f, const char *description) {
  Serial.print("[");
  Serial.print(&__PRETTY_FUNCTION__[48]);
  Serial.print(" ");
  Serial.println(description);
}


/**
 * Recursion terminator for {_describe}.
 */
void _describe(void) {}

/**
 * Describe a list of functions.
 *
 * We isolate the first two parameters {f} and {description}, pass these to
 * {__writeDescription} and make a recursive call to process the remaining
 * parameters.
 *
 * @arg {F} f - Function pointer.
 * @arg {const char *} description - Function description.
 * @arg {Args...} args - Remaining parameters.
 */
template<class F, class... Args>
void _describe(F f, const char *description, Args... args) {
  _writeDescription(f, description);
  _describe(args...);
}


/**
 * Recursion terminator for {_select}.
 */
void _select(byte number, byte depth) {}

/**
 * Select and call a function indexed by {number}.
 *
 * We isolate the first two parameters {f} and {description}. If we have
 * arrived at the selected function (i.e., if {depth} equals {number}, we call
 * function {f}. Otherwise, we make a recursive call, discarding {f} and
 * {description}.
 *
 * @arg {byte} number - Function index.
 * @arg {byte} depth - Current index.
 * @arg {F} f - Function pointer.
 * @arg {const char *} description - Function description.
 * @arg {Args...} args - Remaining parameters.
 */
template<class F, class... Args>
void _select(
    byte number, byte depth, F f, const char *description, Args... args) {
  if (depth == number) {
    _call(f);
    return;
  }
  _select(number, depth + 1, args...);
}


/**
 * RPC interface.
 *
 * This function expects a list of tuples (function pointer, description) as
 * parameters.
 *
 * Read one byte from serial into {command}, if the value is {_LIST_REQ}, we
 * describe the list of functions. Otherwise, we call the function indexed by
 * {command}.
 *
 * @arg {Args...} args - Tuples of (function pointer, description) parameters.
 */
template<class... Args>
void interface(Args... args) {
  byte command;

  if (Serial.available()) {
    command = Serial.read();

    if (command == _LIST_REQ) {
      _describe(args...);
      Serial.println(); // List terminator.
      return;
    }
    _select(command, 0, args...);
  }
}

#endif
