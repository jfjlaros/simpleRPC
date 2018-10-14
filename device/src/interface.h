#ifndef __INTERFACE_H__
#define __INTERFACE_H__

typedef struct {
  char *name,
       *type,
       *args;
} Method;

extern const Method methods[];
extern const byte numberOfMethods;

void caller(void);

template<typename T> T readVal(void) {
  T data;
  int i;

  for (i = 0; i < sizeof(T); i++) {
    Serial.readBytes((char *)&(((byte *)&data)[i]), 1);
  }

  return data;
}

template<typename T> void writeVal(T data) {
  int i;

  for (i = 0; i < sizeof(T); i++) {
    Serial.write(((byte *)&data)[i]);
  }
}

#endif
