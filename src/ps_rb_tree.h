#ifndef CONTAINERS_SRC_PS_RB_TREE_H_
#define CONTAINERS_SRC_PS_RB_TREE_H_

#include <utility>

namespace ps {

enum Color {
  RED,
  BLACK,
};

template <typename K, typename V>
struct rbnode {
  std::pair<const K, V> value;
  struct rbnode *left = nullptr;
  struct rbnode *right = nullptr;
  struct rbnode *parent = nullptr;
  Color color = RED;
};

template <typename K, typename V>
class RBTree {
  struct rbnode<K, V> *_root = nullptr;
  struct rbnode<K, V> *_sentinelNode = nullptr;
  struct rbnode<K, V> *_endNode = nullptr;
  struct rbnode<K, V> *_startNode = nullptr;
  size_t _size = 0;

  void insertFixUp(rbnode<K, V> *z);
  void rotateRight(rbnode<K, V> *x);
  void rotateLeft(rbnode<K, V> *x);
  void transplant(rbnode<K, V> *u, rbnode<K, V> *v);
  void delFixUp(rbnode<K, V> *x);
  void clearNodeRecursive(rbnode<K, V> *x);

 public:
  rbnode<K, V> *findNode(K value);
  rbnode<K, V> *findLowerBoundNode(K value);

  rbnode<K, V> *minNode() const;
  rbnode<K, V> *maxNode() const;
  rbnode<K, V> *minNode(rbnode<K, V> *x) const;
  rbnode<K, V> *maxNode(rbnode<K, V> *x) const;
  rbnode<K, V> *nextNode(const rbnode<K, V> *x) const;
  rbnode<K, V> *prevNode(const rbnode<K, V> *x) const;
  size_t size();
  size_t max_size();

  RBTree();
  ~RBTree();
  rbnode<K, V> *insert(std::pair<const K, V> &value);
  std::pair<const K, V> &find(K value);
  bool contains(K value);
  void del(K key);
  void clear();
};

template <typename K, typename V>
RBTree<K, V>::RBTree() {
  _endNode = new rbnode<K, V>{};
  _startNode = new rbnode<K, V>{};
  _sentinelNode = new rbnode<K, V>{};
  _sentinelNode->color = BLACK;
  _sentinelNode->parent = _sentinelNode;
  _sentinelNode->left = _sentinelNode;
  _sentinelNode->right = _sentinelNode;
  _root = _sentinelNode;
}

template <typename K, typename V>
RBTree<K, V>::~RBTree() {
  clear();
  delete _sentinelNode;
  delete _startNode;
  delete _endNode;
}

template <typename K, typename V>
rbnode<K, V> *ps::RBTree<K, V>::insert(std::pair<const K, V> &value) {
  struct rbnode<K, V> *parent = _sentinelNode;
  struct rbnode<K, V> *tree = _root;

  while (tree != _sentinelNode) {
    parent = tree;
    if (value.first < tree->value.first) {
      tree = tree->left;
    } else if (value.first > tree->value.first) {
      tree = tree->right;
    } else {
      return nullptr;
    }
  }
  auto *node = new rbnode<K, V>{value};
  node->parent = parent;
  node->left = _sentinelNode;
  node->right = _sentinelNode;

  if (parent == _sentinelNode) {
    _root = node;
  } else if (value.first < parent->value.first) {
    parent->left = node;
  } else {
    parent->right = node;
  }
  _size++;
  node->color = RED;
  insertFixUp(node);

  return node;
}

template <typename K, typename V>
void RBTree<K, V>::insertFixUp(rbnode<K, V> *z) {
  while (z->parent != nullptr && z->parent->parent != nullptr &&
         z->parent->color == RED) {
    rbnode<K, V> *u;
    if (z->parent == z->parent->parent->left) {
      u = z->parent->parent->right;
      if (u->color == RED) {
        z->parent->color = BLACK;
        u->color = BLACK;
        z->parent->parent->color = RED;
        z = z->parent->parent;
      } else {
        if (z == z->parent->right) {
          z = z->parent;
          rotateLeft(z);
        }
        z->parent->color = BLACK;
        z->parent->parent->color = RED;
        rotateRight(z->parent->parent);
      }
    } else {
      u = z->parent->parent->left;
      if (u->color == RED) {
        z->parent->color = BLACK;
        u->color = BLACK;
        z->parent->parent->color = RED;
        z = z->parent->parent;
      } else {
        if (z == z->parent->left) {
          z = z->parent;
          rotateRight(z);
        }
        z->parent->color = BLACK;
        z->parent->parent->color = RED;
        rotateLeft(z->parent->parent);
      }
    }
  }
  _root->color = BLACK;
}

template <typename K, typename V>
void RBTree<K, V>::rotateLeft(rbnode<K, V> *x) {
  rbnode<K, V> *y = x->right;
  x->right = y->left;
  if (y->left != _sentinelNode) {
    y->left->parent = x;
  }
  y->parent = x->parent;
  if (x == x->parent->left) {
    x->parent->left = y;
  } else {
    x->parent->right = y;
  }
  if (x == _root) {
    _root = y;
  }
  y->left = x;
  x->parent = y;
}

template <typename K, typename V>
void RBTree<K, V>::rotateRight(rbnode<K, V> *x) {
  rbnode<K, V> *y = x->left;
  x->left = y->right;
  if (y->right != _sentinelNode) {
    y->right->parent = x;
  }
  y->parent = x->parent;
  if (x == x->parent->left) {
    x->parent->left = y;
  } else {
    x->parent->right = y;
  }
  if (x == _root) {
    _root = y;
  }
  y->right = x;
  x->parent = y;
}

template <typename K, typename V>
std::pair<const K, V> &ps::RBTree<K, V>::find(const K value) {
  auto node = findNode(value);

  return node->value;
}

template <typename K, typename V>
bool ps::RBTree<K, V>::contains(const K value) {
  auto node = findNode(value);

  return node != nullptr;
}

template <typename K, typename V>
rbnode<K, V> *ps::RBTree<K, V>::findNode(const K value) {
  auto tree = _root;
  while (tree != _sentinelNode) {
    if (value < tree->value.first) {
      tree = tree->left;
    } else if (value > tree->value.first) {
      tree = tree->right;
    } else {
      return tree;
    }
  }
  return nullptr;
}

template <typename K, typename V>
rbnode<K, V> *RBTree<K, V>::findLowerBoundNode(K value) {
  auto tree = _root;
  rbnode<K, V> *response_node = nullptr;
  while (tree != _sentinelNode) {
    if (value <= tree->value.first) response_node = tree;
    if (value < tree->value.first) {
      tree = tree->left;
    } else if (value > tree->value.first) {
      tree = tree->right;
    } else {
      return tree;
    }
  }
  return response_node;
}

template <typename K, typename V>
void RBTree<K, V>::del(K key) {
  rbnode<K, V> *z = findNode(key);
  if (z == nullptr) {
    return;
  }

  rbnode<K, V> *y = z;
  rbnode<K, V> *x;
  Color y_color = y->color;
  if (z->left == _sentinelNode) {
    x = z->right;
    transplant(z, z->right);
  } else if (z->right == _sentinelNode) {
    x = z->left;
    transplant(z, z->left);
  } else {
    y = minNode(z->right);
    y_color = y->color;
    x = y->right;
    if (y->parent == z) {
      x->parent = y;
    } else {
      transplant(y, y->right);
      y->right = z->right;
      y->right->parent = y;
    }
    transplant(z, y);
    y->left = z->left;
    y->left->parent = y;
    y->color = z->color;
  }
  if (y_color == BLACK) {
    delFixUp(x);
  }
  _size--;
  delete z;
}

template <typename K, typename V>
void RBTree<K, V>::clearNodeRecursive(rbnode<K, V> *x) {
  if (x->left != _sentinelNode) {
    clearNodeRecursive(x->left);
  }
  if (x->right != _sentinelNode) {
    clearNodeRecursive(x->right);
  }

  if (x == _root) {
    _root = _sentinelNode;
  }
  if (x != _sentinelNode) {
    delete x;
  }
}

template <typename K, typename V>
void RBTree<K, V>::clear() {
  if (_root != _sentinelNode) {
    clearNodeRecursive(_root);
    _size = 0;
  }
}

template <typename K, typename V>
void RBTree<K, V>::transplant(rbnode<K, V> *u, rbnode<K, V> *v) {
  if (u->parent == _sentinelNode) {
    _root = v;
  } else if (u == u->parent->left) {
    u->parent->left = v;
  } else {
    u->parent->right = v;
  }
  v->parent = u->parent;
}

template <typename K, typename V>
rbnode<K, V> *RBTree<K, V>::minNode(rbnode<K, V> *x) const {
  rbnode<K, V> *node = x;
  while (node->left != _sentinelNode) {
    node = node->left;
  }
  return node;
}

template <typename K, typename V>
rbnode<K, V> *RBTree<K, V>::minNode() const {
  return minNode(_root);
}

template <typename K, typename V>
rbnode<K, V> *RBTree<K, V>::maxNode(rbnode<K, V> *x) const {
  rbnode<K, V> *node = x;
  while (node->right != _sentinelNode) {
    node = node->right;
  }
  return node;
}

template <typename K, typename V>
rbnode<K, V> *RBTree<K, V>::maxNode() const {
  return maxNode(_root);
}

template <typename K, typename V>
rbnode<K, V> *RBTree<K, V>::nextNode(const rbnode<K, V> *x) const {
  rbnode<K, V> *max_node = maxNode();

  if (x == max_node) {
    return _endNode;
  }

  if (x == _startNode) {
    return minNode();
  }

  rbnode<K, V> *tree = _root;
  rbnode<K, V> *successor = nullptr;
  while (tree != _sentinelNode) {
    if (x->value.first < tree->value.first) {
      successor = tree;
      tree = tree->left;
    } else if (x->value.first > tree->value.first) {
      tree = tree->right;
    } else {
      if (tree->right != _sentinelNode) {
        return minNode(tree->right);
      }
      return successor;
    }
  }
  return nullptr;
}

template <typename K, typename V>
rbnode<K, V> *RBTree<K, V>::prevNode(const rbnode<K, V> *x) const {
  rbnode<K, V> *min_node = minNode();

  if (x == min_node) {
    return min_node - 1;
  }

  if (x == _endNode) {
    return maxNode();
  }

  rbnode<K, V> *tree = _root;
  rbnode<K, V> *predecessor = nullptr;
  while (tree != _sentinelNode) {
    if (x->value.first < tree->value.first) {
      tree = tree->left;
    } else if (x->value.first > tree->value.first) {
      predecessor = tree;
      tree = tree->right;
    } else {
      if (tree->left != _sentinelNode) {
        return maxNode(tree->left);
      }
      return predecessor;
    }
  }
  return nullptr;
}

template <typename K, typename V>
void RBTree<K, V>::delFixUp(rbnode<K, V> *x) {
  while (x != _root && x->color == BLACK) {
    if (x == x->parent->left) {
      rbnode<K, V> *w = x->parent->right;
      if (w->color == RED) {
        w->color = BLACK;
        x->parent->color = RED;
        rotateLeft(x->parent);
        w = x->parent->right;
      }
      if (w->left->color == BLACK && w->right->color == BLACK) {
        w->color = RED;
        x = x->parent;
      } else {
        if (w->right->color == BLACK) {
          w->left->color = BLACK;
          w->color = RED;
          rotateRight(w);
          w = x->parent->right;
        }
        w->color = x->parent->color;
        x->parent->color = BLACK;
        w->right->color = BLACK;
        rotateLeft(x->parent);
        x = _root;
      }
    } else {
      rbnode<K, V> *w = x->parent->left;
      if (w->color == RED) {
        w->color = BLACK;
        x->parent->color = RED;
        rotateRight(x->parent);
        w = x->parent->left;
      }
      if (w->right->color == BLACK && w->left->color == BLACK) {
        w->color = RED;
        x = x->parent;
      } else {
        if (w->left->color == BLACK) {
          w->right->color = BLACK;
          w->color = RED;
          rotateLeft(w);
          w = x->parent->left;
        }
        w->color = x->parent->color;
        x->parent->color = BLACK;
        w->left->color = BLACK;
        rotateRight(x->parent);
        x = _root;
      }
    }
  }
  x->color = BLACK;
}

template <typename K, typename V>
size_t RBTree<K, V>::size() {
  return _size;
}

template <typename K, typename V>
size_t RBTree<K, V>::max_size() {
  return std::numeric_limits<size_t>::max() / sizeof(rbnode<K, V>);
}

}  // namespace ps

#endif