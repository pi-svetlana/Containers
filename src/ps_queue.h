#ifndef CONTAINERS_SRC_PS_QUEUE_H_
#define CONTAINERS_SRC_PS_QUEUE_H_

#include "ps_deque.h"

namespace ps {
template <class T, class Container = ps::deque<T>>
class queue {
 public:
  using value_type = T;
  using reference = T&;
  using const_reference = const T&;
  using size_type = size_t;

  queue();
  explicit queue(std::initializer_list<value_type> const& items);
  queue(const queue& q);
  queue(queue&& q);
  ~queue() { deque_.clear(); }

  queue& operator=(const queue& other);
  queue& operator=(queue&& other);

  reference front();
  const_reference front() const;
  reference back();
  const_reference back() const;
  bool empty() const;
  size_type size() const;

  void push(const_reference value);
  void pop();
  void swap(queue& other) noexcept;

  template <class... Args>
  void insert_many_back(Args&&... args);

 private:
  Container deque_;
};
}  // namespace ps

template <class T, class Container>
ps::queue<T, Container>::queue() : deque_() {}

template <class T, class Container>
ps::queue<T, Container>::queue(std::initializer_list<value_type> const& items)
    : deque_(items) {}

template <class T, class Container>
ps::queue<T, Container>::queue(const queue& q) : deque_(q.deque_) {}

template <class T, class Container>
ps::queue<T, Container>::queue(queue&& q) : deque_(std::move(q.deque_)) {}

template <class T, class Container>
ps::queue<T, Container>& ps::queue<T, Container>::operator=(
    const queue& other) {
  deque_ = other.deque_;
  return *this;
}

template <class T, class Container>
ps::queue<T, Container>& ps::queue<T, Container>::operator=(queue&& other) {
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
typename ps::queue<T, Container>::reference ps::queue<T, Container>::front() {
  return deque_.front();
}

template <class T, class Container>
typename ps::queue<T, Container>::const_reference
ps::queue<T, Container>::front() const {
  return deque_.front();
}

template <class T, class Container>
typename ps::queue<T, Container>::reference ps::queue<T, Container>::back() {
  return deque_.back();
}

template <class T, class Container>
typename ps::queue<T, Container>::const_reference
ps::queue<T, Container>::back() const {
  return deque_.back();
}

template <class T, class Container>
bool ps::queue<T, Container>::empty() const {
  return deque_.empty();
}

template <class T, class Container>
typename ps::queue<T, Container>::size_type ps::queue<T, Container>::size()
    const {
  return deque_.size();
}

template <class T, class Container>
void ps::queue<T, Container>::push(const_reference value) {
  deque_.push_back(value);
}

template <class T, class Container>
void ps::queue<T, Container>::pop() {
  deque_.pop_front();
}

template <class T, class Container>
void ps::queue<T, Container>::swap(queue& other) noexcept {
  deque_.swap(other.deque_);
}

template <class T, class Container>
template <class... Args>
void ps::queue<T, Container>::insert_many_back(Args&&... args) {
  for (const auto& arg : {args...}) {
    deque_.push_back(arg);
  }
}

#endif  // CONTAINERS_SRC_PS_QUEUE_H_