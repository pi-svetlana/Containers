#ifndef CONTAINERS_SRC_PS_SET_H_
#define CONTAINERS_SRC_PS_SET_H_

#include <stdexcept>

#include "ps_rb_tree.h"
#include "ps_vector.h"

namespace ps {

template <typename Key>
class set {
  class SetIterator;
  class SetConstIterator;

  class SetIterator {
    friend set<Key>;
    using node_type = rbnode<Key, Key>;
    node_type *_node;
    RBTree<Key, Key> *_tree;

   public:
    SetIterator() {}
    explicit SetIterator(RBTree<Key, Key> *tree, rbnode<Key, Key> *node)
        : _node(node), _tree(tree) {}

    const Key &operator*() const { return _node->value.first; }

    SetIterator &operator++() {
      _node = _tree->nextNode(_node);
      return *this;
    }

    SetIterator &operator--() {
      _node = _tree->prevNode(_node);
      return *this;
    }

    SetIterator operator++(int) {
      SetIterator tmp(*this);
      ++(*this);
      return tmp;
    }

    SetIterator operator--(int) {
      SetIterator tmp(*this);
      --(*this);
      return tmp;
    }

    bool operator==(const SetConstIterator &other) const noexcept {
      return other._node == _node;
    }

    bool operator!=(const SetConstIterator &other) const noexcept {
      return other._node != _node;
    }

    bool operator==(const SetIterator &other) const noexcept {
      return other._node == _node;
    }
    bool operator!=(const SetIterator &other) const noexcept {
      return other._node != _node;
    }

    ~SetIterator() { _node = nullptr; }
  };

  class SetConstIterator {
    friend set<Key>;
    using node_type = rbnode<Key, Key>;
    const node_type *_node;
    const RBTree<Key, Key> *_tree;

   public:
    SetConstIterator() {}
    explicit SetConstIterator(const RBTree<Key, Key> *tree,
                              const rbnode<Key, Key> *node)
        : _node(node), _tree(tree) {}

    const Key &operator*() const { return _node->value.first; }

    SetConstIterator &operator++() {
      _node = _tree->nextNode(_node);
      return *this;
    }

    SetConstIterator &operator--() {
      _node = _tree->prevNode(_node);
      return *this;
    }

    SetConstIterator operator++(int) {
      SetConstIterator tmp(*this);
      ++(*this);
      return tmp;
    }

    SetConstIterator operator--(int) {
      SetConstIterator tmp(*this);
      --(*this);
      return tmp;
    }

    bool operator==(const SetConstIterator &other) const noexcept {
      return other._node == _node;
    }

    bool operator!=(const SetConstIterator &other) const noexcept {
      return other._node != _node;
    }

    bool operator==(const SetIterator &other) const noexcept {
      return other._node == _node;
    }
    bool operator!=(const SetIterator &other) const noexcept {
      return other._node != _node;
    }

    ~SetConstIterator() { _node = nullptr; }
  };

  RBTree<Key, Key> *_tree;

 public:
  using key_type = Key;
  using value_type = Key;
  using reference = value_type &;
  using const_reference = value_type &;
  using iterator = SetIterator;
  using const_iterator = SetConstIterator;
  using size_type = size_t;

  set();
  set(const set &m);
  set(set &&m) noexcept;
  set(std::initializer_list<value_type> const &items);
  ~set();

  set &operator=(const set &other);
  set &operator=(set &&other) noexcept;

  bool empty() const noexcept;
  size_type size() const noexcept;
  size_type max_size() const noexcept;

  iterator begin() noexcept;
  const_iterator begin() const noexcept;
  const_iterator cbegin() const noexcept;
  iterator end() noexcept;
  const_iterator end() const noexcept;
  const_iterator cend() const noexcept;

  void clear() noexcept;
  std::pair<iterator, bool> insert(const value_type &value);
  void erase(iterator pos);
  void erase(Key key);
  void swap(set &other);
  void merge(set &other);

  bool contains(const Key &key);
  iterator find(const Key &key);

  template <class... Args>
  vector<std::pair<iterator, bool>> insert_many(Args &&...args);
};

template <typename Key>
set<Key>::set() {
  _tree = new RBTree<Key, Key>{};
}

template <typename Key>
set<Key>::set(const set &m) {
  _tree = new RBTree<Key, Key>{};

  for (SetConstIterator start = m.begin(); start != m.end(); start++) {
    Key value = *start;

    insert(value);
  }
}

template <typename Key>
set<Key>::set(std::initializer_list<value_type> const &items) : set() {
  for (auto i = items.begin(); i < items.end(); i++) {
    insert(*i);
  }
}

template <typename Key>
set<Key>::set(set &&m) noexcept {
  _tree = m._tree;

  m._tree = nullptr;
}

template <typename Key>
set<Key>::~set() {
  if (_tree != nullptr) {
    delete _tree;
  }
}

template <typename Key>
set<Key> &set<Key>::operator=(const set &other) {
  if (this == &other) return *this;
  set<Key> temp_set(other);
  delete _tree;
  this->_tree = temp_set._tree;
  temp_set._tree = nullptr;
  return *this;
}

template <typename Key>
set<Key> &set<Key>::operator=(set &&other) noexcept {
  if (this == &other) return *this;
  delete _tree;
  _tree = other._tree;
  other._tree = nullptr;
  return *this;
}

template <typename Key>
bool set<Key>::empty() const noexcept {
  return _tree->size() == 0;
}

template <typename Key>
typename set<Key>::size_type set<Key>::size() const noexcept {
  return _tree->size();
}

template <typename Key>
typename set<Key>::size_type set<Key>::max_size() const noexcept {
  return _tree->max_size();
}

template <typename Key>
typename set<Key>::iterator set<Key>::begin() noexcept {
  return set::iterator(_tree, _tree->minNode());
}

template <typename Key>
typename set<Key>::const_iterator set<Key>::begin() const noexcept {
  set::const_iterator iterator(_tree, _tree->minNode());
  return iterator;
}

template <typename Key>
typename set<Key>::const_iterator set<Key>::cbegin() const noexcept {
  set::const_iterator iterator(_tree, _tree->minNode());
  return iterator;
}

template <typename Key>
typename set<Key>::iterator set<Key>::end() noexcept {
  return set::iterator(_tree, _tree->nextNode(_tree->maxNode()));
}

template <typename Key>
typename set<Key>::const_iterator set<Key>::end() const noexcept {
  return set::const_iterator(_tree, _tree->nextNode(_tree->maxNode()));
}

template <typename Key>
typename set<Key>::const_iterator set<Key>::cend() const noexcept {
  return set::const_iterator(_tree, _tree->nextNode(_tree->maxNode()));
}

template <typename Key>
void set<Key>::clear() noexcept {
  _tree->clear();
}

template <typename Key>
std::pair<typename set<Key>::iterator, bool> set<Key>::insert(
    const set::value_type &value) {
  rbnode<Key, Key> *found_node = _tree->findNode(value);
  rbnode<Key, Key> *result_node;
  bool inserted;
  if (found_node != nullptr) {
    result_node = found_node;
    inserted = false;
  } else {
    auto value_pair = std::pair<const Key, Key>(value, value);
    result_node = _tree->insert(value_pair);
    inserted = true;
  }

  iterator result_node_iterator(_tree, result_node);
  return std::pair<iterator, bool>(result_node_iterator, inserted);
}

template <typename Key>
void set<Key>::erase(set<Key>::iterator pos) {
  _tree->del(*pos);
}

template <typename Key>
void set<Key>::erase(Key key) {
  _tree->del(key);
}

template <typename Key>
void set<Key>::swap(set &other) {
  RBTree<Key, Key> *temp_tree = this->_tree;
  this->_tree = other._tree;
  other._tree = temp_tree;
}

template <typename Key>
void set<Key>::merge(set &other) {
  vector<Key> moved_values;
  for (SetIterator start = other.begin(); start != other.end(); start++) {
    if (!contains(*start)) {
      insert(*start);
      moved_values.push_back(*start);
    }
  }
  for (auto start : moved_values) {
    other.erase(other.find(start));
  }
}

template <typename Key>
bool set<Key>::contains(const Key &key) {
  auto node = _tree->findNode(key);
  if (node == nullptr) {
    return false;
  }
  return true;
}

template <typename Key>
typename set<Key>::iterator set<Key>::find(const Key &key) {
  return set<Key>::iterator(_tree, _tree->findNode(key));
}

template <typename Key>
template <class... Args>
vector<std::pair<typename set<Key>::iterator, bool>> set<Key>::insert_many(
    Args &&...args) {
  vector<std::pair<iterator, bool>> res{};
  for (const auto &arg : {args...}) {
    res.push_back(insert(arg));
  }
  return res;
}

}  // namespace ps

#endif
