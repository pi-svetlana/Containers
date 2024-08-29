#ifndef CONTAINERS_SRC_PS_MULTISET_H_
#define CONTAINERS_SRC_PS_MULTISET_H_

#include <stdexcept>

#include "ps_rb_tree.h"
#include "ps_vector.h"

namespace ps {

template <typename Key>
class multiset {
  class MultisetIterator;
  class MultisetConstIterator;

  class MultisetIterator {
    friend multiset<Key>;
    using node_type = rbnode<Key, size_t>;
    node_type *_node;
    RBTree<Key, size_t> *_tree;
    size_t _pos = 0;

   public:
    MultisetIterator() {}
    explicit MultisetIterator(RBTree<Key, size_t> *tree,
                              rbnode<Key, size_t> *node)
        : _node(node), _tree(tree) {}

    const Key &operator*() const { return _node->value.first; }

    MultisetIterator &operator++() {
      if ((_pos + 1) < _node->value.second) {
        _pos++;
      } else {
        _node = _tree->nextNode(_node);
        _pos = 0;
      }
      return *this;
    }

    MultisetIterator &operator--() {
      if (_pos > 0) {
        _pos--;
      } else {
        _node = _tree->prevNode(_node);
        _pos = _node->value.second - 1;
      }
      return *this;
    }

    MultisetIterator operator++(int) {
      MultisetIterator tmp(*this);
      ++(*this);
      return tmp;
    }

    MultisetIterator operator--(int) {
      MultisetIterator tmp(*this);
      --(*this);
      return tmp;
    }

    bool operator==(const MultisetConstIterator &other) const noexcept {
      return other._node == _node;
    }

    bool operator!=(const MultisetConstIterator &other) const noexcept {
      return other._node != _node;
    }

    bool operator==(const MultisetIterator &other) const noexcept {
      return other._node == _node;
    }
    bool operator!=(const MultisetIterator &other) const noexcept {
      return other._node != _node;
    }

    ~MultisetIterator() { _node = nullptr; }
  };

  class MultisetConstIterator {
    friend multiset<Key>;
    using node_type = rbnode<Key, size_t>;
    const node_type *_node;
    const RBTree<Key, size_t> *_tree;
    size_t _pos = 0;

   public:
    MultisetConstIterator() {}
    explicit MultisetConstIterator(const RBTree<Key, size_t> *tree,
                                   const rbnode<Key, size_t> *node)
        : _node(node), _tree(tree) {}

    const Key &operator*() const { return _node->value.first; }

    MultisetConstIterator &operator++() {
      if ((_pos + 1) < _node->value.second) {
        _pos++;
      } else {
        _node = _tree->nextNode(_node);
        _pos = 0;
      }
      return *this;
    }

    MultisetConstIterator &operator--() {
      if (_pos > 0) {
        _pos--;
      } else {
        _node = _tree->prevNode(_node);
        _pos = _node->value.second - 1;
      }
      return *this;
    }

    MultisetConstIterator operator++(int) {
      MultisetConstIterator tmp(*this);
      ++(*this);
      return tmp;
    }

    MultisetConstIterator operator--(int) {
      MultisetConstIterator tmp(*this);
      --(*this);
      return tmp;
    }

    bool operator==(const MultisetConstIterator &other) const noexcept {
      return other._node == _node;
    }

    bool operator!=(const MultisetConstIterator &other) const noexcept {
      return other._node != _node;
    }

    bool operator==(const MultisetIterator &other) const noexcept {
      return other._node == _node;
    }
    bool operator!=(const MultisetIterator &other) const noexcept {
      return other._node != _node;
    }

    ~MultisetConstIterator() { _node = nullptr; }
  };

  RBTree<Key, size_t> *_tree;
  size_t _size = 0;

 public:
  using key_type = Key;
  using value_type = Key;
  using reference = value_type &;
  using const_reference = value_type &;
  using iterator = MultisetIterator;
  using const_iterator = MultisetConstIterator;
  using size_type = size_t;

  multiset();
  multiset(const multiset &m);
  multiset(multiset &&m) noexcept;
  multiset(std::initializer_list<value_type> const &items);
  ~multiset();

  multiset &operator=(const multiset &other);
  multiset &operator=(multiset &&other) noexcept;

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
  void swap(multiset &other);
  void merge(multiset &other);

  size_type count(const Key &key);
  bool contains(const Key &key);
  iterator find(const Key &key);
  std::pair<iterator, iterator> equal_range(const Key &key);
  iterator lower_bound(const Key &key);
  iterator upper_bound(const Key &key);

  template <class... Args>
  vector<std::pair<iterator, bool>> insert_many(Args &&...args);
};

template <typename Key>
multiset<Key>::multiset() {
  _tree = new RBTree<Key, size_t>{};
}

template <typename Key>
multiset<Key>::multiset(const multiset &m) {
  _tree = new RBTree<Key, size_t>{};

  for (MultisetConstIterator start = m.begin(); start != m.end(); start++) {
    Key value = *start;

    insert(value);
  }
}

template <typename Key>
multiset<Key>::multiset(std::initializer_list<value_type> const &items)
    : multiset() {
  for (auto i = items.begin(); i < items.end(); i++) {
    insert(*i);
  }
}

template <typename Key>
multiset<Key>::multiset(multiset &&m) noexcept {
  _tree = m._tree;
  _size = m._size;

  m._tree = nullptr;
}

template <typename Key>
multiset<Key>::~multiset() {
  if (_tree != nullptr) {
    delete _tree;
  }
}

template <typename Key>
multiset<Key> &multiset<Key>::operator=(const multiset &other) {
  if (this == &other) return *this;
  multiset<Key> temp_set(other);
  delete _tree;
  this->_tree = temp_set._tree;
  temp_set._tree = nullptr;
  return *this;
}

template <typename Key>
multiset<Key> &multiset<Key>::operator=(multiset &&other) noexcept {
  if (this == &other) return *this;
  delete _tree;
  _tree = other._tree;
  other._tree = nullptr;
  return *this;
}

template <typename Key>
bool multiset<Key>::empty() const noexcept {
  return _size == 0;
}

template <typename Key>
typename multiset<Key>::size_type multiset<Key>::size() const noexcept {
  return _size;
}

template <typename Key>
typename multiset<Key>::size_type multiset<Key>::max_size() const noexcept {
  return _tree->max_size();
}

template <typename Key>
typename multiset<Key>::iterator multiset<Key>::begin() noexcept {
  return multiset::iterator(_tree, _tree->minNode());
}

template <typename Key>
typename multiset<Key>::const_iterator multiset<Key>::begin() const noexcept {
  multiset::const_iterator iterator(_tree, _tree->minNode());
  return iterator;
}

template <typename Key>
typename multiset<Key>::const_iterator multiset<Key>::cbegin() const noexcept {
  multiset::const_iterator iterator(_tree, _tree->minNode());
  return iterator;
}

template <typename Key>
typename multiset<Key>::iterator multiset<Key>::end() noexcept {
  return multiset::iterator(_tree, _tree->nextNode(_tree->maxNode()));
}

template <typename Key>
typename multiset<Key>::const_iterator multiset<Key>::end() const noexcept {
  return multiset::const_iterator(_tree, _tree->nextNode(_tree->maxNode()));
}

template <typename Key>
typename multiset<Key>::const_iterator multiset<Key>::cend() const noexcept {
  return multiset::const_iterator(_tree, _tree->nextNode(_tree->maxNode()));
}

template <typename Key>
void multiset<Key>::clear() noexcept {
  _tree->clear();
  _size = 0;
}

template <typename Key>
std::pair<typename multiset<Key>::iterator, bool> multiset<Key>::insert(
    const multiset::value_type &value) {
  rbnode<Key, size_t> *found_node = _tree->findNode(value);
  rbnode<Key, size_t> *result_node;
  bool inserted;
  if (found_node != nullptr) {
    found_node->value.second += 1;
    result_node = found_node;
    inserted = false;
  } else {
    auto value_pair = std::pair<const Key, size_t>(value, 1);
    result_node = _tree->insert(value_pair);
    inserted = true;
  }
  _size++;

  iterator result_node_iterator(_tree, result_node);
  return std::pair<iterator, bool>(result_node_iterator, inserted);
}

template <typename Key>
void multiset<Key>::erase(multiset<Key>::iterator pos) {
  erase(*pos);
}

template <typename Key>
void multiset<Key>::erase(Key key) {
  auto found_node = _tree->findNode(key);
  if (found_node == nullptr) {
    return;
  }
  if (found_node->value.second > 1) {
    found_node->value.second -= 1;
  } else {
    _tree->del(key);
  }
  _size--;
}

template <typename Key>
void multiset<Key>::swap(multiset &other) {
  RBTree<Key, size_t> *temp_tree = this->_tree;
  size_t temp_size = this->_size;
  this->_size = other._size;
  other._size = temp_size;
  this->_tree = other._tree;
  other._tree = temp_tree;
}

template <typename Key>
void multiset<Key>::merge(multiset &other) {
  std::vector<Key> moved_values;
  for (MultisetIterator start = other.begin(); start != other.end(); start++) {
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
typename multiset<Key>::size_type multiset<Key>::count(const Key &key) {
  auto found_node = _tree->findNode(key);
  if (found_node != nullptr) {
    return found_node->value.second;
  } else {
    return 0;
  }
}

template <typename Key>
bool multiset<Key>::contains(const Key &key) {
  auto node = _tree->findNode(key);
  if (node == nullptr) {
    return false;
  }
  return true;
}

template <typename Key>
std::pair<typename multiset<Key>::iterator, typename multiset<Key>::iterator>
multiset<Key>::equal_range(const Key &key) {
  multiset<Key>::iterator start_iter = find(key);
  multiset<Key>::iterator end_iter = find(key);
  size_t key_count = count(key);
  for (size_t i = 0; i < key_count - 1; i++) {
    end_iter++;
  }
  return std::pair<multiset<Key>::iterator, multiset<Key>::iterator>(start_iter,
                                                                     end_iter);
}

template <typename Key>
typename multiset<Key>::iterator multiset<Key>::lower_bound(const Key &key) {
  auto found_node = _tree->findLowerBoundNode(key);
  if (found_node == nullptr) {
    return end();
  }
  return multiset<Key>::iterator(_tree, found_node);
}

template <typename Key>
typename multiset<Key>::iterator multiset<Key>::upper_bound(const Key &key) {
  auto found_node = _tree->findLowerBoundNode(key);
  if (found_node == nullptr) {
    return end();
  } else {
    if (key == found_node->value.first) {
      return multiset<Key>::iterator(_tree, _tree->nextNode(found_node));
    } else {
      return multiset<Key>::iterator(_tree, found_node);
    }
  }
}

template <typename Key>
typename multiset<Key>::iterator multiset<Key>::find(const Key &key) {
  return multiset<Key>::iterator(_tree, _tree->findNode(key));
}

template <typename Key>
template <class... Args>
vector<std::pair<typename multiset<Key>::iterator, bool>>
multiset<Key>::insert_many(Args &&...args) {
  vector<std::pair<iterator, bool>> res{};
  for (const auto &arg : {args...}) {
    res.push_back(insert(arg));
  }
  return res;
}

}  // namespace ps

#endif
