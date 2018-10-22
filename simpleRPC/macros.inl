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
