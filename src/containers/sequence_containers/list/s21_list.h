#ifndef _CONTAINERS_S21_LIST_H
#define _CONTAINERS_S21_LIST_H

#include <memory>

template <typename T, typename Allocator = std::allocator<T>>
class s21_list {
 public:
  // class ListIterator;
  using value_type = T;
  using reference = T &;
  using const_reference = const T &;
  // using iterator = ListIterator<T>;
  // using const_iterator = ListConstIterator<T>;
  using size_type = size_t;
  using allocator_type = Allocator;
  using Allocator_Traits = std::allocator_traits<Allocator>;
  using pointer = typename std::allocator_traits<Allocator>::pointer;
  using const_pointer =
      typename std::allocator_traits<Allocator>::const_pointer;

 private:
};
#endif  // _CONTAINERS_S21_LIST_H
