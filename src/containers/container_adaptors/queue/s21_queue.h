#ifndef _CONTAINERS_S21_QUEUE_H
#define _CONTAINERS_S21_QUEUE_H

#include <initializer_list>
#include <utility>

#include "../../sequence_containers/list/s21_list.h"

namespace s21_containers {

template <typename T, typename Container = s21_containers::s21_list<T>>
class s21_queue {
 public:
  using container_type = Container;
  using value_type = typename Container::value_type;
  using size_type = typename Container::size_type;
  using reference = typename Container::reference;
  using const_reference = typename Container::const_reference;

  s21_queue() : _container() {}

  s21_queue(std::initializer_list<value_type> const& items)
      : _container(items) {}

  s21_queue(const s21_queue& q) : _container(q._container) {}

  s21_queue(s21_queue&& q) : _container(std::move(q._container)) {}

  s21_queue& operator=(const s21_queue& other) {
    if (this != &other) {
      _container = other._container;
    }
    return *this;
  }

  s21_queue& operator=(s21_queue&& other) noexcept {
    if (this != &other) {
      _container = std::move(other._container);
    }
    return *this;
  }

  ~s21_queue() {}

  reference front() { return _container.front(); }

  const_reference front() const { return _container.front(); }

  reference back() { return _container.back(); }

  const_reference back() const { return _container.back(); }

  bool empty() const { return _container.empty(); }

  size_type size() const { return _container.size(); }

  template <class... Args>
  decltype(auto) emplace(Args&&... args) {
    return _container.emplace_back(std::forward<Args>(args)...);
  }
  void push(const value_type& value) { _container.push_back(value); }

  void push(value_type&& value) { _container.push_back(std::move(value)); }

  void pop() { _container.pop_back(); }

  void swap(s21_queue& other) noexcept(std::is_nothrow_swappable_v<Container>) {
    using std::swap;
    swap(_container, other._container);
  }

 private:
  Container _container;
};
}  // namespace s21_containers
#endif  // _CONTAINERS_S21_QUEUE_H
