#ifndef _CONTAINERS_S21_ASSOCIATIVE_CONTAINER_H
#define _CONTAINERS_S21_ASSOCIATIVE_CONTAINER_H

#include <iostream>
#include <limits>

namespace s21_containers {

template <typename T>
class S21_ASSOCIATIVE_CONTAINER {
 public:
  using value_type = T;
  using reference = T &;
  using const_reference = const T &;
  using size_type = size_t;
};

}  // namespace s21_containers

#endif  // _CONTAINERS_S21_ASSOCIATIVE_CONTAINER_H
