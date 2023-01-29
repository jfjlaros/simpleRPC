template <class T>
class Span {
public:
  Span() = default;

  /*!
   * Create a Span with `n` elements.
   */
  template <size_t n>
    Span(T (&)[n]);

  T& operator [](size_t const);
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
   * \return Span size.
   */
  size_t size() const;

private:
  T* data_ {};
  size_t size_ {};
};


template <class T>
template <size_t n>
Span<T>::Span(T (&a)[n]) : data_ {a}, size_ {n} {}


template <class T>
T& Span<T>::operator [](size_t const idx) {
  return data_[idx];
}

template <class T>
T const& Span<T>::operator [](size_t const idx) const {
  return data_[idx];
}


template <class T>
T* Span<T>::begin() {
  return data_;
}

template <class T>
T* Span<T>::end() {
  return data_ + size_;
}

template <class T>
T const* Span<T>::begin() const {
  return data_;
}

template <class T>
T const* Span<T>::end() const {
  return data_ + size_;
}


template <class T>
T* Span<T>::data() const {
  return data_;
}

template <class T>
size_t Span<T>::size() const {
  return size_;
}
