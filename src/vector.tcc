#pragma once

#include <Arduino.h>

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
  bool destroy_ = true; //!< Free memory when destructor is called.
  T* data_ = nullptr;
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
  this->destroy_ = destroy;
  data_ = data;
}

//! Destructor.
template <class T>
Vector<T>::~Vector() {
  if (destroy_) {
    delete[] data_;
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
  return data_[index];
}

/*!
 * Resize the Vector.
 *
 * \param size New size of the Vector.
 */
template <class T>
void Vector<T>::resize(size_t const size) {
  T* newData = new T[size];

  for (size_t i = 0; i < min(this->size, size); i++) {
    newData[i] = data_[i];
  }

  delete[] data_;
  data_ = newData;

  this->size = size;
}
