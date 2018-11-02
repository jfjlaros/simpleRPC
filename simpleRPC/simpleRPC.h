#ifndef __SIMPLE_RPC_H__
#define __SIMPLE_RPC_H__
/*
 * Inspiration from:
 *
 * http://www.drdobbs.com/cpp/extracting-function-parameter-and-return/240000586
 * https://eli.thegreenplace.net/2014/variadic-templates-in-c/
 * https://en.cppreference.com/w/cpp/language/parameter_pack
 */

#include <Arduino.h>


/**
 * Execute a function and write return value to serial.
 *
 * All parameters have been parsed since function pointer {*f_} has no
 * parameter types. Function pointer {*f} now equals the original function
 * pointer and all values are now present in the {args} parameter pack.
 *
 * We use the return type {R} of function pointer {*f} to instantiate the
 * variable {data}, which receives the result of {f(args...}. This result is
 * written in {sizeof(R)} bytes to the serial stream.
 */
template<class R, class... Args>
void call(void (*f_)(void), R (*f)(Args...), Args... args) {
  R data = f(args...);

  Serial.write((byte *)&data, sizeof(R));
}

/**
 * Collect parameters of a function from serial.
 *
 * We isolate the first parameter type {T} from function pointer {*f_}. This
 * type is used to instantiate the variable {data}, which is used to receive
 * {sizeof(T)} bytes from the serial stream. This value is passed recursively
 * to {call}, adding it to the {args} parameter pack.
 *
 * The first parameter type {T} is removed from function pointer {*f_} and
 * added to function pointer {*f}.
 */
template<class R, class T, class... Tail, class... Args, class... LArgs>
void call(void (*f_)(T, Tail...), R (*f)(Args...), LArgs... args) {
  // TODO: Try to get rid of building parameters for {f}.
  T data;

  Serial.readBytes((char *)&data, sizeof(T));
  call((void (*)(Tail...))f_, (R (*)(T, Args...))f, data, args...);
}

/**
 * 
 */
template<class R, class... Args>
void call(R (*f)(Args...)) {
  call((void (*)(Args...))f, (R (*)(void))f);
}


template<class F>
void writeDescription(F f, const char *description) {
  Serial.print(&__PRETTY_FUNCTION__[48]);
  Serial.print(" ");
  Serial.println(description);
}


void describe(void) {}

template<class F, class... Args>
void describe(F f, const char *description, Args... args) {
  writeDescription(f, description);
  describe(args...);
}


void select(byte number, byte depth) {}

template<class F, class... Args>
void select(byte number, byte depth, F f, const char *description, Args... args) {
  if (depth == number) {
    call(f);
    return;
  }
  select(number, depth + 1, args...);
}


template<class... Args>
void interface(Args... args) {
  byte command = Serial.read();

  if (command == 0xff) {
    describe(args...);
    return;
  }
  select(command, 0, args...);
}

#endif
