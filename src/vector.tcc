#pragma once

#include <Arduino.h>

/*!
 * Generic Vector.
 */
template <class T>
class Vector {
public:
  Vector() {}

  /*! Create a Vector with `size` elements.
   *
   * \param size Size of the Vector.
   */
  Vector(size_t const);

  /*!
   * Create a Vector with `size` elements from a C array.
   *
   * \param size Size of the Vector.
   * \param data Pointer to data.
   */
  Vector(size_t const, T* const);

  Vector(Vector const& v);

  ~Vector();

  Vector& operator=(Vector);


  /*!
   * Get a reference to an element.
   *
   * This can be used for both retrieval as well as assignment.
   *
   * \param index Index.
   *
   * \return Reference to element at index `index`.
   */
  T& operator[](size_t) const;

  size_t size() const {
    return size_;
  }
  /*!
   * Resize the Vector.
   *
   * \param size New size of the Vector.
   */
  void resize(size_t);

  template <class U>
    friend void swap(Vector<U>&, Vector<U>&) noexcept;

  //T* begin();
  //T* end();
  //T const* begin() const;
  //T const* end() const;

private:
  size_t size_ {0};
  T* data_ {nullptr};
};

template <class T>
void swap_(T& a, T& b) noexcept {
  T tmp {a};
  a = b;
  b = tmp;
}

template <class U>
void swap(Vector<U>& a, Vector<U>& b) noexcept {
  swap_(a.size_, b.size_);
  swap_(a.data_, b.data_);
}


template <class T>
Vector<T>::Vector(size_t const size) {
  resize(size);
}

template <class T>
Vector<T>::Vector(size_t const size, T* const data) {
  this->size_ = size;
  data_ = data;
}

template <class T>
Vector<T>::Vector(Vector const& v) : size_ {v.size_} {
  data_ = new T[size_];
  for (size_t i {0}; i < size_; i++) {
    data_[i] = v.data_[i];
  }
}

template <class T>
Vector<T>::~Vector() {
  delete[] data_;
}

template <class T>
Vector<T>& Vector<T>::operator=(Vector v) {
  swap(*this, v);
  return *this;
}


template <class T>
T& Vector<T>::operator[](size_t const index) const {
  return data_[index];
}

template <class T>
void Vector<T>::resize(size_t const size) {
  T* newData {new T[size]};
  for (size_t i {0}; i < min(this->size_, size); i++) {
    newData[i] = data_[i];
  }
  delete[] data_;
  data_ = newData;

  this->size_ = size;
}
