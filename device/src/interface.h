#ifndef __INTERFACE_H__
#define __INTERFACE_H__

typedef struct {
  char *name,
       *type,
       *args,
       *doc;
} Method;

extern const Method methods[];
extern const byte numberOfMethods;

void serialInterface(void);

/**
 * Read a value from serial.
 */
template<typename T> T readVal(void) {
  T data;
  int i;

  for (i = 0; i < sizeof(T); i++) {
    Serial.readBytes((char *)&(((byte *)&data)[i]), 1);
  }

  return data;
}

/**
 * Write a value to serial.
 */
template<typename T> void writeVal(T data) {
  int i;

  for (i = 0; i < sizeof(T); i++) {
    Serial.write(((byte *)&data)[i]);
  }
}

#endif
