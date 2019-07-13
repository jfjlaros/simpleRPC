#ifndef SIMPLE_RPC_PRINT_TCC_
#define SIMPLE_RPC_PRINT_TCC_

/** @file */

#include <Arduino.h>
#include <avr/pgmspace.h>

#include "defs.h"

/*
 * Prototypes needed for recursive definitions.
 */
template <class T, class... Args>
  size_t multiPrint(T, Args...);
template <class... Args>
  size_t multiPrint(const __FlashStringHelper*, Args...);


/**
 * Recursion terminator for @a multiPrint().
 */
inline size_t multiPrint(void) {
  return 0;
}

/**
 * Write a list of parameters to serial.
 *
 * @param arg Parameter to be printed.
 * @param args Remaining parameters.
 *
 * @return Number of bytes written.
 */
template <class T, class... Args>
size_t multiPrint(T arg, Args... args) {
  return Serial.write(arg) + multiPrint(args...);
}

// String support.
template <class... Args>
size_t multiPrint(String& arg, Args... args) {
  return Serial.write(arg.c_str()) + multiPrint(args...);
}

// @a F() macro support.
template <class... Args>
size_t multiPrint(const __FlashStringHelper* arg, Args... args) {
  return Serial.print(arg) + multiPrint(args...);
}

#endif
