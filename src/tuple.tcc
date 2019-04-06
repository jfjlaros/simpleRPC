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
 * Preferably this would have been an alias, but this is not supported in the
 * current version of Arduino C++.
 */
template<class... Args>
struct Object : Tuple <Args...> {
  Object() = default;
  Object(Args... args) : Tuple <Args...>({args...}) {}
};


/**
 * Recursion terminator for {Tuple::get()}.
 */
template<>
template<class R>
R &Tuple<>::get(size_t) {}

/**
 * Get a reference to an element.
 *
 * This can be used for both retrieving as well as setting the content of an
 * element.
 *
 * @arg {size_t} index - Index.
 *
 * @return {R &} - Reference to element at index {index}.
 */
template<class T, class... Args>
template<class R>
R &Tuple<T, Args...>::get(size_t index) {
  if (!index) {
    return (R &)head;
  }
  return tail.get<R>(index - 1);
}

/**
 * Get a reference to an element.
 *
 * This can be used for both retrieving as well as setting the content of an
 * element.
 *
 * @arg {size_t} index - Index.
 *
 * @return {R &} - Reference to element at index {index}.
 */
template<class... Args>
template<class R>
R &Object<Args...>::get(size_t index) {
  return members.get<R>(index);
}


/**
 * Make a nested tuple from a list of parameters.
 *
 * @arg {Args...} args - Values to store in a nested tuple.
 *
 * @return {Tuple} - Nested tuple containing {args}.
 */
template<class... Args>
Tuple <Args...>pack(Args... args) {
  Tuple <Args...>t = {args...};

  return t;
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
