#ifndef SIMPLE_RPC_COLLECT_TCC_
#define SIMPLE_RPC_COLLECT_TCC_

#include "print.tcc"

//! \defgroup collector

/*! \ingroup collector
 * String collector.
 */
class Collector {
  public:
    Collector(void) {}
    ~Collector(void);
    void add(char const*);
    template <class I>
      void print(I&);
  private:
    char const** _data = NULL;
    size_t _size = 0;
};


//! Destructor.
Collector::~Collector(void) {
  free(_data);
}

/*!
 * Add a string.
 *
 * \param str String.
 */
void Collector::add(char const* str) {
  _size++;
  _data = (char const**)realloc(
    (void*)_data, _size * sizeof(char const*));
  _data[_size - 1] = str;
}

/*!
 * Write collected data.
 *
 * \param io Input / output object.
 */
template <class I>
void Collector::print(I& io) {
  for (size_t i = 0; i < _size; i++) {
    rpcPrint(io, _data[i]);
  }

  free(_data);
  _data = NULL;
  _size = 0;
}

#endif
