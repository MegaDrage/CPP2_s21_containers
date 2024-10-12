#ifndef _CONTAINERS_S21_VECTOR_H
#define _CONTAINERS_S21_VECTOR_H

#include <algorithm>
#include <initializer_list>
#include <limits>
#include <memory>
#include <stdexcept>

namespace s21_containers {

namespace __iterator {
template <typename T, typename Allocator>
class VectorIterator {
 public:
  using iterator_category = std::random_access_iterator_tag;
  using value_type = T;
  using difference_type = std::ptrdiff_t;
  using pointer = typename std::allocator_traits<Allocator>::pointer;
  using reference = T &;

  VectorIterator() : ptr(nullptr) {}
  VectorIterator(pointer p) : ptr(p) {}

  reference operator*() const { return *ptr; }
  pointer operator->() const { return ptr; }

  VectorIterator &operator++() {
    ++ptr;
    return *this;
  }
  VectorIterator operator++(int) {
    VectorIterator tmp = *this;
    ++ptr;
    return tmp;
  }

  VectorIterator &operator--() {
    --ptr;
    return *this;
  }
  VectorIterator operator--(int) {
    VectorIterator tmp = *this;
    --ptr;
    return tmp;
  }

  VectorIterator &operator+=(difference_type n) {
    ptr += n;
    return *this;
  }
  VectorIterator &operator-=(difference_type n) {
    ptr -= n;
    return *this;
  }

  VectorIterator operator+(difference_type n) const {
    return VectorIterator(ptr + n);
  }
  VectorIterator operator-(difference_type n) const {
    return VectorIterator(ptr - n);
  }

  difference_type operator-(const VectorIterator &other) const {
    return ptr - other.ptr;
  }

  bool operator==(const VectorIterator &other) const {
    return ptr == other.ptr;
  }
  bool operator!=(const VectorIterator &other) const {
    return ptr != other.ptr;
  }
  bool operator<(const VectorIterator &other) const { return ptr < other.ptr; }
  bool operator>(const VectorIterator &other) const { return ptr > other.ptr; }
  bool operator<=(const VectorIterator &other) const {
    return ptr <= other.ptr;
  }
  bool operator>=(const VectorIterator &other) const {
    return ptr >= other.ptr;
  }

 private:
  pointer ptr;
};

template <typename T, typename Allocator>
class VectorConstIterator {
 public:
  using iterator_category = std::random_access_iterator_tag;
  using value_type = T;
  using difference_type = std::ptrdiff_t;
  using pointer = const typename std::allocator_traits<Allocator>::pointer;
  using reference = const T &;

  VectorConstIterator() : ptr(nullptr) {}
  VectorConstIterator(pointer p) : ptr(p) {}

  reference operator*() const { return *ptr; }
  pointer operator->() const { return ptr; }

  VectorConstIterator &operator++() {
    ++ptr;
    return *this;
  }
  VectorConstIterator operator++(int) {
    VectorConstIterator tmp = *this;
    ++ptr;
    return tmp;
  }

  VectorConstIterator &operator--() {
    --ptr;
    return *this;
  }
  VectorConstIterator operator--(int) {
    VectorConstIterator tmp = *this;
    --ptr;
    return tmp;
  }

  VectorConstIterator &operator+=(difference_type n) {
    ptr += n;
    return *this;
  }
  VectorConstIterator &operator-=(difference_type n) {
    ptr -= n;
    return *this;
  }

  VectorConstIterator operator+(difference_type n) const {
    return VectorConstIterator(ptr + n);
  }
  VectorConstIterator operator-(difference_type n) const {
    return VectorConstIterator(ptr - n);
  }

  difference_type operator-(const VectorConstIterator &other) const {
    return ptr - other.ptr;
  }

  bool operator==(const VectorConstIterator &other) const {
    return ptr == other.ptr;
  }
  bool operator!=(const VectorConstIterator &other) const {
    return ptr != other.ptr;
  }
  bool operator<(const VectorConstIterator &other) const {
    return ptr < other.ptr;
  }
  bool operator>(const VectorConstIterator &other) const {
    return ptr > other.ptr;
  }
  bool operator<=(const VectorConstIterator &other) const {
    return ptr <= other.ptr;
  }
  bool operator>=(const VectorConstIterator &other) const {
    return ptr >= other.ptr;
  }

 private:
  pointer ptr;
};
}  // namespace __iterator

template <typename T, typename Allocator = std::allocator<T>>
class s21_vector {
 public:
  using value_type = T;
  using reference = value_type &;
  using const_reference = const value_type &;
  using iterator = __iterator::VectorIterator<T, Allocator>;
  using const_iterator = const __iterator::VectorIterator<T, Allocator>;
  using size_type = size_t;
  using allocator_type = Allocator;
  using Allocator_Traits = std::allocator_traits<Allocator>;
  using pointer = typename std::allocator_traits<Allocator>::pointer;
  using const_pointer =
      typename std::allocator_traits<Allocator>::const_pointer;

  s21_vector() : _array(nullptr), _size(0), _capacity(0) {}

  s21_vector(size_type n)
      : _array(Allocator_Traits::allocate(_alloc, n)), _size(n), _capacity(n) {
    for (size_type i = 0; i < _size; ++i) {
      _place_into_memory(_array + i);
    }
  }

  explicit s21_vector(size_type n, const T &value)
      : _array(Allocator_Traits::allocate(_alloc, n)), _size(n), _capacity(n) {
    for (size_type i = 0; i < _size; ++i) {
      _place_into_memory(_array + i, value);
    }
  }

  s21_vector(std::initializer_list<value_type> const &items)
      : _array(Allocator_Traits::allocate(_alloc, items.size())),
        _size(items.size()),
        _capacity(items.size()) {
    size_type i = 0;
    for (auto begin = items.begin(), end = items.end(); begin != end;
         ++begin, ++i) {
      _place_into_memory(_array + i, *begin);
    }
  }

  s21_vector(const s21_vector &v)
      : _array(Allocator_Traits::allocate(_alloc, v._capacity)),
        _size(v._size),
        _capacity(v._capacity) {
    for (size_t i = 0; i < _size; ++i) {
      _place_into_memory(_array + i, *(v._array + i));
    }
  }

  s21_vector(s21_vector &&v)
      : _array(v._array),
        _size(v._size),
        _capacity(v._capacity),
        _alloc(std::move(v._alloc)) {
    v._array = nullptr;
    v._size = 0;
    v._capacity = 0;
  }

  ~s21_vector() {
    clear();
    Allocator_Traits::deallocate(_alloc, _array, _capacity);
  }

  void clear() noexcept {
    _destroy_elements(_size);
    _size = 0;
  }
  void pop_back() noexcept {
    if (_size > 0) {
      --_size;
      Allocator_Traits::destroy(_alloc, _array + _size);
    }
  }

  size_type max_size() const {
    return std::numeric_limits<std::size_t>::max() / sizeof(value_type);
  }

  // iterator begin() { return iterator(_array); }
  iterator begin() { return iterator(_array); }
  const_iterator cbegin() { return const_iterator(_array); }
  iterator end() { return iterator(_array + _size); }
  const_iterator cend() { return const_iterator(_array + _size); }

  reference front() { return *begin(); }
  const_reference front() const { return *cbegin(); }
  reference back() { return *(end() - 1); }
  const_reference back() const { return *(cend() - 1); }

  reference at(size_type pos) {
    if (_size <= pos) {
      throw ::std::out_of_range("");
    }
    return *(begin() + pos);
  }

  const_reference at(size_type pos) const {
    if (_size <= pos) {
      throw ::std::out_of_range("");
    }
    return *(cbegin() + pos);
  }

  T *data() { return _array; }
  const T *data() const { return _array; }

  void reserve(size_type size) {
    if (size <= _capacity) {
      return;
    }
    pointer newarr = Allocator_Traits::allocate(_alloc, size);
    _move_n(newarr, size);
  }
  void erase(const_iterator pos) {
    if (pos > end() || pos < begin()) {
      return;
    }
    if (pos == end()) {
      pop_back();
    }
    Allocator_Traits::destroy(_alloc, &(*pos));
    for (iterator it = pos; it != end() - 1; ++it) {
      *it = std::move(*(it + 1));
    }
    --_size;
  }

  iterator erase(const_iterator first, const_iterator last) {
    if (first > end() || first < begin() || last > end() || last < first) {
      return first;
    }

    if (first == last) {
      return first;
    }

    if (last == end()) {
      for (iterator it = first; it != last; ++it) {
        Allocator_Traits::destroy(_alloc, &(*it));
        --_size;
      }
      return end();
    }

    iterator new_end = std::copy(last, end(), first);

    for (iterator it = new_end; it != end(); ++it) {
      Allocator_Traits::destroy(_alloc, &(*it));
    }

    _size -= std::distance(first, last);

    return iterator(first);
  }

  iterator insert(iterator pos, const_reference value) { emplace(pos, value); }
  iterator insert(iterator pos, T &&value) {
    emplace(pos, std::move_if_noexcept(value));
  }

  template <typename... Args>
  iterator emplace(const_iterator pos, Args &&...args) {
    if (pos > end() || pos < begin()) {
      return pos;
    }

    if (pos == end()) {
      emplace_back(std::forward<Args>(args)...);
      return end();
    }
    size_type index = pos - begin();

    if (_capacity <= _size) {
      _reserve_n_emplace((_capacity == 0) ? 1 : _capacity * 2, index,
                         std::forward<Args>(args)...);
    } else {
      Allocator_Traits::construct(_alloc, _array + _size,
                                  std::move_if_noexcept(*(_array + _size - 1)));
      for (auto it = end() - 1; it != pos; --it) {
        *(it) = std::move(*(it - 1));
      }
      _place_into_memory(_array + index, std::forward<Args>(args)...);
    }

    ++_size;
    return begin() + index;
  }

  template <typename... Args>
  void emplace_back(Args &&...args) {
    if (_capacity <= _size) {
      _reserve_n_emplace_back((_capacity == 0) ? 1 : _capacity * 2,
                              std::forward<Args>(args)...);
    } else {
      _place_into_memory(_array + _size, std::forward<Args>(args)...);
    }
    ++_size;
  }

  void push_back(const_reference &value) { emplace_back(value); }
  void push_back(T &&value) { emplace_back(std::move(value)); }

  void shrink_to_fit() {
    pointer newarr = Allocator_Traits::allocate(_alloc, _size);
    _move_n(newarr, _size);
  }

  /* OPERATORS */
  s21_vector &operator=(s21_vector &&v) {
    this->swap(v);
    this->_alloc = std::move(v._alloc);
    return *this;
  }

  reference operator[](size_type pos) { return *(begin() + pos); }
  /* GETTERS */
  size_type size() { return _size; }
  size_type capacity() { return _capacity; }

  bool empty() const noexcept { return _size == 0; }

 private:
  pointer _array;
  size_type _size;
  size_type _capacity;
  allocator_type _alloc;

  void swap(s21_vector &v) {
    std::swap(_size, v._size);
    std::swap(_capacity, v._capacity);
    std::swap(_array, v._array);
  }

  void _destroy_elements(size_t size) {
    for (size_t i = 0; i < size; ++i) {
      Allocator_Traits::destroy(_alloc, _array + i);
    }
  }

  template <typename... Args>
  void _place_into_memory(pointer p, Args &&...args) {
    Allocator_Traits::construct(_alloc, p, std::forward<Args>(args)...);
  }
  template <typename... Args>
  void _reserve_n_emplace_back(size_type new_capacity, Args &&...args) {
    pointer newarr = Allocator_Traits::allocate(_alloc, new_capacity);
    _place_into_memory(newarr + _size, std::forward<Args>(args)...);
    _move_n(newarr, new_capacity);
  }
  template <typename... Args>
  void _reserve_n_emplace(size_type new_capacity, size_type &pos,
                          Args &&...args) {
    pointer newarr = Allocator_Traits::allocate(_alloc, new_capacity);
    _place_into_memory(newarr + pos, std::forward<Args>(args)...);
    _move_n_with_pos(newarr, pos, new_capacity);
  }
  void _move_n(pointer &newarr, size_type &new_capacity) {
    for (size_type i = 0; i < _size; ++i) {
      Allocator_Traits::construct(_alloc, newarr + i,
                                  std::move_if_noexcept(*(_array + i)));
      Allocator_Traits::destroy(_alloc, _array + i);
    }
    Allocator_Traits::deallocate(_alloc, _array, _capacity);
    _array = newarr;
    _capacity = new_capacity;
  }
  void _move_n_with_pos(pointer &newarr, size_type pos,
                        size_type new_capacity) {
    for (size_type i = 0; i < pos; ++i) {
      Allocator_Traits::construct(_alloc, newarr + i,
                                  std::move_if_noexcept(*(_array + i)));
      Allocator_Traits::destroy(_alloc, _array + i);
    }
    for (size_type i = pos + 1; i < _size + 1; ++i) {
      Allocator_Traits::construct(_alloc, newarr + i,
                                  std::move_if_noexcept(*(_array + i - 1)));
      Allocator_Traits::destroy(_alloc, _array + i - 1);
    }
    Allocator_Traits::deallocate(_alloc, _array, _capacity);
    _array = newarr;
    _capacity = new_capacity;
  }
};

}  // namespace s21_containers
#endif  // _CONTAINERS_S21_VECTOR_H
