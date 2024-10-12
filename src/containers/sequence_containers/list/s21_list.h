#ifndef _CONTAINERS_S21_LIST_H
#define _CONTAINERS_S21_LIST_H

#include <algorithm>
#include <exception>
#include <iostream>
#include <limits>
#include <memory>
#include <utility>

namespace __detail {

struct _List_Node_Base {
  _List_Node_Base* prev;
  _List_Node_Base* next;

  _List_Node_Base() = default;

  static void _N_hook(_List_Node_Base*& first, _List_Node_Base*& second) {
    first->next = second;
    second->prev = first;
  }
  static void _N_insert_hook(_List_Node_Base*& first,
                             _List_Node_Base*& second) {
    // first->prev = second->prev;
    // first->next = second;
    // second->prev->next = first;
    // second->prev = first;
    _N_hook(second->prev, first);
    _N_hook(first, second);
  }
};
template <typename _Tp>
struct _List_Node : public _List_Node_Base {
  _Tp _value;
  _List_Node(const _Tp& val) : _List_Node_Base(), _value(val) {}

  _Tp* _L_valptr() { return std::addressof(_value); }
  _Tp const* _L_valptr() const { return std::addressof(_value); }
};
}  // namespace __detail

namespace __iterator {
template <typename T>
class ListIterator {
 public:
  using _Self = ListIterator<T>;
  using _Node = __detail::_List_Node<T>;
  using iterator_category = std::bidirectional_iterator_tag;
  using value_type = T;
  using difference_type = std::ptrdiff_t;
  using pointer = T*;
  using reference = T&;

  ListIterator() : _ptr() {}
  explicit ListIterator(__detail::_List_Node_Base* ptr) : _ptr(ptr) {}

  reference operator*() const noexcept {
    return *static_cast<_Node*>(_ptr)->_L_valptr();
  }
  pointer operator->() const noexcept {
    return static_cast<_Node*>(_ptr)->_L_valptr();
  }
  _Self _M_const_cast() const noexcept { return *this; }
  _Self& operator++() noexcept {
    _ptr = _ptr->next;
    return *this;
  }

  _Self operator++(int) noexcept {
    _Self __tmp = *this;
    _ptr = _ptr->next;
    return __tmp;
  }
  _Self& operator--() noexcept {
    _ptr = _ptr->prev;
    return *this;
  }

  _Self operator--(int) noexcept {
    _Self __tmp = *this;
    _ptr = _ptr->prev;
    return __tmp;
  }

  friend bool operator==(const _Self& __x, const _Self& __y) noexcept {
    return __x._ptr == __y._ptr;
  }

  friend bool operator!=(const _Self& __x, const _Self& __y) noexcept {
    return __x._ptr != __y._ptr;
  }

  __detail::_List_Node_Base* _ptr;
};

template <typename T>
class ListConstIterator {
 public:
  using _Self = ListConstIterator<T>;
  using _Node = const __detail::_List_Node<T>;
  using iterator = ListIterator<T>;
  using iterator_category = std::bidirectional_iterator_tag;
  using value_type = T;
  using difference_type = std::ptrdiff_t;
  using pointer = const T*;
  using reference = const T&;

  ListConstIterator() : _ptr() {}
  explicit ListConstIterator(const __detail::_List_Node_Base* ptr)
      : _ptr(ptr) {}

  reference operator*() const noexcept {
    return *static_cast<_Node*>(_ptr)->_L_valptr();
  }

  pointer operator->() const noexcept {
    return static_cast<_Node*>(_ptr)->_L_valptr();
  }

  ListConstIterator(const iterator& __x) noexcept : _ptr(__x._ptr) {}

  iterator _M_const_cast() const noexcept {
    return iterator(const_cast<__detail::_List_Node_Base*>(_ptr));
  }

  _Self& operator++() noexcept {
    _ptr = _ptr->next;
    return *this;
  }

  _Self operator++(int) noexcept {
    _Self __tmp = *this;
    _ptr = _ptr->next;
    return __tmp;
  }
  _Self& operator--() noexcept {
    _ptr = _ptr->prev;
    return *this;
  }

  _Self operator--(int) noexcept {
    _Self __tmp = *this;
    _ptr = _ptr->prev;
    return __tmp;
  }

  friend bool operator==(const _Self& __x, const _Self& __y) noexcept {
    return __x._ptr == __y._ptr;
  }

  friend bool operator!=(const _Self& __x, const _Self& __y) noexcept {
    return __x._ptr != __y._ptr;
  }
  const __detail::_List_Node_Base* _ptr;
};
}  // namespace __iterator

namespace s21_containers {
template <typename T, typename Allocator = std::allocator<T>>
class s21_list {
 public:
  using value_type = T;
  using reference = T&;
  using const_reference = const T&;
  using iterator = __iterator::ListIterator<T>;
  using const_iterator = __iterator::ListConstIterator<T>;
  using size_type = size_t;
  using NodeBase = __detail::_List_Node_Base;
  using Node = __detail::_List_Node<T>;
  using allocator_type = Allocator;
  using Allocator_Traits = std::allocator_traits<Allocator>;
  using pointer = typename std::allocator_traits<Allocator>::pointer;
  using const_pointer =
      typename std::allocator_traits<Allocator>::const_pointer;
  using node_allocator = typename std::allocator_traits<
      Allocator>::template rebind_alloc<__detail::_List_Node<T>>;
  using NodeAllocatorTraits = std::allocator_traits<node_allocator>;

  s21_list() : _fakeNode{&_fakeNode, &_fakeNode}, _size(0) {}

  explicit s21_list(size_type n) : _fakeNode{&_fakeNode, &_fakeNode}, _size(0) {
    for (size_t i = 0; i < n; ++i) emplace_back(T());
  }

  explicit s21_list(std::initializer_list<value_type> const& items)
      : _fakeNode{&_fakeNode, &_fakeNode}, _size(0) {
    for (auto begin = items.begin(), end = items.end(); begin != end; ++begin) {
      emplace_back(*begin);
    };
  }

  s21_list(const s21_list& other)
      : _fakeNode{&_fakeNode, &_fakeNode}, _size(0) {
    for (const auto& value : other) {
      emplace_back(value);
    }
  }

  s21_list(s21_list&& other) noexcept
      : _fakeNode{&_fakeNode, &_fakeNode},
        _size(other._size),
        _alloc(std::move(other._alloc)) {
    _move(other);
  }

  ~s21_list() { clear(); }

  s21_list& operator=(s21_list&& other) noexcept {
    if (this != &other) {
      clear();

      _size = other._size;
      _alloc = std::move(other._alloc);
      _move(other);
    }
    return *this;
  }

  void clear() {
    while (_fakeNode.next != &_fakeNode) {
      NodeBase* tmp = _fakeNode.next;
      _fakeNode.next = tmp->next;
      _remove_node(tmp);
    }
    _fakeNode.prev = &_fakeNode;
  }

  void push_back(const_reference value) { emplace_back(value); }
  void push_back(T&& value) { emplace_back(std::move(value)); }
  void pop_back() { erase(std::prev(end())); }

  template <typename... Args>
  reference emplace_back(Args&&... args) {
    return *this->emplace(const_iterator(end()), args...);
  }

  void push_front(const_reference value) { emplace_front(value); }
  void push_front(T&& value) { emplace_front(std::move(value)); }
  void pop_front() { erase(begin()); }

  iterator erase(const_iterator pos) {
    iterator it(pos++._M_const_cast());
    NodeBase::_N_hook(it._ptr->prev, it._ptr->next);
    _remove_node(it._ptr);
    return pos._M_const_cast();
  }

  void swap(s21_list& other) noexcept(
      Allocator_Traits::is_always_equal::value) {
    if (Allocator_Traits::propagate_on_container_swap::value) {
      std::swap(_alloc, other._alloc);
    }
    bool isCurrentEmpty = (_fakeNode.next == &_fakeNode);
    bool isOtherEmpty = (other._fakeNode.next == &other._fakeNode);
    if (!isCurrentEmpty && !isOtherEmpty) {
      std::swap(_fakeNode.next->prev, other._fakeNode.next->prev);
      std::swap(_fakeNode.prev->next, other._fakeNode.prev->next);
      std::swap(_fakeNode.next, other._fakeNode.next);
      std::swap(_fakeNode.prev, other._fakeNode.prev);
    } else if (!isCurrentEmpty) {
      _move_empty_nodes(other._fakeNode, _fakeNode);
    } else if (!isOtherEmpty) {
      _move_empty_nodes(_fakeNode, other._fakeNode);
    }

    std::swap(_size, other._size);
  }

  void splice(const_iterator pos, s21_list& other) {
    if (!other.empty()) {
      _size += other._size;
      iterator it(pos._M_const_cast());
      other._fakeNode.prev->next = it._ptr;
      other._fakeNode.next->prev = it._ptr->prev;
      it._ptr->prev->next = other._fakeNode.next;
      it._ptr->prev = other._fakeNode.prev;
      _init_node(other._fakeNode);
      other._size = 0;
    }
  }

  void splice(const_iterator pos, s21_list& other, const_iterator it) {
    if (pos != it) {
      iterator fit(pos._M_const_cast());
      iterator sit(it._M_const_cast());
      NodeBase::_N_hook(sit._ptr->prev, sit._ptr->next);
      --other._size;
      NodeBase::_N_hook(fit._ptr->prev, sit._ptr);
      NodeBase::_N_hook(sit._ptr, fit._ptr);
      ++_size;
    }
  }

  void splice(const_iterator pos, s21_list& other, const_iterator first,
              const_iterator last) {}

  template <typename Compare>
  void merge(s21_list& other, Compare comp) {
    if (this == &other) {
      return;
    }

    auto it1 = begin();
    auto it2 = other.begin();
    auto end1 = end();
    auto end2 = other.end();

    while (it1 != end1 && it2 != end2) {
      if (comp(*it2, *it1)) {
        auto next = it2;
        ++next;
        splice(it1, other, it2);
        it2 = next;
      } else {
        ++it1;
      }
    }

    if (it2 != end2) {
      splice(end1, other, it2, end2);
    }

    other.clear();
  }

  void merge(s21_list& other) { merge(other, std::less<value_type>()); }

  // void merge(s21_list&& other) {}

  template <typename... Args>
  reference emplace_front(Args&&... args) {
    return *this->emplace(const_iterator(begin()), args...);
  }

  template <typename... Args>
  iterator emplace(const_iterator pos, Args&&... args) {
    Node* newNode = NodeAllocatorTraits::allocate(_alloc, 1);
    try {
      NodeAllocatorTraits::construct(_alloc, newNode,
                                     std::forward<Args>(args)...);
    } catch (...) {
      NodeAllocatorTraits::deallocate(_alloc, newNode, 1);
      throw;
    }
    iterator it(pos._M_const_cast());
    NodeBase* rec_NodeBase = static_cast<NodeBase*>(newNode);
    NodeBase::_N_hook(it._ptr->prev, rec_NodeBase);
    NodeBase::_N_hook(rec_NodeBase, it._ptr);

    ++_size;

    return iterator(newNode);
  }

  iterator insert(const_iterator pos, const T& value) {
    return this->emplace(pos, value);
  }
  iterator insert(const_iterator pos, T&& value) {
    return this->emplace(pos, std::move(value));
  }

  size_type size() const { return _size; }
  bool empty() const { return _size == 0; }
  size_type max_size() const {
    return std::numeric_limits<size_type>::max() /
           sizeof(__detail::_List_Node<T>) / 2;
  }

  iterator begin() noexcept { return iterator(_fakeNode.next); }
  const_iterator begin() const noexcept {
    return const_iterator(_fakeNode.next);
  }
  const_iterator cbegin() const noexcept {
    return const_iterator(_fakeNode.next);
  }

  iterator end() noexcept { return iterator(&_fakeNode); }
  const_iterator end() const noexcept { return const_iterator(&_fakeNode); }
  const_iterator cend() const noexcept { return const_iterator(&_fakeNode); }

  reference front() { return *begin(); }
  const_reference front() const { return *cbegin(); }

  reference back() { return *std::prev(end()); }
  const_reference back() const { return *std::prev(cend()); }

 private:
  NodeBase _fakeNode;
  size_type _size;
  node_allocator _alloc;

  void _move(s21_list& other) {
    if (other._size > 0) {
      _fakeNode.next = other._fakeNode.next;
      _fakeNode.prev = other._fakeNode.prev;
      _init_n_p_nodes(_fakeNode);
      _init_node(other._fakeNode);
      other._size = 0;
    }
  }
  void _remove_node(NodeBase* tmp) {
    NodeAllocatorTraits::destroy(_alloc, static_cast<Node*>(tmp));
    NodeAllocatorTraits::deallocate(_alloc, static_cast<Node*>(tmp), 1);
    --_size;
  }

  void _init_node(NodeBase& node) { node = {&node, &node}; }

  void _init_n_p_nodes(NodeBase& node) {
    node.next->prev = node.prev->next = &node;
  }

  void _move_empty_nodes(NodeBase& first, NodeBase& second) {
    first.next = second.next;
    first.prev = second.prev;
    _init_n_p_nodes(first);
    _init_node(second);
  }
};
}  // namespace s21_containers
#endif  // _CONTAINERS_S21_LIST_H
