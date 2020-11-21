#ifndef SIMPLE_RPC_COLLECT_TCC_
#define SIMPLE_RPC_COLLECT_TCC_

#include "print.tcc"

class Collection {
  public:
    Collection(void) {}
    ~Collection(void);
    void add(char const*);
    template <class I>
      void print(I&);
  private:
    char const** _data = NULL;
    size_t _size = 0;
};


Collection::~Collection(void) {
  free(_data);
}

void Collection::add(char const* str) {
  _size++;
  _data = (char const**)realloc(
    (void*)_data, _size * sizeof(char const*));
  _data[_size - 1] = str;
}

template <class I>
void Collection::print(I& io) {
  for (size_t i = 0; i < _size; i++) {
    rpcPrint(io, _data[i]);
  }
}

#endif
