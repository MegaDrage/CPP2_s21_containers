#ifndef _CONTAINERS_S21_SET_H
#define _CONTAINERS_S21_SET_H

#include <functional>
#include <memory>

namespace s21_containers {

template <class Key, class Compare = std::less<Key>,
          class Allocator = std::allocator<Key>>
class s21_set;
}
#endif  // _CONTAINERS_S21_SET_H
