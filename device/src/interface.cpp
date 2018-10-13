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
#define INTERFACE(type, name, args...) \
  {(char *)QUOTE(name), (char *)QUOTE(type), (char *)QUOTE(args)},

const Method methods[] = {
  #include "functions.h"
};

const int numberOfMethods = sizeof(methods) / sizeof(Method);

#undef INTERFACE


/*
 * Make the functions available for the caller() function.
 */
#define INTERFACE(type, name, args...) \
  extern type name(args);

#include "functions.h"

#undef INTERFACE


/*
 * Build a function for calling the functions.
 */
#define parse_void
#define parse_float Serial.parseFloat()
#define parse_int Serial.parseInt()
#define parse(type) PRIMITIVE_CAT(parse_, type)

#define xrite_void 0
#define xrite(type) PRIMITIVE_CAT(xrite_, type)

#define M(type) \
  WHEN(type) ( \
    parse(type))

#define S(head, tail...) \
  WHEN(head) ( \
    ,)

#define W(type, ...) \
  IF(xrite(type)) ( \
    Serial.write(__VA_ARGS__), \
    __VA_ARGS__)

#define reduce_id() reduce
#define reduce(type, tail...) \
    WHEN(type) ( \
      M(type)S(tail) \
      OBSTRUCT(reduce_id)()(tail))

#define INTERFACE(type, name, args...) \
  case __COUNTER__: \
    W(type, name(EVAL(reduce(args, 0)))); \
    break;


void caller(void) {
  int i = 0;

  switch (i) {
    case 0xff:
      break;
    #include "functions.h"
  }
}

#undef INTERFACE
