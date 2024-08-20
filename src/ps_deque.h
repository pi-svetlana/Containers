#ifndef CONTAINERS_SRC_PS_DEQUE_H_
#define CONTAINERS_SRC_PS_DEQUE_H_

namespace ps {
template <class T>
class deque {
 public:
  using value_type = T;
  using reference = T&;
  using const_reference = const T&;
  using size_type = size_t;

  deque();
  explicit deque(std::initializer_list<value_type> const& items);
  deque(const deque& s);
  deque(deque&& s);
  ~deque() { clear(); }

  deque& operator=(const deque& other);
  deque& operator=(deque&& other);

  reference front();
  const_reference front() const;
  reference back();
  const_reference back() const;
  bool empty() const;
  size_type size() const;
  void push_back(const T& value);
  void push_front(const T& value);
  void pop_back();
  void pop_front();
  void clear() noexcept;
  void swap(deque& other);

 private:
  struct Node {
    T data_;
    Node* next_;
    Node* prev_;

    Node(T data) : data_(data), next_(nullptr), prev_(nullptr) {}
    ~Node() {}
  };

  struct LinkedList {
    size_type size_ = 0;
    Node* head_ = nullptr;
    Node* tail_ = nullptr;
  };

  LinkedList list_;
};
}  // namespace ps

template <class T>
ps::deque<T>::deque() {}

template <class T>
ps::deque<T>::deque(std::initializer_list<value_type> const& items) {
  for (auto it = items.begin(); it != items.end(); ++it) {
    push_back(*it);
  }
}

template <class T>
ps::deque<T>::deque(const deque& s) : deque() {
  Node* cur = s.list_.head_;
  while (cur) {
    push_back(cur->data_);
    cur = cur->next_;
  }
}

template <class T>
ps::deque<T>::deque(deque&& s) {
  list_.size_ = s.list_.size_;
  list_.head_ = s.list_.head_;
  list_.tail_ = s.list_.tail_;
  s.list_.size_ = 0;
  s.list_.head_ = nullptr;
  s.list_.tail_ = nullptr;
}

template <class T>
ps::deque<T>& ps::deque<T>::operator=(const deque& other) {
  if (this != &other) {
    while (!empty()) {
      pop_front();
    }
    Node* cur = other.list_.head_;
    while (cur) {
      push_back(cur->data_);
      cur = cur->next_;
    }
  }
  return *this;
}

template <class T>
ps::deque<T>& ps::deque<T>::operator=(deque&& other) {
  if (this != &other) {
    while (!empty()) {
      pop_front();
    }
    list_.size_ = other.list_.size_;
    list_.head_ = other.list_.head_;
    list_.tail_ = other.list_.tail_;
    other.list_.size_ = 0;
    other.list_.head_ = nullptr;
    other.list_.tail_ = nullptr;
  }
  return *this;
}

template <class T>
typename ps::deque<T>::reference ps::deque<T>::front() {
  return list_.head_->data_;
}

template <class T>
typename ps::deque<T>::const_reference ps::deque<T>::front() const {
  return list_.head_->data_;
}

template <class T>
typename ps::deque<T>::reference ps::deque<T>::back() {
  return list_.tail_->data_;
}

template <class T>
typename ps::deque<T>::const_reference ps::deque<T>::back() const {
  return list_.tail_->data_;
}

template <class T>
bool ps::deque<T>::empty() const {
  return list_.size_ == 0;
}

template <class T>
typename ps::deque<T>::size_type ps::deque<T>::size() const {
  return list_.size_;
}

template <class T>
void ps::deque<T>::push_back(const T& value) {
  Node* tmp = new Node(value);
  tmp->prev_ = list_.tail_;
  tmp->next_ = nullptr;
  if (list_.tail_) list_.tail_->next_ = tmp;
  list_.tail_ = tmp;
  if (!list_.head_) list_.head_ = tmp;
  ++list_.size_;
}

template <class T>
void ps::deque<T>::push_front(const T& value) {
  Node* tmp = new Node(value);
  tmp->prev_ = nullptr;
  tmp->next_ = list_.head_;
  if (list_.head_) list_.head_->prev_ = tmp;
  list_.head_ = tmp;
  if (!list_.tail_) list_.tail_ = tmp;
  ++list_.size_;
}

template <class T>
void ps::deque<T>::pop_back() {
  if (list_.tail_) {
    Node* tmp = list_.tail_;
    list_.tail_ = list_.tail_->prev_;
    delete tmp;
    if (list_.tail_)
      list_.tail_->next_ = nullptr;
    else
      list_.head_ = nullptr;
    --list_.size_;
  }
}

template <class T>
void ps::deque<T>::pop_front() {
  if (list_.head_) {
    Node* tmp = list_.head_;
    list_.head_ = list_.head_->next_;
    delete tmp;
    if (list_.head_)
      list_.head_->prev_ = nullptr;
    else
      list_.tail_ = nullptr;
    --list_.size_;
  }
}

template <class T>
void ps::deque<T>::clear() noexcept {
  while (!empty()) {
    pop_front();
  }
  list_.size_ = 0;
  list_.head_ = nullptr;
  list_.tail_ = nullptr;
}

template <class T>
void ps::deque<T>::swap(deque& other) {
  std::swap(list_.size_, other.list_.size_);
  std::swap(list_.head_, other.list_.head_);
  std::swap(list_.tail_, other.list_.tail_);
}

#endif  // CONTAINERS_SRC_PS_DEQUE_H_