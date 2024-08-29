#ifndef CONTAINERS_SRC_PS_STACK_H_
#define CONTAINERS_SRC_PS_STACK_H_

#include "ps_deque.h"

namespace ps {
template <class T, class Container = ps::deque<T>>
class stack {
 public:
  using value_type = T;
  using reference = T&;
  using const_reference = const T&;
  using size_type = size_t;

  stack();
  explicit stack(std::initializer_list<value_type> const& items);
  stack(const stack& s);
  stack(stack&& s);
  ~stack() { deque_.clear(); }

  stack& operator=(const stack& other);
  stack& operator=(stack&& other);

  reference top();
  const_reference top() const;
  bool empty() const;
  size_type size() const;

  void push(const_reference value);
  void pop();
  void swap(stack& other);

  template <class... Args>
  void insert_many_front(Args&&... args);

 private:
  Container deque_;
};
}  // namespace ps

template <class T, class Container>
ps::stack<T, Container>::stack() : deque_() {}

template <class T, class Container>
ps::stack<T, Container>::stack(std::initializer_list<value_type> const& items)
    : deque_(items) {}

template <class T, class Container>
ps::stack<T, Container>::stack(const stack& s) : deque_(s.deque_) {}

template <class T, class Container>
ps::stack<T, Container>::stack(stack&& s) : deque_(std::move(s.deque_)) {}

template <class T, class Container>
ps::stack<T, Container>& ps::stack<T, Container>::operator=(
    const stack& other) {
  deque_ = other.deque_;
  return *this;
}

template <class T, class Container>
ps::stack<T, Container>& ps::stack<T, Container>::operator=(stack&& other) {
  if (this != &other) {
    while (!empty()) {
      deque_.pop_front();
    }
    deque_ = other.deque_;
    other.deque_.clear();
  }
  return *this;
}

template <class T, class Container>
typename ps::stack<T, Container>::reference ps::stack<T, Container>::top() {
  return deque_.back();
}

template <class T, class Container>
typename ps::stack<T, Container>::const_reference ps::stack<T, Container>::top()
    const {
  return deque_.back();
}

template <class T, class Container>
bool ps::stack<T, Container>::empty() const {
  return deque_.empty();
}

template <class T, class Container>
typename ps::stack<T, Container>::size_type ps::stack<T, Container>::size()
    const {
  return deque_.size();
}

template <class T, class Container>
void ps::stack<T, Container>::push(const_reference value) {
  deque_.push_back(value);
}

template <class T, class Container>
void ps::stack<T, Container>::pop() {
  deque_.pop_back();
}

template <class T, class Container>
void ps::stack<T, Container>::swap(stack& other) {
  deque_.swap(other.deque_);
}

template <class T, class Container>
template <class... Args>
void ps::stack<T, Container>::insert_many_front(Args&&... args) {
  for (const auto& arg : {args...}) {
    deque_.push_front(arg);
  }
}

#endif  // CONTAINERS_SRC_PS_STACK_H_