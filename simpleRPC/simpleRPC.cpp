#include "simpleRPC.h"
#include "macros.inl"


/*
 * Build a static array of function signatures.
 */
#define INTERFACE(doc, type, name, args...) \
  {(char *)QUOTE(name), (char *)QUOTE(type), (char *)QUOTE(args), (char *)doc},

const Method methods[] = {
  #include "methods.inc"
};

#undef INTERFACE

const byte numberOfMethods = sizeof(methods) / sizeof(Method);


/*
 * Make the functions available for the interface() function.
 */
#define INTERFACE(doc, type, name, args...) \
  extern type name(args);

#include "methods.inc"

#undef INTERFACE


/*
 * Build the interface() function.
 */
#define NOT_VOID_void 0
#define NOT_VOID(type) CAT(NOT_VOID_, type)

#define READ_VAL(type) \
  WHEN(NOT_VOID(type)) ( \
    readVal<type>())

#define SEPARATOR(head, tail...) \
  WHEN(head) ( \
    ,)

#define WRITE_VAL(type, args...) \
  IF(NOT_VOID(type)) ( \
    writeVal(args), \
    args)

#define READ_ARGS_ID() READ_ARGS
#define READ_ARGS(type, tail...) \
    WHEN(type) ( \
      READ_VAL(type)SEPARATOR(tail) \
      OBSTRUCT(READ_ARGS_ID)()(tail))

#define INTERFACE(doc, type, name, args...) \
  case __COUNTER__: \
    WRITE_VAL(type, name(EVAL(READ_ARGS(args, 0)))); \
    break;

/**
 * Receiver for incoming RPC calls.
 */
void interface(void) {
  int i;

  if (Serial.available()) {
    switch (Serial.read()) {
      #include "methods.inc"
      default:
        Serial.write(numberOfMethods);
        for (i = 0; i < numberOfMethods; i++) {
          Serial.print(methods[i].type);
          Serial.print(";");
          Serial.print(methods[i].name);
          Serial.print(";");
          Serial.print(methods[i].args);
          Serial.print(";");
          Serial.println(methods[i].doc);
        }
        break;
    }
  }
}

#undef INTERFACE

/**
 * Test function.
 */
int ping(int x) {
  return x;
}
