#ifndef SIMPLE_RPC_VECTOR_TCC_
#define SIMPLE_RPC_VECTOR_TCC_

//! \defgroup vector

/*! \ingroup vector
 * Generic Vector.
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
    size_t size = 0;     //!< Number of elements.
    bool destroy = true; //!< Free memory when destructor is called.
  private:
    T* _data = NULL;
};


/*!
 * Create a Vector with `size` elements.
 *
 * \param size Size of the Vector.
 */
template <class T>
Vector<T>::Vector(size_t size) {
  resize(size);
}

/*!
 * Create a Vector with `size` elements from a C array.
 *
 * \param size Size of the Vector.
 * \param data Pointer to data.
 * \param destroy Free `data` in the destructor.
 */
template <class T>
Vector<T>::Vector(size_t size, T* data, bool destroy) {
  this->size = size;
  this->destroy = destroy;
  _data = data;
}

//! Destructor.
template <class T>
Vector<T>::~Vector(void) {
  if (destroy) {
    for (size_t i = 0; i < size; i++) {
      _data[i].T::~T();
    }

    free(_data);
  }
}

/*!
 * Get a reference to an element.
 *
 * This can be used for both retrieval as well as assignment.
 *
 * \param index Index.
 *
 * \return Reference to element at index `index`.
 */
template <class T>
T& Vector<T>::operator[](size_t index) {
  return _data[index];
}

/*!
 * Resize the Vector.
 *
 * \param size New size of the Vector.
 */
template <class T>
void Vector<T>::resize(size_t size) {
  for (size_t i = size; i < this->size; i++) {
    _data[i].T::~T();
  }

  _data = (T*)realloc((void*)_data, size * sizeof(T));

  for (size_t i = this->size; i < size; i++) {
    _data[i] = T();
  }

  this->size = size;
}

#endif
