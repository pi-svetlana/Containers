#ifndef CONTAINERS_SRC_PS_ARRAY_H_
#define CONTAINERS_SRC_PS_ARRAY_H_

#include <iostream>

namespace ps {
template <class T, size_t N>
class array {
 public:
  using value_type = T;
  using reference = T &;
  using const_reference = const T &;
  using iterator = T *;
  using const_iterator = const T *;
  using size_type = size_t;
  using array_type = array<T, N>;

  array();
  array(std::initializer_list<T> const &items);
  array(const array_type &a);
  array(array_type &&a) noexcept;
  ~array() {}

  array_type &operator=(const array &other);
  array_type &operator=(array &&a) noexcept;

  constexpr reference operator[](size_type pos);
  constexpr const_reference operator[](size_type pos) const;

  constexpr reference at(size_type pos);
  constexpr const_reference at(size_type pos) const;
  constexpr reference front();
  constexpr const_reference front() const;
  constexpr reference back();
  constexpr const_reference back() const;

  constexpr iterator data() noexcept;
  constexpr const_iterator data() const noexcept;

  constexpr iterator begin() noexcept;
  constexpr const_iterator begin() const noexcept;
  constexpr const_iterator cbegin() const noexcept;

  constexpr iterator end() noexcept;
  constexpr const_iterator end() const noexcept;
  constexpr const_iterator cend() const noexcept;

  constexpr bool empty() const noexcept;
  constexpr size_type size() const noexcept;
  constexpr size_type max_size() const noexcept;

  void swap(array &other) noexcept;
  void fill(const_reference value);

 private:
  const size_type size_ = N;
  value_type data_[N];
};

template <class T>
class array<T, 0> {
 public:
  using value_type = T;
  using reference = T &;
  using const_reference = const T &;
  using iterator = T *;
  using const_iterator = const T *;
  using size_type = size_t;
  using array_type = array<T, 0>;

  array() {}
  array([[maybe_unused]] const array_type &a) : array() {}
  array([[maybe_unused]] array_type &&a) noexcept : array() {}
  ~array() {}

  array_type &operator=([[maybe_unused]] const array &other) { return *this; }
  array_type &operator=([[maybe_unused]] array &&a) noexcept { return *this; }

  constexpr reference at([[maybe_unused]] size_type pos) {
    throw std::out_of_range("Out of range");
  }
  constexpr const_reference at([[maybe_unused]] size_type pos) const {
    throw std::out_of_range("Out of range");
  }

  constexpr reference front() { throw std::out_of_range("Out of range"); }
  constexpr const_reference front() const {
    throw std::out_of_range("Out of range");
  }
  constexpr reference back() { throw std::out_of_range("Out of range"); }
  constexpr const_reference back() const {
    throw std::out_of_range("Out of range");
  }
  constexpr iterator data() noexcept { return nullptr; }
  constexpr const_iterator data() const noexcept { return nullptr; }

  constexpr iterator begin() noexcept { return nullptr; }
  constexpr const_iterator begin() const noexcept { return nullptr; }
  constexpr const_iterator cbegin() const noexcept { return nullptr; }

  constexpr iterator end() noexcept { return nullptr; }
  constexpr const_iterator end() const noexcept { return nullptr; }
  constexpr const_iterator cend() const noexcept { return nullptr; }

  constexpr bool empty() const noexcept { return true; }
  constexpr size_type size() const noexcept { return 0; }
  constexpr size_type max_size() const noexcept { return 0; }

  void swap([[maybe_unused]] array &other) noexcept {}
  void fill([[maybe_unused]] const_reference value) {}

 private:
  value_type data_[1];
  const size_type size_ = 0;
};
}  // namespace ps

template <class T, size_t N>
ps::array<T, N>::array() {
  constexpr T object{};
  for (size_type i = 0; i < size_; ++i) {
    data_[i] = object;
  }
}

template <typename T, size_t N>
ps::array<T, N>::array(std::initializer_list<T> const &items) {
  size_t i = 0;
  for (auto it = items.begin(); it != items.end() && i < N; ++it, ++i) {
    data_[i] = *it;
  }
}

template <class T, size_t N>
ps::array<T, N>::array(const array_type &a) {
  for (size_type i = 0; i < size_; ++i) {
    data_[i] = a.data_[i];
  }
}

template <class T, size_t N>
ps::array<T, N>::array(array_type &&a) noexcept {
  for (size_type i = 0; i < size_; ++i) {
    data_[i] = a.data_[i];
    a.data_[i] = 0;
  }
}

template <class T, size_t N>
ps::array<T, N> &ps::array<T, N>::operator=(const array &a) {
  if (this != &a) {
    for (size_type i = 0; i < a.size_; ++i) {
      data_[i] = a.data_[i];
    }
  }
  return *this;
}

template <class T, size_t N>
ps::array<T, N> &ps::array<T, N>::operator=(array &&a) noexcept {
  if (this != &a) {
    for (size_type i = 0; i < a.size_; ++i) {
      data_[i] = a.data_[i];
      a.data_[i] = 0;
    }
  }
  return *this;
}

template <class T, size_t N>
constexpr typename ps::array<T, N>::reference ps::array<T, N>::operator[](
    size_type pos) {
  return data_[pos];
}

template <class T, size_t N>
constexpr typename ps::array<T, N>::const_reference
ps::array<T, N>::operator[](size_type pos) const {
  return data_[pos];
}

template <class T, size_t N>
constexpr typename ps::array<T, N>::reference ps::array<T, N>::at(
    size_type pos) {
  if (pos >= size_) throw std::out_of_range("Index is out of range");
  return data_[pos];
}

template <class T, size_t N>
constexpr typename ps::array<T, N>::const_reference ps::array<T, N>::at(
    size_type pos) const {
  if (pos >= size_) throw std::out_of_range("Index is out of range");
  return data_[pos];
}

template <class T, size_t N>
constexpr typename ps::array<T, N>::reference ps::array<T, N>::front() {
  return data_[0];
}

template <class T, size_t N>
constexpr typename ps::array<T, N>::const_reference ps::array<T, N>::front()
    const {
  return data_[0];
}

template <class T, size_t N>
constexpr typename ps::array<T, N>::reference ps::array<T, N>::back() {
  return data_[size_ - 1];
}

template <class T, size_t N>
constexpr typename ps::array<T, N>::const_reference ps::array<T, N>::back()
    const {
  return data_[size_ - 1];
}

template <class T, size_t N>
constexpr typename ps::array<T, N>::iterator
ps::array<T, N>::data() noexcept {
  return data_;
}

template <class T, size_t N>
constexpr typename ps::array<T, N>::const_iterator ps::array<T, N>::data()
    const noexcept {
  if (size_ == 0) return nullptr;
  return data_;
}

template <class T, size_t N>
constexpr typename ps::array<T, N>::iterator
ps::array<T, N>::begin() noexcept {
  return &data_[0];
}

template <class T, size_t N>
constexpr typename ps::array<T, N>::const_iterator ps::array<T, N>::begin()
    const noexcept {
  return &data_[0];
}

template <class T, size_t N>
constexpr typename ps::array<T, N>::const_iterator ps::array<T, N>::cbegin()
    const noexcept {
  return &data_[0];
}

template <class T, size_t N>
constexpr typename ps::array<T, N>::iterator ps::array<T, N>::end() noexcept {
  return &data_[size_];
}

template <class T, size_t N>
constexpr typename ps::array<T, N>::const_iterator ps::array<T, N>::end()
    const noexcept {
  return &data_[size_];
}

template <class T, size_t N>
constexpr typename ps::array<T, N>::const_iterator ps::array<T, N>::cend()
    const noexcept {
  return &data_[size_];
}

template <class T, size_t N>
constexpr bool ps::array<T, N>::empty() const noexcept {
  return false;
}

template <class T, size_t N>
constexpr typename ps::array<T, N>::size_type ps::array<T, N>::size()
    const noexcept {
  return size_;
}

template <class T, size_t N>
constexpr typename ps::array<T, N>::size_type ps::array<T, N>::max_size()
    const noexcept {
  return size_;
}

template <class T, size_t N>
void ps::array<T, N>::swap(array &other) noexcept {
  if (this != &other) {
    for (size_t i = 0; i < size_; ++i) {
      std::swap(data_[i], other.data_[i]);
    }
  }
}

template <class T, size_t N>
void ps::array<T, N>::fill(const T &value) {
  for (size_t i = 0; i < size_; ++i) {
    data_[i] = value;
  }
}

#endif  // CONTAINERS_SRC_PS_ARRAY_H_