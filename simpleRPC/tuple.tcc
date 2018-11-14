#ifndef __SIMPLE_RPC_TUPLE_TCC__
#define __SIMPLE_RPC_TUPLE_TCC__

/*
 * Base: empty class template.
 */
template<class... Args>
struct Tuple {};

/*
 * Nested tuple.
 *
 * {T} head: First element.
 * {Args...} tail: Rest of the elements.
 */
template<class T, class... Args>
struct Tuple<T, Args...> {
  T head;
  Tuple <Args...>tail;
};

/**
 * Make a nested tuple from a list of parameters.
 *
 * @arg {Args...} args - Values to store in a nested tuple.
 *
 * @return {Tuple} - Nested tuple containing {args}.
 */
template<class... Args>
Tuple <Args...>makeTuple(Args... args) {
  Tuple <Args...>tuple = {args...};

  return tuple;
}

#endif
