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


/*
 * The following three template functions are requires because the template
 * function in this comment causes an ambiguity. The same overloading seems to
 * work for the setup template function {call} though.
 *
 * See the {call} function family for documentation.
 *
template<class... Args>
void call(void (*f_)(void), void (*f)(Args...), Args... args) {
  f(args...);
}
 */

template<class... Args>
void call_void(void (*f_)(void), void (*f)(Args...), Args... args) {
  f(args...);
}

template<class T, class... Tail, class F, class... Args>
void call_void(void (*f_)(T, Tail...), F f, Args... args) {
  T data;

  Serial.readBytes((char *)&data, sizeof(T));
  call_void((void (*)(Tail...))f_, f, args..., data);
}

template<class... Args>
void call(void (*f)(Args...)) {
  call_void(f, f);
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
 */
template<class T, class... Args>
void call(void (*f_)(void), T (*f)(Args...), Args... args) {
  T data = f(args...);

  Serial.write((byte *)&data, sizeof(T));
}

/**
 * Collect parameters of a function from serial.
 *
 * We isolate the first parameter type {T} from function pointer {*f_}. This
 * type is used to instantiate the variable {data}, which is used to receive
 * {sizeof(T)} bytes from the serial stream. This value is passed recursively
 * to {call}, adding it to the {args} parameter pack. The first parameter type
 * {T} is removed from function pointer {*f_} in the recursive call.
 */
template<class T, class... Tail, class F, class... Args>
void call(void (*f_)(T, Tail...), F f, Args... args) {
  T data;

  Serial.readBytes((char *)&data, sizeof(T));
  call((void (*)(Tail...))f_, f, args..., data);
}

/**
 * Set up function parameter collection, execution and writing to serial.
 *
 * We prepare a dummy function pointer, referred to as {f_} in the template
 * functions above, which will be used to isolate parameter types. The return
 * type of this function pointer is removed to avoid unneeded template
 * expansion.
 */
template<class R, class... Args>
void call(R (*f)(Args...)) {
  call((void (*)(Args...))f, f);
}


template<class F>
void writeDescription(F f, const char *description) {
  Serial.print("[");
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
  byte command;
  
  if (Serial.available()) {
    command = Serial.read();

    if (command == 0xff) {
      describe(args...);
      Serial.println(); // List terminator.
      return;
    }
    select(command, 0, args...);
  }
}

#endif
