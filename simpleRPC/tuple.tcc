#ifndef __SIMPLE_RPC_TUPLE_TCC__
#define __SIMPLE_RPC_TUPLE_TCC__

template<class... Args>
struct Tuple {};

template<class T, class... Args>
struct Tuple<T, Args...> {
  T head;
  Tuple <Args...>tail;
};

template<class... Args>
Tuple <Args...>makeTuple(Args... args) {
  Tuple <Args...>tuple = {args...};

  return tuple;
}

#endif
