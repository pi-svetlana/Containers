#ifndef CONTAINERS_SRC_PS_MAP_H_
#define CONTAINERS_SRC_PS_MAP_H_

#include <iostream>
#include <stdexcept>

#include "ps_rb_tree.h"
#include "ps_vector.h"

namespace ps {

template <typename Key, typename T>
class map {
  class MapIterator;
  class MapConstIterator;

  class MapIterator {
    friend ps::map<Key, T>;
    using node_type = rbnode<Key, T>;
    node_type *_node;
    RBTree<Key, T> *_tree;

   public:
    MapIterator() {}
    explicit MapIterator(RBTree<Key, T> *tree, rbnode<Key, T> *node)
        : _node(node), _tree(tree) {}

    const std::pair<const Key, T> &operator*() const { return _node->value; }
    std::pair<const Key, T> *operator->() { return &(_node->value); }

    MapIterator &operator++() {
      _node = _tree->nextNode(_node);
      return *this;
    }

    MapIterator &operator--() {
      _node = _tree->prevNode(_node);
      return *this;
    }

    MapIterator operator++(int) {
      MapIterator tmp(*this);
      ++(*this);
      return tmp;
    }

    MapIterator operator--(int) {
      MapIterator tmp(*this);
      --(*this);
      return tmp;
    }

    bool operator==(const MapConstIterator &other) const noexcept {
      return other._node == _node;
    }

    bool operator!=(const MapConstIterator &other) const noexcept {
      return other._node != _node;
    }

    bool operator==(const MapIterator &other) const noexcept {
      return other._node == _node;
    }
    bool operator!=(const MapIterator &other) const noexcept {
      return other._node != _node;
    }

    ~MapIterator() { _node = nullptr; }
  };

  class MapConstIterator {
    friend ps::map<Key, T>;
    using node_type = rbnode<Key, T>;
    const node_type *_node;
    const RBTree<Key, T> *_tree;

   public:
    MapConstIterator() {}
    explicit MapConstIterator(const RBTree<Key, T> *tree,
                              const rbnode<Key, T> *node)
        : _node(node), _tree(tree) {}

    const std::pair<const Key, T> &operator*() const { return _node->value; }
    const std::pair<const Key, T> *operator->() const {
      return &(_node->value);
    }

    MapConstIterator &operator++() {
      _node = _tree->nextNode(_node);
      return *this;
    }

    MapConstIterator &operator--() {
      _node = _tree->prevNode(_node);
      return *this;
    }

    MapConstIterator operator++(int) {
      MapConstIterator tmp(*this);
      ++(*this);
      return tmp;
    }

    MapConstIterator operator--(int) {
      MapConstIterator tmp(*this);
      --(*this);
      return tmp;
    }

    bool operator==(const MapConstIterator &other) const noexcept {
      return other._node == _node;
    }

    bool operator!=(const MapConstIterator &other) const noexcept {
      return other._node != _node;
    }

    bool operator==(const MapIterator &other) const noexcept {
      return other._node == _node;
    }
    bool operator!=(const MapIterator &other) const noexcept {
      return other._node != _node;
    }

    ~MapConstIterator() { _node = nullptr; }
  };

  RBTree<Key, T> *_tree;

 public:
  using key_type = Key;
  using mapped_type = T;
  using value_type = std::pair<const key_type, mapped_type>;
  using reference = value_type &;
  using const_reference = value_type &;
  using iterator = MapIterator;
  using const_iterator = MapConstIterator;
  using size_type = size_t;

  map();
  map(const map &m);
  map(map &&m) noexcept;
  explicit map(std::initializer_list<value_type> const &items);
  ~map();

  mapped_type &operator[](const Key &key);
  const mapped_type &operator[](const Key &key) const;
  map &operator=(const map &other);
  map &operator=(map &&other) noexcept;

  bool empty() const noexcept;
  size_type size() const noexcept;
  size_type max_size() const noexcept;

  T &at(const Key &key);
  const T &at(const Key &key) const;

  iterator begin() noexcept;
  const_iterator begin() const noexcept;
  const_iterator cbegin() const noexcept;
  iterator end() noexcept;
  const_iterator end() const noexcept;
  const_iterator cend() const noexcept;

  void clear() noexcept;
  std::pair<iterator, bool> insert(const value_type &value);
  std::pair<iterator, bool> insert(const Key &key, const T &obj);
  std::pair<iterator, bool> insert_or_assign(const Key &key, const T &obj);
  void erase(iterator pos);
  void erase(const Key &key);
  void swap(map &other);
  void merge(map &other);

  bool contains(const Key &key);

  template <class... Args>
  vector<std::pair<iterator, bool>> insert_many(Args &&...args);

 private:
  std::pair<iterator, bool> insert(const value_type &value, bool assign);
};

template <typename Key, typename T>
map<Key, T>::map() {
  _tree = new RBTree<Key, T>{};
}

template <typename Key, typename T>
map<Key, T>::map(const map &m) {
  _tree = new RBTree<Key, T>{};

  for (MapConstIterator start = m.cbegin(); start != m.cend(); start++) {
    std::pair<Key, T> start_pair = *start;

    auto copy_pair =
        std::pair<const Key, T>{start_pair.first, start_pair.second};

    _tree->insert(copy_pair);
  }
}

template <typename Key, typename T>
map<Key, T>::map(std::initializer_list<value_type> const &items) : map() {
  for (auto i = items.begin(); i < items.end(); i++) {
    insert(*i);
  }
}

template <typename Key, typename T>
map<Key, T>::map(map &&m) noexcept {
  _tree = m._tree;

  m._tree = nullptr;
}

template <typename Key, typename T>
map<Key, T>::~map() {
  if (_tree != nullptr) {
    delete _tree;
  }
}

template <typename Key, typename T>
bool map<Key, T>::empty() const noexcept {
  return _tree->size() == 0;
}

template <typename Key, typename T>
typename map<Key, T>::size_type map<Key, T>::size() const noexcept {
  return _tree->size();
}

template <typename Key, typename T>
typename map<Key, T>::size_type map<Key, T>::max_size() const noexcept {
  return _tree->max_size();
}

template <typename Key, typename T>
T &map<Key, T>::at(const Key &key) {
  if (!contains(key)) {
    throw std::out_of_range("key does not exists");
  }
  return _tree->find(key).second;
}

template <typename Key, typename T>
const T &map<Key, T>::at(const Key &key) const {
  auto node = _tree->findNode(key);
  if (node == nullptr) {
    throw std::out_of_range("key does not exists");
  }
  return _tree->find(key).second;
}

template <typename Key, typename T>
typename map<Key, T>::mapped_type &map<Key, T>::operator[](const Key &key) {
  if (!_tree->contains(key)) {
    std::pair<const Key, T> pair = std::pair<Key, T>(key, T());
    insert(pair);
  }
  return _tree->find(key).second;
}

template <typename Key, typename T>
const typename map<Key, T>::mapped_type &map<Key, T>::operator[](
    const Key &key) const {
  return _tree->find(key).second;
}

template <typename Key, typename T>
map<Key, T> &map<Key, T>::operator=(const map &other) {
  if (this == &other) return *this;
  map<Key, T> temp_map(other);
  delete _tree;
  this->_tree = temp_map._tree;
  temp_map._tree = nullptr;
  return *this;
}

template <typename Key, typename T>
map<Key, T> &map<Key, T>::operator=(map &&other) noexcept {
  if (this == &other) return *this;
  delete _tree;
  _tree = other._tree;
  other._tree = nullptr;
  return *this;
}

template <typename Key, typename T>
typename map<Key, T>::iterator map<Key, T>::begin() noexcept {
  return map::iterator(_tree, _tree->minNode());
}

template <typename Key, typename T>
typename map<Key, T>::const_iterator map<Key, T>::begin() const noexcept {
  return map::const_iterator(_tree, _tree->minNode());
}

template <typename Key, typename T>
typename map<Key, T>::const_iterator map<Key, T>::cbegin() const noexcept {
  rbnode<Key, T> *node = _tree->minNode();
  map::MapConstIterator iterator(_tree, node);
  return iterator;
}

template <typename Key, typename T>
typename map<Key, T>::iterator map<Key, T>::end() noexcept {
  return map::iterator(_tree, _tree->nextNode(_tree->maxNode()));
}

template <typename Key, typename T>
typename map<Key, T>::const_iterator map<Key, T>::end() const noexcept {
  return map::const_iterator(_tree, _tree->nextNode(_tree->maxNode()));
}

template <typename Key, typename T>
typename map<Key, T>::const_iterator map<Key, T>::cend() const noexcept {
  return map::const_iterator(_tree, _tree->nextNode(_tree->maxNode()));
}

template <typename Key, typename T>
void map<Key, T>::clear() noexcept {
  _tree->clear();
}

template <typename Key, typename T>
std::pair<typename map<Key, T>::iterator, bool> map<Key, T>::insert(
    const map::value_type &value, bool assign) {
  rbnode<Key, T> *found_node = _tree->findNode(value.first);
  rbnode<Key, T> *result_node;
  bool inserted;
  if (found_node != nullptr) {
    result_node = found_node;
    if (assign) {
      result_node->value.second = value.second;
    }
    inserted = false;
  } else {
    map::value_type copy_value(value);
    result_node = _tree->insert(copy_value);
    inserted = true;
  }

  iterator result_node_iterator(_tree, result_node);
  return std::pair<iterator, bool>(result_node_iterator, inserted);
}

template <typename Key, typename T>
std::pair<typename map<Key, T>::iterator, bool> map<Key, T>::insert(
    const map::value_type &value) {
  return insert(value, false);
}

template <typename Key, typename T>
std::pair<typename map<Key, T>::iterator, bool> map<Key, T>::insert(
    const Key &key, const T &obj) {
  return insert(value_type(key, obj));
}

template <typename Key, typename T>
std::pair<typename map<Key, T>::iterator, bool> map<Key, T>::insert_or_assign(
    const Key &key, const T &obj) {
  return insert(std::pair<Key, T>(key, obj), true);
}

template <typename Key, typename T>
void map<Key, T>::erase(map<Key, T>::iterator pos) {
  erase(pos->first);
}

template <typename Key, typename T>
void map<Key, T>::erase(const Key &key) {
  _tree->del(key);
}

template <typename Key, typename T>
void map<Key, T>::swap(map &other) {
  RBTree<Key, T> *temp_tree = this->_tree;
  this->_tree = other._tree;
  other._tree = temp_tree;
}

template <typename Key, typename T>
void map<Key, T>::merge(map &other) {
  vector<Key> moved_values;
  for (MapIterator start = other.begin(); start != other.end(); start++) {
    if (!contains((*start).first)) {
      insert(*start);
      moved_values.push_back((*start).first);
    }
  }
  for (auto i : moved_values) {
    other.erase(i);
  }
}

template <typename Key, typename T>
bool map<Key, T>::contains(const Key &key) {
  auto node = _tree->findNode(key);
  if (node == nullptr) {
    return false;
  }
  return true;
}

template <typename Key, typename T>
template <class... Args>
vector<std::pair<typename map<Key, T>::iterator, bool>>
map<Key, T>::insert_many(Args &&...args) {
  vector<std::pair<iterator, bool>> res{};
  for (const auto &arg : {args...}) {
    res.push_back(insert(arg));
  }
  return res;
}

}  // namespace ps

#endif