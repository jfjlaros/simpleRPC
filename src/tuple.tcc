#ifndef __SIMPLE_RPC_TUPLE_TCC__
#define __SIMPLE_RPC_TUPLE_TCC__

/*
 * Empty tuple.
 */
template<class... Args>
class Tuple {
  public:
    template<class R>
      R &get(size_t);
};

/*
 * Nested tuple.
 *
 * {T} head - First element.
 * {Args...} tail - Remaining elements.
 */
template<class T, class... Args>
class Tuple<T, Args...> {
  public:
    template<class R>
      R &get(size_t);
    T head;
    Tuple <Args...>tail;
};

/*
 * Nested object.
 *
 * {Tuple} members - Nested tuple containing elements.
 */
template<class... Args>
class Object {
  public:
    template<class R>
      R &get(size_t);
    Tuple <Args...>members;
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
