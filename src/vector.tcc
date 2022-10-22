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
    for (size_t i = 0; i < size; i++) {
      data_[i].T::~T();
    }

    free(data_);
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
  for (size_t i = size; i < this->size; i++) {
    data_[i].T::~T();
  }

  data_ = static_cast<T*>(realloc(
    static_cast<void*>(data_), size * sizeof(T)));

  for (size_t i = this->size; i < size; i++) {
    data_[i] = T();
  }

  this->size = size;
}
