#ifndef SIMPLE_RPC_VECTOR_TCC_
#define SIMPLE_RPC_VECTOR_TCC_

/**
 * @class Vector
 *
 * Generic vector.
 */
template <class T>
class Vector {
  public:
    Vector(void) {}
    Vector(size_t);
    Vector(size_t, T*, bool=true);
    ~Vector(void);
    void resize(size_t);
    T& operator[](size_t);
    size_t size = 0;     ///< Number of elements.
    bool destroy = true; ///< Free memory when destructor is called.
  private:
    T* _data = NULL;
};


/**
 * Constructor.
 *
 * @param size Size of the vector.
 */
template <class T>
Vector<T>::Vector(size_t size) {
  resize(size);
}

/**
 * Constructor.
 *
 * @param size Size of the vector.
 * @param data Pointer to data.
 * @param destroy Free @a data in the destructor.
 */
template <class T>
Vector<T>::Vector(size_t size, T* data, bool destroy) {
  this->size = size;
  this->destroy = destroy;
  _data = data;
}

/**
 * Destructor.
 */
template <class T>
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
 * @param index Index.
 *
 * @return Reference to element at index @a index.
 */
template <class T>
T& Vector<T>::operator[](size_t index) {
  return _data[index];
}

/**
 * Set the size of a vector.
 *
 * @param size New size of the vector.
 */
template <class T>
void Vector<T>::resize(size_t size) {
  int i;

  for (i = size; i < this->size; i++) {
    _data[i].T::~T();
  }

  _data = (T*)realloc((void*)_data, size * sizeof(T));

  for (i = this->size; i < size; i++) {
    _data[i] = T();
  }

  this->size = size;
}

#endif
