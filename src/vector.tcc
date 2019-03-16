#ifndef __SIMPLE_RPC_VECTOR_TCC__
#define __SIMPLE_RPC_VECTOR_TCC__


template<class T>
class Vector {
  public:
    Vector(void);
    //Vector(size_t);
    ~Vector(void);
    void setLength(size_t);
    T &operator[](size_t);
    size_t length;
  private:
    T **_data;
};


template<class T>
Vector<T>::Vector(void) {
  length = 0;
  _data = NULL;
}

/*
template<class T>
Vector<T>::Vector(size_t l) {
  length = l;
  _data = (T *)malloc(length * sizeof(T));
}
*/

template<class T>
Vector<T>::~Vector(void) {
  int i;

  for (i = 0; i < length; i++) {
    delete(_data[i]);
  }
  free(_data);
}

template<class T>
T &Vector<T>::operator[](size_t index) {
  return *_data[index];
}

template<class T>
void Vector<T>::setLength(size_t l) {
  int i;

  length = l;
  _data = (T **)realloc((void *)_data, length * sizeof(T *));

  for (i = 0; i < length; i++) {
    _data[i] = new(T);
  }
}

#endif
