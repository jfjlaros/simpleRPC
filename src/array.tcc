#pragma once

template <class T, size_t n>
class Array {
public:
  Array() = default;

  /*!
   * Create an array using an initialiser list.
   *
   * \param data... Data.
   */
  template <class... Ts>
    Array(Ts...);

  /*!
   * Create an Array using a C array.
   *
   * \param arr C array.
   */
  Array(T const (&)[n]);

  T& operator[](size_t const);
  T const& operator[](size_t const) const;

  T* begin();
  T* end();
  T const* begin() const;
  T const* end() const;

  /*!
   * Get the number of elements.
   *
   * \return Array size.
   */
  size_t size() const;

private:
  T arr_[n] {};
};


template <class T, size_t n>
template <class... Ts>
Array<T, n>::Array(Ts... data) : arr_ {data...} {}

template <class T, size_t n>
Array<T, n>::Array(T const (&arr)[n]) {
  for (size_t i {0}; i < n; ++i) {
    arr_[i] = arr[i];
  }
}


template <class T, size_t n>
T& Array<T, n>::operator[](size_t const idx) {
  return arr_[idx];
}

template <class T, size_t n>
T const& Array<T, n>::operator[](size_t const idx) const {
  return arr_[idx];
}


template <class T, size_t n>
T* Array<T, n>::begin() {
  return arr_;
}

template <class T, size_t n>
T* Array<T, n>::end() {
  return arr_ + n;
}

template <class T, size_t n>
T const * Array<T, n>::begin() const {
  return arr_;
}

template <class T, size_t n>
T const* Array<T, n>::end() const {
  return arr_ + n;
}


template <class T, size_t n>
size_t Array<T, n>::size() const {
  return n;
}
