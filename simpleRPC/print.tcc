#ifndef __SIMPLE_RPC_PRINT_TCC__
#define __SIMPLE_RPC_PRINT_TCC__

#include <Arduino.h>

#define _END_OF_STRING '\0'


/**
 * Recursion terminator for {multiPrint()}.
 */
inline size_t multiPrint(void) {
  return 0;
}

/**
 * Write a list of parameters to serial.
 *
 * @arg {T} arg - Parameter to be printed.
 * @arg {Args...} args... - Remaining parameters.
 *
 * @return {size_t} - Number of bytes written.
 */
template<class T, class... Args>
size_t multiPrint(T arg, Args... args) {
  return Serial.write(arg) + multiPrint(args...);
}

#endif
