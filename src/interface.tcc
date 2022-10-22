#pragma once

/*
 * Template library for exporting native C and C++ functions as remote
 * procedure calls.
 *
 * For more information about (variadic) templates:
 * \li http://www.drdobbs.com/cpp/extracting-function-parameter-and-return/240000586
 * \li https://eli.thegreenplace.net/2014/variadic-templates-in-c/
 * \li https://en.cppreference.com/w/cpp/language/parameter_pack
 */
#include "rpcCall.tcc"
#include "signature.tcc"

//! \defgroup interface


/*!
 * Write the signature and documentation of a function.
 *
 * \param io Stream.
 * \param f Function pointer.
 * \param doc Function documentation.
 */
template <class F, class D>
void writeDescription_(Stream& io, F f, D doc) {
  signature(io, f);
  rpcPrint(io, ';', doc, '\0');
}


//! Recursion terminator for `describe_()`.
inline void describe_(Stream& io) {
  rpcPrint(io, '\0');
}

/*!
 * Describe a list of functions.
 *
 * \param io Stream.
 * \param f Function pointer.
 * \param doc Function documentation.
 * \param args Remaining parameters.
 */
template <class F, class D, class... Args>
void describe_(Stream& io, F f, D doc, Args... args) {
  /*
   * The first two parameters `f` and `doc` are isolated and passed to
   * `writeDescription_()`. Then a recursive call to process the remaining
   * parameters is made.
   */
  writeDescription_(io, f, doc);
  describe_(io, args...);
}

//! \copydoc describe_(Stream&, F, D, Args...)
template <class U, class V, class D, class... Args>
void describe_(Stream& io, Tuple<U, V> t, D doc, Args... args) {
  writeDescription_(io, t.tail.head, doc);
  describe_(io, args...);
}


//! Recursion terminator for `select_()`.
inline void select_(Stream&, uint8_t, uint8_t) {}

/*!
 * Select and call a function indexed by `number`.
 *
 * \param io Stream.
 * \param number Function index.
 * \param depth Current index.
 * \param f Function pointer.
 * \param - Function documentation.
 * \param args Remaining parameters.
 */
template <class F, class D, class... Args>
void select_(Stream& io, uint8_t number, uint8_t depth, F f, D, Args... args) {
  /*
   * The parameter `f` and its documentation string are isolated, discarding
   * the latter. If the selected function is encountered (i.e., if `depth`
   * equals `number`), function `f` is called. Otherwise, a new try is made
   * recursively.
   */
  if (depth == number) {
    rpcCall(io, f);
    return;
  }
  select_(io, number, depth + 1, args...);
}


/*! \ingroup interface
 * RPC interface.
 *
 * The `args` parameter pack is a list of pairs (function pointer,
 * documentation). The documentation string can be of type `char const*`, or
 * the PROGMEM `F()` macro can be used to reduce memory footprint.
 *
 * \param io Stream.
 * \param args Parameter pairs (function pointer, documentation).
 */
template <class... Args>
void interface(Stream& io, Args... args) {
  /*
   * One byte is read into `command`, if the value equals `LIST_REQ_`, the list
   * of functions is described. Otherwise, the function indexed by `command` is
   * called.
   */
  if (io.available()) {
    uint8_t command;

    rpcRead(io, &command);

    if (command == LIST_REQ_) {
      rpcPrint(io, PROTOCOL_, '\0', VERSION_[0], VERSION_[1], VERSION_[2]);
      hardwareDefs(io);
      describe_(io, args...);
      return;
    }
    select_(io, command, 0, args...);
  }
}

//! Recursion terminator for `interface()`.
template <class... Args>
void interface(Tuple<>, Args...) {}

/*! \ingroup interface
 * Multiple RPC interfaces.
 *
 * Similar to the standard interface , but with support for multiple I/O
 * interfaces, passed as Tuple `t`.
 *
 * \sa interface(Stream&, Args...)
 *
 * \param t Tuple of input / output objects.
 * \param args Parameter pairs (function pointer, documentation).
 */
template <class... Membs, class... Args>
void interface(Tuple<Membs...> t, Args... args) {
  interface(*t.head, args...);
  interface(t.tail, args...);
}
