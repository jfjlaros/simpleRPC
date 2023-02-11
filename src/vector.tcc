#pragma once

#include <Arduino.h>


template <class T>
void swap_(T& a, T& b) noexcept {
  T tmp {a};
  a = b;
  b = tmp;
}


/*!
 * Generic Vector.
 */
template <class T>
class Vector {
public:
  Vector() = default;
  Vector(Vector const& v);

  /*! Create a Vector with `size` elements.
   *
   * \param size Vector size.
   */
  Vector(size_t const);

  /*!
   * Create a Vector with `size` elements from a C array.
   *
   * \param arr C array.
   */
  template <size_t n>
    Vector(T const (&)[n]);

  ~Vector();

  Vector& operator=(Vector);
  T& operator[](size_t const);
  T const& operator [](size_t const) const;

  T* begin();
  T* end();
  T const* begin() const;
  T const* end() const;

  /*!
   * Get the underlying data.
   *
   * \return data.
   */
  T* data() const;

  /*!
   * Get the number of elements.
   *
   * \return Vector size.
   */
  size_t size() const;

  /*!
   * Set the number of elements.
   *
   * \param size Vector size.
   */
  void resize(size_t const);

  /*! Clear the contents. */
  void clear();

  /*!
   * Add an element to the back.
   *
   * \param el Element.
   */
  void push_back(T const&);

  /*!
   * Add an element to the back.
   *
   * \param el Element.
   */
  void push_back(T const&&);

  /*!
   * Remove an element from the back.
   *
   * \return Element.
   */
  T pop_back();

  template <class U>
    friend void swap(Vector<U>&, Vector<U>&) noexcept;

private:
  void copy_(T const* const, size_t const size);

  size_t size_ {0};
  T* data_ {nullptr};
};


template <class T>
Vector<T>::Vector(Vector const& other)
    : size_ {other.size_}, data_ {new T[other.size_]} {
  copy_(other.data_, other.size_);
}

template <class T>
Vector<T>::Vector(size_t const size)
    : size_ {size}, data_ {new T[size]} {}

template <class T>
template <size_t n>
Vector<T>::Vector(T const (&arr)[n])
    : size_ {n}, data_ {new T[n]} {
  copy_(arr, n);
}

template <class T>
Vector<T>::~Vector() {
  delete[] data_;
}


template <class T>
Vector<T>& Vector<T>::operator=(Vector<T> other) {
  swap(*this, other);
  return *this;
}

template <class T>
T& Vector<T>::operator[](size_t const idx) {
  return data_[idx];
}

template <class T>
T const& Vector<T>::operator[](size_t const idx) const {
  return data_[idx];
}


template <class T>
T* Vector<T>::begin() {
  return data_;
}

template <class T>
T* Vector<T>::end() {
  return data_ + size_;
}

template <class T>
T const* Vector<T>::begin() const {
  return data_;
}

template <class T>
T const* Vector<T>::end() const {
  return data_ + size_;
}


template <class T>
T* Vector<T>::data() const {
  return data_;
}

template <class T>
size_t Vector<T>::size() const {
  return size_;
}

template <class T>
void Vector<T>::resize(size_t const size) {
  T* data {new T[size]};
  swap_(data_, data);
  copy_(data, min(size_, size));
  delete[] data;

  size_ = size;
}

template <class T>
void Vector<T>::clear() {
  size_ = 0;
  delete[] data_;
  data_ = nullptr;
}

template <class T>
void Vector<T>::push_back(T const& el) {
  resize(size_ + 1);
  data_[size_ - 1] = el;
}

template <class T>
void Vector<T>::push_back(T const&& el) {
  resize(size_ + 1);
  data_[size_ - 1] = el;
}

template <class T>
T Vector<T>::pop_back() {
  T el {data_[size_ - 1]};
  resize(size_ - 1);
  return el;
}


template <class T>
void Vector<T>::copy_(T const* const data, size_t const size) {
  for (size_t i {0}; i < size; ++i) {
    data_[i] = data[i];
  }
}


template <class U>
void swap(Vector<U>& a, Vector<U>& b) noexcept {
  swap_(a.size_, b.size_);
  swap_(a.data_, b.data_);
}
