#ifndef CONTAINERS_SRC_PS_LIST_H_
#define CONTAINERS_SRC_PS_LIST_H_

#include <iostream>

namespace ps {
template <class T, class Allocator = std::allocator<T> >
class list {
 public:
  struct Node;
  class ListIterator;
  class ListConstIterator;
  class ListIterator {
    friend ps::list<T, Allocator>;

   public:
    using node_type = Node;
    ListIterator() {}
    ListIterator(node_type* node) : node_(node) {}

    const T& operator*() const { return node_->value_; }
    ListIterator& operator++() {
      node_ = node_->next_;
      return *this;
    }

    ListIterator& operator--() {
      node_ = node_->prev_;
      return *this;
    }

    ListIterator operator++(int) {
      ListIterator tmp(*this);
      ++(*this);
      return tmp;
    }

    ListIterator operator--(int) {
      ListIterator tmp(*this);
      --(*this);
      return tmp;
    }

    bool operator==(const ListIterator& other) const noexcept {
      return other.node_ == node_;
    }

    bool operator!=(const ListIterator& other) const noexcept {
      return !(other.node_ == node_);
    }

    bool operator==(const ListConstIterator& other) const noexcept {
      return other.node_ == node_;
    }
    bool operator!=(const ListConstIterator& other) const noexcept {
      return !(other.node_ == node_);
    }

    ~ListIterator() { node_ = nullptr; }

   private:
    Node* node_;
  };

  class ListConstIterator {
    friend ps::list<T, Allocator>;

   public:
    using node_type = Node;

    ListConstIterator() {}
    explicit ListConstIterator(node_type* node) { node_ = node; }

    const T& operator*() const { return node_->value_; }

    ListConstIterator& operator++() {
      node_ = node_->next_;
      return *this;
    }

    ListConstIterator& operator--() {
      node_ = node_->prev_;
      return *this;
    }

    ListConstIterator operator++(int) {
      ListConstIterator tmp(*this);
      ++(*this);
      return tmp;
    }

    ListConstIterator operator--(int) {
      ListConstIterator tmp(*this);
      --(*this);
      return tmp;
    }

    bool operator==(const ListConstIterator& other) const noexcept {
      return other.node_ == node_;
    }

    bool operator!=(const ListConstIterator& other) const noexcept {
      return !(other.node_ == node_);
    }

    bool operator==(const ListIterator& other) const noexcept {
      return other.node_ == node_;
    }
    bool operator!=(const ListIterator& other) const noexcept {
      return !(other.node_ == node_);
    }

    ~ListConstIterator() { node_ = nullptr; }

   private:
    Node* node_;
  };

  using value_type = T;
  using reference = T&;
  using const_reference = const T&;
  using iterator = ListIterator;
  using const_iterator = ListConstIterator;
  using size_type = size_t;
  using allocator_type = Allocator;
  using rebind_allocator_type =
      typename std::allocator_traits<Allocator>::template rebind_alloc<Node>;
  /**
   * rebind_allocator_type - новый тип аллокатора, который переопределяет
   * тип выделения памяти для объектов типа Node.
   *
   * Он использует стандартный шаблонный класс std::allocator_traits для
   * получения типа аллокатора Allocator, а затем вызывает его метод
   * rebind_alloc для создания нового типа аллокатора, который может выделять
   * память для объектов типа Node.
   */
  using node_allocator =
      typename std::allocator_traits<Allocator>::template rebind_traits<Node>;
  /**
   * Тип node_allocator - переопределение типа Allocator для выделения
   * памяти для объектов типа Node.
   *
   * std::allocator_traits - утилита, которая предоставляет типы и функции
   * для работы с аллокаторами. rebind_traits - это функция-член
   * allocator_traits, которая создает новый аллокатор, переопределяя тип
   * выделяемых объектов на указанный тип.
   */
  using list_type = ps::list<value_type, allocator_type>;

  list();
  list(size_type count);
  list(std::initializer_list<T> init);
  list(const list& other);
  list(list&& other);
  ~list() { clear(); }

  list& operator=(const list_type& other);
  list& operator=(list_type&& other) noexcept;

  reference front();  // Reference to the first element
  const_reference front() const;
  reference back();  // Reference to the last element
  const_reference back() const;

  iterator begin() noexcept;  // Iterator to the first element
  const_iterator begin() const noexcept;
  const_iterator cbegin() const noexcept;

  iterator end() noexcept;  // Iterator to the element following the last
                            // element
  const_iterator end() const noexcept;
  const_iterator cend() const noexcept;

  bool empty()
      const noexcept;  // true if the container is empty, false otherwise
  size_type size() const noexcept;  // The number of elements in the container
  size_type max_size() const noexcept;  // Maximum number of elements

  void clear() noexcept;
  iterator insert(const_iterator pos,
                  const T& value);     // Inserts value before pos
  iterator erase(const_iterator pos);  // Removes the element at pos

  void push_back(
      const T& value);  // The new element is initialized as a copy of value
  void pop_back();
  void push_front(const T& value);
  void pop_front();
  void swap(list& other) noexcept;
  void merge(list& other);
  void splice(const_iterator pos, list& other);
  void reverse() noexcept;
  void unique();
  void sort();

  template <class... Args>
  iterator insert_many(const_iterator pos, Args&&... args);

  template <class... Args>
  void insert_many_back(Args&&... args);

  template <class... Args>
  void insert_many_front(Args&&... args);

  struct Node {
    Node* next_;
    Node* prev_;
    T value_;

    Node();
    ~Node();
  };

 private:
  Node* head_;
  Node* tail_;
  Node* fake_node_;
  size_type size_;
  rebind_allocator_type allocator_;

  Node* allocate_node();
  void deallocate_node(Node* ptr) noexcept;
  void quick_sort(iterator first, iterator last, size_type size);
};
}  // namespace ps

template <class T, class Allocator>
ps::list<T, Allocator>::Node::Node() : next_(nullptr), prev_(nullptr) {}

template <class T, class Allocator>
ps::list<T, Allocator>::Node::~Node() {
  next_ = nullptr;
  prev_ = nullptr;
}

template <class T, class Allocator>
typename ps::list<T, Allocator>::Node* ps::list<T, Allocator>::allocate_node() {
  Node* node = nullptr;
  node = node_allocator::allocate(allocator_, 1);
  node_allocator::construct(allocator_, node);
  return node;
}

template <class T, class Allocator>
void ps::list<T, Allocator>::deallocate_node(Node* ptr) noexcept {
  node_allocator::destroy(allocator_, ptr);
  node_allocator::deallocate(allocator_, ptr, 1);
}

template <class T, class Allocator>
ps::list<T, Allocator>::list() : allocator_() {
  size_ = 0;
  head_ = nullptr;
  tail_ = nullptr;
  fake_node_ = nullptr;
}

template <class T, class Allocator>
ps::list<T, Allocator>::list(size_type count) : list() {
  while (count > 0) {
    push_back(value_type());
    --count;
  }
}

template <class T, class Allocator>
ps::list<T, Allocator>::list(std::initializer_list<T> init) : list() {
  for (auto iter = init.begin(); iter != init.end(); ++iter) {
    push_back(*iter);
  }
}

template <class T, class Allocator>
ps::list<T, Allocator>::list(const list& other) : list() {
  Node* tmp = other.head_;
  while (tmp != other.fake_node_) {
    push_back(tmp->value_);
    tmp = tmp->next_;
  }
}

template <class T, class Allocator>
ps::list<T, Allocator>::list(list&& other) {
  size_ = other.size_;
  head_ = other.head_;
  tail_ = other.tail_;
  fake_node_ = other.fake_node_;
  other.size_ = 0;
  other.head_ = nullptr;
  other.tail_ = nullptr;
  other.fake_node_ = nullptr;
}

template <class T, class Allocator>
ps::list<T, Allocator>& ps::list<T, Allocator>::operator=(
    const list_type& other) {
  if (this != &other) {
    clear();
    Node* tmp = other.head_;
    while (tmp != other.fake_node_) {
      push_back(tmp->value_);
      tmp = tmp->next_;
    }
  }
  return *this;
}

template <class T, class Allocator>
ps::list<T, Allocator>& ps::list<T, Allocator>::operator=(
    list_type&& other) noexcept {
  if (this != &other) {
    clear();
    head_ = other.head_;
    tail_ = other.tail_;
    size_ = other.size_;
    fake_node_ = other.fake_node_;
    other.head_ = nullptr;
    other.tail_ = nullptr;
    other.fake_node_ = nullptr;
    other.size_ = 0;
  }
  return *this;
}

template <class T, class Allocator>
typename ps::list<T, Allocator>::reference ps::list<T, Allocator>::front() {
  return head_->value_;
}

template <class T, class Allocator>
typename ps::list<T, Allocator>::const_reference ps::list<T, Allocator>::front()
    const {
  return head_->value_;
}

template <class T, class Allocator>
typename ps::list<T, Allocator>::reference ps::list<T, Allocator>::back() {
  return tail_->value_;
}

template <class T, class Allocator>
typename ps::list<T, Allocator>::const_reference ps::list<T, Allocator>::back()
    const {
  return tail_->value_;
}

template <class T, class Allocator>
typename ps::list<T, Allocator>::iterator
ps::list<T, Allocator>::begin() noexcept {
  return ListIterator(head_);
}

template <class T, class Allocator>
typename ps::list<T, Allocator>::const_iterator ps::list<T, Allocator>::begin()
    const noexcept {
  return ListConstIterator(head_);
}

template <class T, class Allocator>
typename ps::list<T, Allocator>::const_iterator ps::list<T, Allocator>::cbegin()
    const noexcept {
  return ListConstIterator(head_);
}

template <class T, class Allocator>
typename ps::list<T, Allocator>::iterator
ps::list<T, Allocator>::end() noexcept {
  return ListIterator(fake_node_);
}

template <class T, class Allocator>
typename ps::list<T, Allocator>::const_iterator ps::list<T, Allocator>::end()
    const noexcept {
  return ListConstIterator(fake_node_);
}

template <class T, class Allocator>
typename ps::list<T, Allocator>::const_iterator ps::list<T, Allocator>::cend()
    const noexcept {
  return ListConstIterator(fake_node_);
}

template <class T, class Allocator>
bool ps::list<T, Allocator>::empty() const noexcept {
  return size_ == 0;
}

template <class T, class Allocator>
typename ps::list<T, Allocator>::size_type ps::list<T, Allocator>::size()
    const noexcept {
  return size_;
}

template <class T, class Allocator>
typename ps::list<T, Allocator>::size_type ps::list<T, Allocator>::max_size()
    const noexcept {
  return std::numeric_limits<size_type>::max() / sizeof(Node);
}

template <class T, class Allocator>
void ps::list<T, Allocator>::clear() noexcept {
  if (size_ == 0) {
    return;
  }
  while (size_ > 0) {
    pop_back();
  }
  deallocate_node(fake_node_);
  head_ = nullptr;
  tail_ = nullptr;
  fake_node_ = nullptr;
  size_ = 0;
}

template <class T, class Allocator>
typename ps::list<T, Allocator>::iterator ps::list<T, Allocator>::insert(
    const_iterator pos, const T& value) {
  ListIterator it = begin();
  if (pos != begin() && pos != end()) {
    Node* new_node = allocate_node();
    new_node->value_ = value;
    while (it != pos) {
      ++it;
    }
    Node* cur = it.node_;
    Node* back = cur->prev_;
    cur->prev_ = new_node;
    back->next_ = new_node;
    new_node->next_ = cur;
    new_node->prev_ = back;
    ++size_;
    --it;
  } else if (pos == begin()) {
    push_front(value);
    it = begin();
  } else {
    push_back(value);
    it = end();
  }
  return it;
}

template <class T, class Allocator>
typename ps::list<T, Allocator>::iterator ps::list<T, Allocator>::erase(
    const_iterator pos) {
  ListIterator it = begin();
  if (pos != begin() && pos != tail_) {
    while (it.node_ != pos.node_) {
      ++it;
    }
    Node* cur = it.node_;
    Node* back = cur->prev_;
    Node* next = cur->next_;
    back->next_ = next;
    next->prev_ = back;
    it.node_ = next;
    deallocate_node(cur);
    cur = nullptr;
    --size_;
  } else if (pos == begin()) {
    pop_front();
    it = begin();
  } else {
    pop_back();
    it = end();
  }
  return it;
}

template <class T, class Allocator>
void ps::list<T, Allocator>::push_back(const T& value) {
  Node* new_node = allocate_node();
  new_node->value_ = value;
  if (head_) {
    new_node->prev_ = tail_;
    tail_->next_ = new_node;
    tail_ = tail_->next_;
    tail_->next_ = fake_node_;
    fake_node_->prev_ = tail_;
  } else {
    head_ = new_node;
    tail_ = new_node;
    fake_node_ = allocate_node();
    head_->prev_ = fake_node_;
    tail_->next_ = fake_node_;
    fake_node_->next_ = head_;
    fake_node_->prev_ = tail_;
  }
  ++size_;
}

template <class T, class Allocator>
void ps::list<T, Allocator>::pop_back() {
  Node* tmp = tail_;
  tail_ = tail_->prev_;
  tail_->next_ = fake_node_;
  fake_node_->prev_ = tail_;
  deallocate_node(tmp);
  --size_;
}

template <class T, class Allocator>
void ps::list<T, Allocator>::push_front(const T& value) {
  Node* new_node = allocate_node();
  new_node->value_ = value;
  if (head_) {
    head_->prev_ = new_node;
    new_node->next_ = head_;
    head_ = head_->prev_;
    head_->prev_ = fake_node_;
    fake_node_->next_ = head_;
  } else {
    head_ = new_node;
    tail_ = new_node;
    fake_node_ = allocate_node();
    head_->prev_ = fake_node_;
    tail_->next_ = fake_node_;
    fake_node_->next_ = head_;
    fake_node_->prev_ = tail_;
  }
  ++size_;
}

template <class T, class Allocator>
void ps::list<T, Allocator>::pop_front() {
  Node* tmp = head_;
  head_ = head_->next_;
  head_->prev_ = fake_node_;
  fake_node_->next_ = head_;
  deallocate_node(tmp);
  --size_;
}

template <class T, class Allocator>
void ps::list<T, Allocator>::swap(list& other) noexcept {
  if (this != &other) {
    std::swap(size_, other.size_);
    std::swap(head_, other.head_);
    std::swap(tail_, other.tail_);
    std::swap(fake_node_, other.fake_node_);
  }
}

template <class T, class Allocator>
void ps::list<T, Allocator>::merge(list& other) {
  ListConstIterator it_this = cbegin();
  ListConstIterator it_other = other.cbegin();
  while (it_this != cend() && it_other != other.cend()) {
    if (it_other.node_->value_ < it_this.node_->value_) {
      insert(it_this, *it_other);
      ++it_other;
    } else {
      ++it_this;
    }
  }
  while (it_other != other.cend()) {
    insert(it_this, *it_other);
    ++it_other;
  }
  other.clear();
}

template <class T, class Allocator>
void ps::list<T, Allocator>::splice(const_iterator pos, list& other) {
  for (iterator it = other.begin(); it != other.end(); ++it) {
    insert(pos, *it);
  }
}

template <class T, class Allocator>
void ps::list<T, Allocator>::reverse() noexcept {
  if (size_ > 0) {
    ListIterator lhs = begin();
    ListIterator rhs = --end();
    for (size_type i = 0; i < size() / 2; ++i) {
      std::swap(lhs.node_->value_, rhs.node_->value_);
      ++lhs;
      --rhs;
    }
  }
}

template <class T, class Allocator>
void ps::list<T, Allocator>::unique() {
  ListIterator begin_it = begin();
  ListIterator end_it = end();
  ListIterator back_it = begin_it;
  ++begin_it;
  while (begin_it != end_it) {
    if (*begin_it == *back_it) {
      ListConstIterator removed{begin_it.node_};
      erase(removed);
      begin_it = back_it;
    } else {
      ++back_it;
    }
    ++begin_it;
  }
}

template <class T, class Allocator>
void ps::list<T, Allocator>::sort() {
  quick_sort(begin(), --end(), size_);
}

template <class T, class Allocator>
void ps::list<T, Allocator>::quick_sort(ListIterator first, ListIterator last,
                                        size_type size) {
  if (first != last && size > 1) {
    ListIterator pivot_it = first;
    ListIterator lhs = first;
    ListIterator rhs = last;
    size_type shift = 0;
    ++pivot_it;
    value_type pivot = *pivot_it;
    shift = 0;
    while (true) {
      while (*lhs < pivot && lhs != rhs) {
        ++lhs;
        ++shift;
      }
      while (*rhs >= pivot && rhs != lhs) --rhs;
      if (lhs == rhs) {
        break;
      }
      std::swap(lhs.node_->value_, rhs.node_->value_);
    }
    ListIterator next_it = lhs;
    size_type next_size_lhs = shift;
    quick_sort(first, --next_it, next_size_lhs);
    size_type next_size_rhs = size - shift;
    quick_sort(next_it, last, next_size_rhs);
  }
}

template <class T, class Allocator>
template <class... Args>
typename ps::list<T, Allocator>::iterator ps::list<T, Allocator>::insert_many(
    const_iterator pos, Args&&... args) {
  iterator it{pos.node_};
  for (const auto& arg : {args...}) {
    it = insert(const_iterator{it.node_}, arg);
  }
  return it;
}

template <class T, class Allocator>
template <class... Args>
void ps::list<T, Allocator>::insert_many_back(Args&&... args) {
  for (const auto& arg : {args...}) {
    push_back(arg);
  }
}

template <class T, class Allocator>
template <class... Args>
void ps::list<T, Allocator>::insert_many_front(Args&&... args) {
  for (const auto& arg : {args...}) {
    push_front(arg);
  }
}

#endif  // CONTAINERS_SRC_PS_LIST_H_