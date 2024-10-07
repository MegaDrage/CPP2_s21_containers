#ifndef _CONTAINERS_S21_VECTOR_ITERATOR_H
#define _CONTAINERS_S21_VECTOR_ITERATOR_H

#include <iterator>
#include "s21_vector.h"

namespace s21_containers {
template <typename T, typename Allocator>
class s21_vector<T, Allocator>::VectorIterator {
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
    iterator tmp = *this;
    ++ptr;
    return tmp;
  }

  VectorIterator &operator--() {
    --ptr;
    return *this;
  }
  VectorIterator operator--(int) {
    iterator tmp = *this;
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
    return iterator(ptr + n);
  }
  VectorIterator operator-(difference_type n) const {
    return iterator(ptr - n);
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
class s21_vector<T, Allocator>::VectorConstIterator {
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
    const_iterator tmp = *this;
    ++ptr;
    return tmp;
  }

  VectorConstIterator &operator--() {
    --ptr;
    return *this;
  }
  VectorConstIterator operator--(int) {
    const_iterator tmp = *this;
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
    return const_iterator(ptr + n);
  }
  VectorConstIterator operator-(difference_type n) const {
    return const_iterator(ptr - n);
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

} // namespace s21_containers

#endif // _CONTAINERS_S21_VECTOR_ITERATOR_H
