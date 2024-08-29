#include <gtest/gtest.h>
#include <stdlib.h>
#include <time.h>

#include "../src/ps_set.h"

using namespace ps;

TEST(setConstructors, constructor_creates_set) {
  set<int> my_set;
  ASSERT_EQ(my_set.contains(5), false);
  ASSERT_EQ(my_set.empty(), true);
}

TEST(setConstructors, copy_constructor_copying_tree) {
  // std::setbuf(stdout, nullptr);
  set<int> my_set;
  my_set.insert(5);
  set<int> copy_set(my_set);
  ASSERT_EQ(copy_set.contains(5), true);
}

TEST(setConstructors, copy_constructor_uses_different_memory) {
  set<int> my_set;
  my_set.insert(5);
  set<int> copy_set(my_set);
  ASSERT_EQ(copy_set.contains(5), true);
}

TEST(setConstructors, move_constructor) {
  set<int> my_set;
  my_set.insert(5);
  set<int> moved_set = std::move(my_set);
  ASSERT_EQ(moved_set.size(), 1);
  ASSERT_EQ(moved_set.contains(5), true);
}

TEST(setConstructors, copy_assignment) {
  set<int> set_1;
  auto set_2 = set<int>{4, 5};
  set_1 = set_2;

  ASSERT_EQ(set_1.contains(5), true);
  ASSERT_EQ(set_1.contains(4), true);
}

TEST(setConstructors, move_assignment) {
  set<int> set_1;
  auto set_2 = set<int>{4, 5};
  set_1 = std::move(set_2);

  ASSERT_EQ(set_1.contains(5), true);
  ASSERT_EQ(set_1.contains(4), true);
}

TEST(setConstructors, initializer_list_constructor) {
  set<int> my_set({5, 6, 7, 8});
  ASSERT_EQ(my_set.size(), 4);
  ASSERT_EQ(my_set.contains(5), true);
  ASSERT_EQ(my_set.contains(6), true);
}

TEST(setModifiers, clear_set) {
  set<int> my_set;
  my_set.insert(5);
  my_set.insert(6);
  my_set.insert(3);
  my_set.clear();
  ASSERT_EQ(my_set.contains(8), false);
  ASSERT_EQ(my_set.size(), 0);
  ASSERT_EQ(my_set.empty(), true);
}

TEST(setModifiers, insert_set_pair) {
  set<int> my_set;
  std::pair<set<int>::iterator, bool> value_iterator = my_set.insert(5);

  ASSERT_EQ(value_iterator.second, true);
  ASSERT_EQ(my_set.contains(5), true);
}

TEST(setModifiers, insert_set_pair_twice) {
  set<int> my_set;
  my_set.insert(5);
  std::pair<set<int>::iterator, bool> value_iterator = my_set.insert(5);

  ASSERT_EQ(value_iterator.second, false);
  ASSERT_EQ(my_set.contains(5), true);
}

TEST(setModifiers, insert_set_key_value) {
  set<int> my_set;
  my_set.insert(3);
  std::pair<set<int>::iterator, bool> value_iterator = my_set.insert(5);

  ASSERT_EQ(my_set.contains(8), false);
  ASSERT_EQ(my_set.contains(5), true);
}

TEST(setModifiers, erase_set) {
  set<int> my_set;
  my_set.insert(3);
  std::pair<set<int>::iterator, bool> inserted_pair = my_set.insert(5);

  my_set.erase(my_set.begin());

  ASSERT_EQ(my_set.contains(3), false);
  ASSERT_EQ(my_set.contains(5), true);
  ASSERT_EQ(my_set.size(), 1);
}

TEST(setModifiers, swap_set) {
  set<char> foo, bar;

  foo.insert('x');
  foo.insert('y');

  bar.insert('a');
  bar.insert('b');
  bar.insert('c');

  foo.swap(bar);

  ASSERT_EQ(foo.contains('a'), true);
  ASSERT_EQ(foo.contains('b'), true);
  ASSERT_EQ(foo.contains('c'), true);
  ASSERT_EQ(foo.size(), 3);
  ASSERT_EQ(bar.contains('x'), true);
  ASSERT_EQ(bar.contains('y'), true);
  ASSERT_EQ(bar.size(), 2);
}

TEST(setModifiers, merge_set) {
  set<int> ma{1, 5, 10};
  set<int> mb{2, 4, 5, 8};
  set<int> u;
  u.merge(ma);
  ASSERT_EQ(ma.empty(), true);
  u.merge(mb);
  ASSERT_EQ(mb.size(), 1);

  ASSERT_EQ(mb.contains(5), true);

  ASSERT_EQ(u.contains(1), true);
  ASSERT_EQ(u.contains(2), true);
  ASSERT_EQ(u.contains(4), true);
  ASSERT_EQ(u.contains(5), true);
  ASSERT_EQ(u.contains(8), true);
  ASSERT_EQ(u.contains(10), true);
}

// TEST(setModifiers, max_size) {
//   ps::set<int> my_set{2, 4, 5, 8};
//   set<int> std_set{3, 7, 2, 4, 5, 8};
//   ASSERT_EQ(my_set.max_size(), std_set.max_size());
// }

TEST(setIterators, begin_iterator) {
  set<int> foo;

  foo.insert(5);
  foo.insert(7);
  foo.insert(9);
  foo.insert(4);

  auto iterator = foo.begin();
  ASSERT_EQ(*iterator, 4);
  iterator++;
  ASSERT_EQ(*iterator, 5);
  iterator++;
  ASSERT_EQ(*iterator, 7);
  iterator++;
  ASSERT_EQ(*iterator, 9);
}

TEST(setIterators, end_iterator) {
  set<int> foo;

  foo.insert(5);
  foo.insert(7);
  foo.insert(9);
  foo.insert(4);

  auto iterator = foo.end();

  iterator--;
  ASSERT_EQ(*iterator, 9);
  iterator--;
  ASSERT_EQ(*iterator, 7);
  iterator--;
  ASSERT_EQ(*iterator, 5);
  iterator--;
  ASSERT_EQ(*iterator, 4);
}

TEST(setIterators, iterate_over_iterator) {
  set<int> foo{5, 7, 9, 4};
  std::set<int> bar{5, 7, 9, 4};

  auto bar_iterator = bar.begin();

  int counter = 0;
  for (set<int>::iterator i = foo.begin(); i != foo.end(); i++) {
    counter++;
    ASSERT_EQ(*i, *bar_iterator);
    bar_iterator++;
  }
  ASSERT_EQ(counter, 4);
}

TEST(setRandomTest, random_test) {
  set<int> foo;
  std::set<int> bar;
  srand(static_cast<uint>(time(nullptr)));

  auto random_numbers = ps::vector<int>{};
  for (int i = 0; i < 100; i++) {
    random_numbers.push_back(rand() % 1000);
  }
  for (auto i : random_numbers) {
    foo.insert(i);
    bar.insert(i);
  }
  ASSERT_EQ(foo.size(), bar.size());

  auto saved_random_numbers = ps::vector<int>{random_numbers};
  auto saved_random_numbers_erase_order = ps::vector<int>{};

  size_t random_numbers_size = random_numbers.size();
  for (size_t i = 0; i < random_numbers_size; i++) {
    size_t random_index = static_cast<size_t>(rand()) % (random_numbers.size());
    int number = random_numbers[random_index];
    random_numbers.erase(random_numbers.begin() +
                         static_cast<int>(random_index));

    saved_random_numbers_erase_order.push_back(number);

    foo.erase(number);
    bar.erase(number);
  }

  ASSERT_EQ(random_numbers.empty(), true);
  ASSERT_EQ(foo.empty(), true);
  ASSERT_EQ(bar.empty(), true);
}

TEST(setModifiers, insert_many) {
  set<int> my_set({5, 7, 2});
  my_set.insert_many(3, 5, 1);
  ASSERT_EQ(my_set.size(), 5);

  auto iterator = my_set.end();
  iterator--;
  ASSERT_EQ(*iterator, 7);
  iterator--;
  ASSERT_EQ(*iterator, 5);
  iterator--;
  ASSERT_EQ(*iterator, 3);
  iterator--;
  ASSERT_EQ(*iterator, 2);
  iterator--;
  ASSERT_EQ(*iterator, 1);
}

TEST(setGroup, iterators_test_1) {
  const set<int> my_set{3, 5, 1, 9};
  const std::set<int> std_set{3, 5, 1, 9};
  auto my_iter = my_set.cbegin();
  auto std_iter = std_set.begin();
  ASSERT_EQ(*my_iter, *std_iter);
  my_iter++;
  std_iter++;
  ASSERT_EQ(*my_iter, *std_iter);
  my_iter--;
  std_iter--;
  ASSERT_EQ(*my_iter, *std_iter);
  auto my_iter2 = my_set.end();
  auto std_iter2 = std_set.end();
  --my_iter2;
  --std_iter2;
  ASSERT_EQ(*my_iter2, *std_iter2);
  --my_iter2;
  ++my_iter;
  ++my_iter;
  EXPECT_TRUE(my_iter2 == my_iter);
}

TEST(setGroup, iterators_test_2) {
  set<int> foo{1, 12, 7};
  auto iter1 = foo.begin();
  auto iter2 = foo.cend();
  EXPECT_FALSE(iter1 == iter2);
  EXPECT_TRUE(iter1 != iter2);
  iter1++;
  iter2--;
  iter2--;
  EXPECT_TRUE(iter2 == iter1);
  EXPECT_FALSE(iter2 != iter1);
}

TEST(setGroup, test_3) {
  set<double> my_set{3.45, 6.789, 12.234, 9.456};
  std::set<double> std_set{3.45, 6.789, 12.234, 9.456};
  auto iter1 = my_set.begin();
  auto iter2 = my_set.end();
  EXPECT_FALSE(iter1 == iter2);
  my_set.insert(4.567);
  std_set.insert(4.567);
  set<double> my_set2{4.34, 5.67, 1.231};
  std::set<double> std_set2{4.34, 5.67, 1.231};
  my_set.merge(my_set2);
  std_set.merge(std_set2);
  ASSERT_EQ(my_set.size(), std_set.size());
  my_set.erase(6.789);
  std_set.erase(6.789);
  ASSERT_EQ(my_set.size(), std_set.size());
  auto my_iter = my_set.begin();
  auto std_iter = std_set.begin();
  for (size_t i = 0; i < my_set.size(); i++) {
    ASSERT_EQ(*my_iter, *std_iter);
    my_iter++;
    std_iter++;
  }
}

TEST(setGroup, test_4) {
  set<int> my_set{1, 5, 6, 2, 3, 10};
  std::set<int> std_set{1, 5, 6, 2, 3, 10};
  set<int> my_set2{5, 8, 2, 6};
  std::set<int> std_set2{5, 8, 2, 6};
  my_set.swap(my_set2);
  std_set.swap(std_set2);
  ASSERT_EQ(my_set.size(), std_set.size());
  ASSERT_EQ(my_set2.size(), std_set2.size());
  auto my_iter = my_set.begin();
  auto std_iter = std_set.begin();
  for (size_t i = 0; i < my_set.size(); i++) {
    ASSERT_EQ(*my_iter, *std_iter);
    my_iter++;
    std_iter++;
  }
  my_set.clear();
  std_set.clear();
  ASSERT_EQ(my_set.size(), std_set.size());
}