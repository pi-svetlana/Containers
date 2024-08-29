#ifndef CONTAINERS_SRC_PS_VECTOR_H_
#define CONTAINERS_SRC_PS_VECTOR_H_

namespace ps {
template <class T>
class vector {
 public:
  using value_type = T;
  using reference = T&;
  using const_reference = const T&;
  using iterator = T*;
  using const_iterator = const T*;
  using size_type = size_t;

  vector();
  explicit vector(size_type n);
  explicit vector(std::initializer_list<value_type> const& items);
  vector(const vector& v);
  vector(vector&& v) noexcept;
  ~vector() { delete[] data_; }

  vector& operator=(const vector& other);
  vector& operator=(vector&& other) noexcept;

  reference at(size_type pos);
  const_reference at(size_type pos) const;

  reference operator[](size_type pos);
  const_reference operator[](size_type pos) const;

  const_reference front();
  const_reference front() const;
  const_reference back();
  const_reference back() const;
  iterator data() noexcept;
  const_iterator data() const noexcept;

  iterator begin() noexcept;
  const_iterator begin() const noexcept;
  const_iterator cbegin() const noexcept;
  iterator end() noexcept;
  const_iterator end() const noexcept;
  const_iterator cend() const noexcept;

  bool empty() const noexcept;
  size_type size() const noexcept;
  size_type max_size() const noexcept;
  void reserve(size_type new_cap);
  size_type capacity() const noexcept;
  void shrink_to_fit();

  void clear() noexcept;
  iterator insert(const_iterator pos, const T& value);
  iterator erase(const_iterator pos);
  void push_back(const_reference value);
  void pop_back();
  void swap(vector& other) noexcept;

  template <class... Args>
  iterator insert_many(const_iterator pos, Args&&... args);

  template <class... Args>
  void insert_many_back(Args&&... args);

 private:
  size_type size_ = 0;
  size_type capacity_ = 0;
  T* data_ = nullptr;
};
}  // namespace ps

template <class T>
ps::vector<T>::vector() {}

template <class T>
ps::vector<T>::vector(size_type n) {
  size_ = n;
  capacity_ = n;
  data_ = nullptr;
  if (size_ > 0) {
    data_ = new T[capacity_];
  }
}

template <class T>
ps::vector<T>::vector(std::initializer_list<value_type> const& items)
    : size_(items.size()), capacity_(items.size()), data_(new T[items.size()]) {
  std::copy(items.begin(), items.end(), data_);
}

template <class T>
ps::vector<T>::vector(const vector& v) {
  size_ = v.size_;
  capacity_ = v.capacity_;
  data_ = nullptr;
  if (size_ > 0) {
    data_ = new T[capacity_];
  }
  std::copy(v.begin(), v.end(), data_);
}

template <class T>
ps::vector<T>::vector(vector&& v) noexcept {
  size_ = std::exchange(v.size_, 0);
  capacity_ = std::exchange(v.capacity_, 0);
  data_ = std::exchange(v.data_, nullptr);
}

template <class T>
ps::vector<T>& ps::vector<T>::operator=(const vector& other) {
  if (this != &other) {
    delete[] data_;
    if (other.size_ > 0) {
      data_ = new T[other.capacity_];
      std::copy(other.begin(), other.end(), data_);
    }
    size_ = other.size_;
    capacity_ = other.capacity_;
  }
  return *this;
}

template <class T>
ps::vector<T>& ps::vector<T>::operator=(vector&& other) noexcept {
  size_ = std::exchange(other.size_, 0);
  capacity_ = std::exchange(other.capacity_, 0);
  data_ = std::exchange(other.data_, nullptr);
  return *this;
}

template <class T>
typename ps::vector<T>::reference ps::vector<T>::operator[](size_type pos) {
  return data_[pos];
}

template <class T>
typename ps::vector<T>::const_reference ps::vector<T>::operator[](
    size_type pos) const {
  return data_[pos];
}

template <class T>
typename ps::vector<T>::reference ps::vector<T>::at(size_type pos) {
  if (pos >= size_) {
    throw std::out_of_range("Out of range");
  }
  return data_[pos];
}

template <class T>
typename ps::vector<T>::const_reference ps::vector<T>::at(size_type pos) const {
  if (pos >= size_) {
    throw std::out_of_range("Out of range");
  }
  return data_[pos];
}

template <class T>
typename ps::vector<T>::const_reference ps::vector<T>::front() {
  return data_[0];
}

template <class T>
typename ps::vector<T>::const_reference ps::vector<T>::front() const {
  return data_[0];
}

template <class T>
typename ps::vector<T>::const_reference ps::vector<T>::back() {
  return data_[size_ - 1];
}

template <class T>
typename ps::vector<T>::const_reference ps::vector<T>::back() const {
  return data_[size_ - 1];
}

template <class T>
typename ps::vector<T>::iterator ps::vector<T>::data() noexcept {
  return data_;
}

template <class T>
typename ps::vector<T>::const_iterator ps::vector<T>::data() const noexcept {
  return data_;
}

template <class T>
typename ps::vector<T>::iterator ps::vector<T>::begin() noexcept {
  return data_;
}

template <class T>
typename ps::vector<T>::const_iterator ps::vector<T>::begin() const noexcept {
  return data_;
}

template <class T>
typename ps::vector<T>::const_iterator ps::vector<T>::cbegin() const noexcept {
  return data_;
}

template <class T>
typename ps::vector<T>::iterator ps::vector<T>::end() noexcept {
  return data_ + size_;
}

template <class T>
typename ps::vector<T>::const_iterator ps::vector<T>::end() const noexcept {
  return data_ + size_;
}

template <class T>
typename ps::vector<T>::const_iterator ps::vector<T>::cend() const noexcept {
  return data_ + size_;
}

template <class T>
bool ps::vector<T>::empty() const noexcept {
  return size_ == 0;
}

template <class T>
typename ps::vector<T>::size_type ps::vector<T>::size() const noexcept {
  return size_;
}

template <class T>
typename ps::vector<T>::size_type ps::vector<T>::max_size() const noexcept {
  return std::numeric_limits<size_type>::max() / sizeof(value_type);
}

template <class T>
void ps::vector<T>::reserve(size_type new_cap) {
  if (new_cap > max_size()) {
    throw std::length_error("Length error");
  }
  if (new_cap > capacity_) {
    T* tmp = new T[new_cap];
    std::copy(begin(), end(), tmp);
    delete[] data_;
    data_ = tmp;
    capacity_ = new_cap;
  }
}

template <class T>
typename ps::vector<T>::size_type ps::vector<T>::capacity() const noexcept {
  return capacity_;
}

template <class T>
void ps::vector<T>::shrink_to_fit() {
  if (capacity_ > size_) {
    T* tmp = new T[size_];
    std::copy(begin(), end(), tmp);
    delete[] data_;
    data_ = tmp;
    capacity_ = size_;
  }
}

template <class T>
void ps::vector<T>::clear() noexcept {
  size_ = 0;
}

template <class T>
typename ps::vector<T>::iterator ps::vector<T>::insert(const_iterator pos,
                                                       const T& value) {
  size_type index = size_type(pos - begin());
  if (index > size_) {
    throw std::out_of_range("Out of range");
  }
  if (capacity_ == size_) {
    reserve(capacity_ * 2);
  }
  value_type tmp = value;
  for (size_type i = index; i <= size_; ++i) {
    value_type item = *(data_ + i);
    *(data_ + i) = tmp;
    tmp = item;
  }
  ++size_;
  return begin() + index;
}

template <class T>
typename ps::vector<T>::iterator ps::vector<T>::erase(const_iterator pos) {
  size_type index = size_type(pos - begin());
  if (index >= size_) {
    return end();
  }
  std::copy(begin(), const_cast<iterator>(pos), data_);
  std::copy(const_cast<iterator>(pos + 1), end(), data_ + index);
  --size_;
  return begin() + index;
}

template <class T>
void ps::vector<T>::push_back(const_reference value) {
  if (capacity_ == size_) {
    reserve(capacity_ * 2);
    if (capacity_ == 0) reserve(1);
  }
  data_[size_] = value;
  ++size_;
}

template <class T>
void ps::vector<T>::pop_back() {
  erase(end() - 1);
}

template <class T>
void ps::vector<T>::swap(vector& other) noexcept {
  std::swap(data_, other.data_);
  std::swap(size_, other.size_);
  std::swap(capacity_, other.capacity_);
}

template <class T>
template <class... Args>
typename ps::vector<T>::iterator ps::vector<T>::insert_many(const_iterator pos,
                                                            Args&&... args) {
  size_type index = size_type(pos - begin());
  for (const auto& arg : {args...}) {
    insert(begin() + index, arg);
  }
  return begin() + index;
}

template <class T>
template <class... Args>
void ps::vector<T>::insert_many_back(Args&&... args) {
  for (const auto& arg : {args...}) {
    push_back(arg);
  }
}

#endif  // CONTAINERS_SRC_PS_VECTOR_H_