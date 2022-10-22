#pragma once

/*!
 * Generic Vector.
 */
template <class T>
class Vector {
public:
  size_t size = 0;     //!< Number of elements.

  Vector() {}
  Vector(size_t const);
  Vector(size_t const, T* const, bool const=true);
  ~Vector();

  void resize(size_t);
  T& operator[](size_t) const;

private:
  bool _destroy = true; //!< Free memory when destructor is called.
  T* _data = nullptr;
};


/*!
 * Create a Vector with `size` elements.
 *
 * \param size Size of the Vector.
 */
template <class T>
Vector<T>::Vector(size_t const size) {
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
Vector<T>::Vector(size_t const size, T* const data, bool const destroy) {
  this->size = size;
  this->_destroy = destroy;
  _data = data;
}

//! Destructor.
template <class T>
Vector<T>::~Vector() {
  if (_destroy) {
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
T& Vector<T>::operator[](size_t const index) const {
  return _data[index];
}

/*!
 * Resize the Vector.
 *
 * \param size New size of the Vector.
 */
template <class T>
void Vector<T>::resize(size_t const size) {
  for (size_t i = size; i < this->size; i++) {
    _data[i].T::~T();
  }

  _data = static_cast<T*>(realloc(
    static_cast<void*>(_data), size * sizeof(T)));

  for (size_t i = this->size; i < size; i++) {
    _data[i] = T();
  }

  this->size = size;
}
