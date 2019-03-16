#ifndef __SIMPLE_RPC_VECTOR_TCC__
#define __SIMPLE_RPC_VECTOR_TCC__

/*
 * Vector template library.
 */

template<class T>
class Vector {
  public:
    Vector(void);
    ~Vector(void);
    void setLength(size_t);
    T &operator[](size_t);
    size_t length;
  private:
    T *_data;
};


/**
 * Constructor.
 */
template<class T>
Vector<T>::Vector(void) {
  length = 0;
  _data = NULL;
}

/**
 * Destructor.
 */
template<class T>
Vector<T>::~Vector(void) {
  int i;

  for (i = 0; i < length; i++) {
    _data[i].T::~T();
  }

  free(_data);
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
 * Set the length of a vector.
 *
 * @arg {size_t} newLength - New length of the vector.
 */
template<class T>
void Vector<T>::setLength(size_t newLength) {
  int i;

  length = newLength;
  _data = (T *)realloc((void *)_data, length * sizeof(T));

  for (i = 0; i < length; i++) {
    _data[i] = T();
  }
}

#endif
