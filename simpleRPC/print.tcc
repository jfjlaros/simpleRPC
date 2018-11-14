#ifndef __SIMPLE_RPC_PRINT_TCC__
#define __SIMPLE_RPC_PRINT_TCC__

#include <Arduino.h>

#define _END_OF_STRING '\0'


/**
 * Recursion terminator for {_print}.
 */
void _print(void) {}

/**
 * Print a list of parameters to serial.
 *
 * @arg {T} arg - Parameter to be printed.
 * @arg {Args...} args... - Remaining parameters.
 */
template<class T, class... Args>
void _print(T arg, Args... args) {
  Serial.write(arg);
  _print(args...);
}

#endif
