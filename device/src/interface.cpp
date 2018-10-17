#include <Arduino.h>

#include "interface.h"

/*
 * https://stackoverflow.com/questions/319328
 */
#define QUOTE(x...) #x

#define EMPTY()
#define DEFER(id) id EMPTY()
#define OBSTRUCT(id) id DEFER(EMPTY)()
#define EXPAND(...) __VA_ARGS__
#define EAT(...)

#define EVAL(...)  EVAL1(EVAL1(EVAL1(__VA_ARGS__)))
#define EVAL1(...) EVAL2(EVAL2(EVAL2(__VA_ARGS__)))
#define EVAL2(...) EVAL3(EVAL3(EVAL3(__VA_ARGS__)))
#define EVAL3(...) EVAL4(EVAL4(EVAL4(__VA_ARGS__)))
#define EVAL4(...) EVAL5(EVAL5(EVAL5(__VA_ARGS__)))
#define EVAL5(...) __VA_ARGS__

#define PRIMITIVE_CAT(a, ...) a ## __VA_ARGS__

#define CHECK_N(x, n, ...) n
#define CHECK(...) CHECK_N(__VA_ARGS__, 0)

#define NOT_0 ~, 1,
#define NOT(x) CHECK(PRIMITIVE_CAT(NOT_, x))

#define COMPL_0 1
#define COMPL_1 0
#define COMPL(b) PRIMITIVE_CAT(COMPL_, b)

#define BOOL(x) COMPL(NOT(x))

#define IIF_0(t, ...) __VA_ARGS__
#define IIF_1(t, ...) t
#define IIF(c) PRIMITIVE_CAT(IIF_, c)

#define IF(c) IIF(BOOL(c))

#define WHEN(c) IF(c)(EXPAND, EAT)


/*
 * Build a static array of function signatures.
 */
#define INTERFACE(doc, type, name, args...) \
  {(char *)QUOTE(name), (char *)QUOTE(type), (char *)QUOTE(args), (char *)doc},

const Method methods[] = {
  #include "functions.h"
};

#undef INTERFACE

const byte numberOfMethods = sizeof(methods) / sizeof(Method);


/*
 * Make the functions available for the caller() function.
 */
#define INTERFACE(doc, type, name, args...) \
  extern type name(args);

#include "functions.h"

#undef INTERFACE


/*
 * Build a function for calling the functions.
 */
#define NOT_VOID_void 0
#define NOT_VOID(type) PRIMITIVE_CAT(NOT_VOID_, type)

#define READ_VAL(type) \
  WHEN(NOT_VOID(type)) ( \
    readVal<type>())

#define SEPARATOR(head, tail...) \
  WHEN(head) ( \
    ,)

#define WRITE_VAL(type, ...) \
  IF(NOT_VOID(type)) ( \
    writeVal(__VA_ARGS__), \
    __VA_ARGS__)

#define READ_ARGS_ID() READ_ARGS
#define READ_ARGS(type, tail...) \
    WHEN(type) ( \
      READ_VAL(type)SEPARATOR(tail) \
      OBSTRUCT(READ_ARGS_ID)()(tail))

#define INTERFACE(doc, type, name, args...) \
  case __COUNTER__: \
    WRITE_VAL(type, name(EVAL(READ_ARGS(args, 0)))); \
    break;

void serialInterface(void) {
  int i;

  if (Serial.available()) {
    switch (Serial.read()) {
      #include "functions.h"
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
