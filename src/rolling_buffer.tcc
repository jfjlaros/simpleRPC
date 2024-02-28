#pragma once

#include "Arduino.h"

template <class T, size_t S>
class RollingBufferBase_ {
protected:
  RollingBufferBase_() : _write_idx(0), _read_idx(0), _cnt(0), _dropped_cnt(0) {
      // _mutex = xSemaphoreCreateMutexStatic(&_xMutexBuffer);
  }

public:
  void push(const T &value) {
    // xSemaphoreTake(_mutex, portMAX_DELAY);

    _items[_write_idx] = value;

    _write_idx++;
    if (_write_idx >= S) {
      _write_idx = 0;
    }

    const bool HASFREESLOTS = (_cnt < S);
    if (HASFREESLOTS) {
      _cnt++;
    } else {
      _dropped_cnt++;
      _read_idx++;
      if (_read_idx >= S) {
        _read_idx = 0;
      }
    }

    // xSemaphoreGive(_mutex);
  }

  const T *pop() {
      if (_cnt > 0) {
          const T *item = &_items[_read_idx];

          _read_idx++;
          if (_read_idx >= S) {
              _read_idx = 0;
          }
          _cnt--;

          return item;
      } else {
          return NULL;
      }
  }

public:
  size_t begin_read() {
    // xSemaphoreTake(_mutex, portMAX_DELAY);
    return _cnt;
  }

  void end_read() {
    // xSemaphoreGive(_mutex);
  }

  const size_t capacity = S;

  size_t count() {
    // xSemaphoreTake(_mutex, portMAX_DELAY);
    size_t cnt = _cnt;
    // xSemaphoreGive(_mutex);
    return cnt;
  }

  size_t dropped() {
    // xSemaphoreTake(_mutex, portMAX_DELAY);
    size_t cnt = _dropped_cnt;
    // xSemaphoreGive(_mutex);
    return cnt;
  }

protected:
  size_t _write_idx;
  size_t _read_idx;
  size_t _cnt;
  size_t _dropped_cnt;

  T _items[S];

  // StaticSemaphore_t _xMutexBuffer;
  // SemaphoreHandle_t _mutex;
};

template <class T, size_t S>
class RollingBuffer : public RollingBufferBase_<T, S> {
public:
  RollingBuffer() : RollingBufferBase_<T,S>() {
  }
};

template <size_t S>
class RollingBuffer<String, S> : public RollingBufferBase_<String, S>
{
public:
  RollingBuffer() : RollingBufferBase_<String, S>() {
  }

  void push_cstr(const char *value) {
    // xSemaphoreTake(this->_mutex, portMAX_DELAY);

    this->_items[this->_write_idx] = value;

    this->_write_idx++;
    if (this->_write_idx >= S) {
      this->_write_idx = 0;
    }

    const bool HASFREESLOTS = (this->_cnt < S);
    if (HASFREESLOTS) {
      this->_cnt++;
    } else {
      this->_dropped_cnt++;
      this->_read_idx++;
      if (this->_read_idx >= S)
        this->_read_idx = 0;
    }

    // xSemaphoreGive(this->_mutex);
  }
};