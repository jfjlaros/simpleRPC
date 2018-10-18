#include "interface.h"

/*
 * https://stackoverflow.com/questions/319328
 */
#define QUOTE(x...) #x

#define EMPTY()
#define DEFER(id) id EMPTY()
#define OBSTRUCT(id) id DEFER(EMPTY)()
#define EXPAND(args...) args
#define EAT(args...)

#define EVAL(args...) EVAL1(EVAL1(EVAL1(args)))
#define EVAL1(args...) EVAL2(EVAL2(EVAL2(args)))
#define EVAL2(args...) EVAL3(EVAL3(EVAL3(args)))
#define EVAL3(args...) EVAL4(EVAL4(EVAL4(args)))
#define EVAL4(args...) EVAL5(EVAL5(EVAL5(args)))
#define EVAL5(args...) args

#define CAT(a, args...) a ## args

#define CHECK_N(x, n, args...) n
#define CHECK(args...) CHECK_N(args, 0)

#define NOT_0 ~, 1,
#define NOT(x) CHECK(CAT(NOT_, x))

#define COMPL_0 1
#define COMPL_1 0
#define COMPL(b) CAT(COMPL_, b)

#define BOOL(x) COMPL(NOT(x))

#define IIF_0(t, args...) args
#define IIF_1(t, args...) t
#define IIF(c) CAT(IIF_, c)

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
 * Make the functions available for the interface() function.
 */
#define INTERFACE(doc, type, name, args...) \
  extern type name(args);

#include "functions.h"

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
 *
 * TODO: Explain protocol.
 */
void interface(void) {
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
