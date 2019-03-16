#ifndef __SIMPLE_RPC_TUPLE_TCC__
#define __SIMPLE_RPC_TUPLE_TCC__

/*
 * Empty tuple.
 */
template<class... Args>
struct Tuple {};

/*
 * Nested tuple.
 *
 * {T} head - First element.
 * {Args...} tail - Remaining elements.
 */
template<class T, class... Args>
struct Tuple<T, Args...> {
  T head;
  Tuple <Args...>tail;
};


/*
 * Nested object.
 *
 * {Tuple} members - Nested tuple containing elements.
 */
template<class... Args>
struct Object {
  Tuple <Args...>members;
};


/**
 * Make a nested tuple from a list of parameters.
 *
 * @arg {Args...} args - Values to store in a nested tuple.
 *
 * @return {Tuple} - Nested tuple containing {args}.
 */
template<class... Args>
Tuple <Args...>pack(Args... args) {
  Tuple <Args...>tuple = {args...};

  return tuple;
}

/**
 * Cast a struct to a tuple.
 *
 * @arg {T} s - Struct.
 *
 * @return {Tuple} - Nested tuple representation of {s}.
 */
template<class... Args, class T>
Tuple <Args...>castStruct(T s) {
  Tuple <Args...>*t = (Tuple <Args...> *)&s;

  return *t;
}

#endif
