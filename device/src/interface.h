#ifndef __INTERFACE_H__
#define __INTERFACE_H__

#include <Arduino.h>


typedef struct {
  char *name,
       *type,
       *args,
       *doc;
} Method;

extern const Method methods[];
extern const byte numberOfMethods;

void interface(void);


/**
 * Read a value from the serial device.
 *
 * @return {T} - Value.
 */
template<typename T> T readVal(void) {
  T data;
  unsigned int i;

  for (i = 0; i < sizeof(T); i++) {
    Serial.readBytes((char *)&(((byte *)&data)[i]), 1);
  }

  return data;
}

/**
 * Write a value to the serial device.
 *
 * @arg {T} data - Value.
 */
template<typename T> void writeVal(T data) {
  unsigned int i;

  for (i = 0; i < sizeof(T); i++) {
    Serial.write(((byte *)&data)[i]);
  }
}

#endif
