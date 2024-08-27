#include <gtest/gtest.h>

#include "../src/ps_rb_tree.h"

using namespace ps;

TEST(RBNodeInsert, insert_test) {
  auto tree = RBTree<int, int>{};
  std::pair<const int, int> p1 = {6, 6};
  tree.insert(p1);
  std::pair<const int, int> p2 = {7, 7};
  tree.insert(p2);
  std::pair<const int, int> p3 = {8, 8};
  tree.insert(p3);

  auto pair = tree.find(8);
  ASSERT_EQ(pair.first, 8);
}

TEST(RBNodeInsert, insert_not_exists_test) {
  auto tree = RBTree<int, int>{};
  std::pair<const int, int> p1 = {6, 6};
  tree.insert(p1);
  std::pair<const int, int> p2 = {7, 7};
  tree.insert(p2);

  ASSERT_EQ(tree.contains(8), false);
}

TEST(RBNodeInsert, insert_multiple_nodes_test) {
  auto tree = RBTree<int, int>{};
  std::pair<const int, int> p1 = {0, 0};
  tree.insert(p1);
  std::pair<const int, int> p2 = {10, 10};
  tree.insert(p2);

  std::pair<const int, int> p3 = {15, 15};
  tree.insert(p3);

  std::pair<const int, int> p4 = {12, 12};
  tree.insert(p4);

  auto pair = tree.find(12);
  ASSERT_EQ(pair.first, 12);
}

TEST(RBNodeDelete, delete_node) {
  auto tree = RBTree<int, int>{};
  std::pair<const int, int> p1 = {0, 0};
  tree.insert(p1);
  std::pair<const int, int> p2 = {10, 10};
  tree.insert(p2);

  tree.del(10);
  ASSERT_EQ(tree.contains(10), false);
}

TEST(RBNodeDelete, delete_root) {
  auto tree = RBTree<int, int>{};
  std::pair<const int, int> p1 = {0, 0};
  tree.insert(p1);

  tree.del(0);
  ASSERT_EQ(tree.contains(0), false);
}

TEST(RBNodeDelete, delete_node_in_middle_tree) {
  auto tree = RBTree<int, int>{};
  std::pair<const int, int> p1 = {0, 0};
  tree.insert(p1);
  std::pair<const int, int> p2 = {10, 10};
  tree.insert(p2);

  std::pair<const int, int> p3 = {15, 15};
  tree.insert(p3);

  std::pair<const int, int> p4 = {12, 12};
  tree.insert(p4);

  tree.del(15);
  auto pair1 = tree.find(12);
  ASSERT_EQ(pair1.first, 12);
  tree.del(12);

  ASSERT_EQ(tree.contains(12), false);
}

TEST(RBTreeFind, findNextElement) {
  auto tree = RBTree<int, int>{};
  std::pair<const int, int> p1 = {0, 0};
  tree.insert(p1);
  std::pair<const int, int> p2 = {10, 10};
  tree.insert(p2);

  std::pair<const int, int> p3 = {15, 15};
  tree.insert(p3);

  std::pair<const int, int> p4 = {12, 12};
  tree.insert(p4);

  ps::rbnode<int, int> *min_node = tree.minNode();
  ASSERT_EQ(min_node->value.first, p1.first);

  ASSERT_EQ(tree.nextNode(min_node)->value.first, 10);
}
