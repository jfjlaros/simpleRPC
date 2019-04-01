#ifndef __SIMPLE_RPC_VECTOR_TCC__
#define __SIMPLE_RPC_VECTOR_TCC__

template<class T>
class Vector {
  public:
    Vector(void) {}
    Vector(size_t);
    Vector(size_t, T *, bool=true);
    ~Vector(void);
    void resize(size_t);
    T &operator[](size_t);
    size_t size = 0;
    bool destroy = true;
  private:
    T *_data = NULL;
};


/**
 * Constructor.
 *
 * @arg {size_t} size - Size of the vector.
 */
template<class T>
Vector<T>::Vector(size_t size) {
  resize(size);
}

/**
 * Constructor.
 *
 * @arg {size_t} size - Size of the vector.
 * @arg {T *} data - Pointer to data.
 * @arg {bool} destroy - Free {data} in the destructor.
 */
template<class T>
Vector<T>::Vector(size_t size, T *data, bool destroy) {
  this->size = size;
  this->destroy = destroy;
  _data = data;
}

/**
 * Destructor.
 */
template<class T>
Vector<T>::~Vector(void) {
  int i;

  if (destroy) {
    for (i = 0; i < size; i++) {
      _data[i].T::~T();
    }

    free(_data);
  }
}

/**
 * Get a reference to an element.
 *
 * This can be used for both retrieving as well as setting the content of an
 * element.
 *
 * @arg {size_t} index - Index.
 *
 * @return {T &} - Reference to element at index {index}.
 */
template<class T>
T &Vector<T>::operator[](size_t index) {
  return _data[index];
}

/**
 * Set the size of a vector.
 *
 * @arg {size_t} size - New size of the vector.
 */
template<class T>
void Vector<T>::resize(size_t size) {
  int i;

  for (i = size; i < this->size; i++) {
    _data[i].T::~T();
  }

  _data = (T *)realloc((void *)_data, size * sizeof(T));

  for (i = this->size; i < size; i++) {
    _data[i] = T();
  }

  this->size = size;
}

#endif
