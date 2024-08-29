#include <gtest/gtest.h>
#include <time.h>

#include "../src/ps_multiset.h"

using namespace ps;

TEST(multisetConstructors, constructor_creates_multiset) {
  multiset<int> my_multiset;
  ASSERT_EQ(my_multiset.contains(5), false);
  ASSERT_EQ(my_multiset.empty(), true);
}

TEST(multisetConstructors, copy_constructor_copying_tree) {
  multiset<int> my_multiset;
  my_multiset.insert(5);
  multiset<int> copy_multiset(my_multiset);
  ASSERT_EQ(copy_multiset.contains(5), true);
}

TEST(multisetConstructors, copy_constructor_uses_different_memory) {
  multiset<int> my_multiset;
  my_multiset.insert(5);
  multiset<int> copy_multiset(my_multiset);
  ASSERT_EQ(copy_multiset.contains(5), true);
}

TEST(multisetConstructors, move_constructor) {
  multiset<int> my_multiset;
  my_multiset.insert(5);
  multiset<int> moved_multiset = std::move(my_multiset);
  ASSERT_EQ(moved_multiset.size(), 1);
  ASSERT_EQ(moved_multiset.contains(5), true);
}

TEST(multisetConstructors, copy_assignment) {
  multiset<int> multiset_1;
  auto multiset_2 = multiset<int>{4, 5};
  multiset_1 = multiset_2;

  ASSERT_EQ(multiset_1.contains(5), true);
  ASSERT_EQ(multiset_1.contains(4), true);
}

TEST(multisetConstructors, move_assignment) {
  multiset<int> multiset_1;
  auto multiset_2 = multiset<int>{4, 5};
  multiset_1 = std::move(multiset_2);

  ASSERT_EQ(multiset_1.contains(5), true);
  ASSERT_EQ(multiset_1.contains(4), true);
}

TEST(multisetConstructors, initializer_list_constructor) {
  multiset<int> my_multiset({5, 6, 7, 8});
  ASSERT_EQ(my_multiset.size(), 4);
  ASSERT_EQ(my_multiset.contains(5), true);
  ASSERT_EQ(my_multiset.contains(6), true);
}

TEST(multisetModifiers, clear_multiset) {
  multiset<int> my_multiset;
  my_multiset.insert(5);
  my_multiset.insert(6);
  my_multiset.insert(3);
  my_multiset.clear();
  ASSERT_EQ(my_multiset.contains(8), false);
  ASSERT_EQ(my_multiset.size(), 0);
  ASSERT_EQ(my_multiset.empty(), true);
}

TEST(multisetModifiers, insert_multiset_pair) {
  multiset<int> my_multiset;
  std::pair<multiset<int>::iterator, bool> value_iterator =
      my_multiset.insert(5);

  ASSERT_EQ(value_iterator.second, true);
  ASSERT_EQ(my_multiset.contains(5), true);
}

TEST(multisetModifiers, insert_multiset_pair_twice) {
  multiset<int> my_multiset;
  my_multiset.insert(5);
  std::pair<multiset<int>::iterator, bool> value_iterator =
      my_multiset.insert(5);

  ASSERT_EQ(value_iterator.second, false);
  ASSERT_EQ(my_multiset.contains(5), true);
}

TEST(multisetModifiers, insert_multiset_key_value) {
  multiset<int> my_multiset;
  my_multiset.insert(3);
  std::pair<multiset<int>::iterator, bool> value_iterator =
      my_multiset.insert(5);

  ASSERT_EQ(my_multiset.contains(8), false);
  ASSERT_EQ(my_multiset.contains(5), true);
}

TEST(multisetModifiers, erase_multiset) {
  multiset<int> my_multiset;
  my_multiset.insert(3);
  std::pair<multiset<int>::iterator, bool> inserted_pair =
      my_multiset.insert(5);

  my_multiset.erase(my_multiset.begin());

  ASSERT_EQ(my_multiset.contains(3), false);
  ASSERT_EQ(my_multiset.contains(5), true);
  ASSERT_EQ(my_multiset.size(), 1);
}

TEST(multisetModifiers, swap_multiset) {
  multiset<char> foo, bar;

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

TEST(multisetModifiers, merge_multiset) {
  multiset<int> ma{1, 5, 10};
  multiset<int> mb{2, 4, 5, 8};
  multiset<int> u;
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

TEST(multisetIterators, begin_iterator) {
  multiset<int> foo;

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

TEST(multisetIterators, end_iterator) {
  multiset<int> foo;

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

TEST(multisetIterators, iterate_over_iterator) {
  multiset<int> foo{5, 7, 9, 4};
  std::multiset<int> bar{5, 7, 9, 4};

  auto bar_iterator = bar.begin();

  int counter = 0;
  for (multiset<int>::iterator i = foo.begin(); i != foo.end(); i++) {
    counter++;
    ASSERT_EQ(*i, *bar_iterator);
    bar_iterator++;
  }
  ASSERT_EQ(counter, 4);
}

TEST(multisetRandomTest, random_test) {
  multiset<int> foo;
  std::multiset<int> bar;
  srand(static_cast<uint>(time(nullptr)));

  auto random_numbers = std::vector<int>{};
  for (int i = 0; i < 100; i++) {
    random_numbers.push_back(rand() % 1000);
  }
  for (auto i : random_numbers) {
    foo.insert(i);
    bar.insert(i);
  }
  ASSERT_EQ(foo.size(), bar.size());

  auto saved_random_numbers = std::vector<int>{random_numbers};
  auto saved_random_numbers_erase_order = std::vector<int>{};

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

// TEST(multisetModifiers, max_size) {
//   ps::multiset<int> my_multiset{2, 4, 5, 8};
//   multiset<int> std_multiset{3, 7, 2, 4, 5, 8};
//   ASSERT_EQ(my_multiset.max_size(), std_multiset.max_size());
// }

TEST(multisetModifiers, insert_many) {
  multiset<int> my_multiset({5, 7, 2});
  my_multiset.insert_many(3, 5, 1);
  ASSERT_EQ(my_multiset.size(), 6);

  auto iterator = my_multiset.end();
  iterator--;
  ASSERT_EQ(*iterator, 7);
  iterator--;
  ASSERT_EQ(*iterator, 5);
  iterator--;
  ASSERT_EQ(*iterator, 5);
  iterator--;
  ASSERT_EQ(*iterator, 3);
  iterator--;
  ASSERT_EQ(*iterator, 2);
  iterator--;
  ASSERT_EQ(*iterator, 1);
}
TEST(multisetLookups, count) {
  multiset<int> my_multiset({5, 7, 2});
  my_multiset.insert_many(3, 5, 1);
  ASSERT_EQ(my_multiset.count(5), 2);
}

TEST(multisetLookups, equal_range) {
  multiset<int> my_multiset({5, 7, 2});
  my_multiset.insert_many(3, 5, 1);
  auto iterators = my_multiset.equal_range(5);

  ASSERT_EQ(*iterators.first, 5);
  ASSERT_EQ(*iterators.second, 5);
  --iterators.first;
  ++iterators.second;
  ASSERT_EQ(*iterators.first, 3);
  ASSERT_EQ(*iterators.second, 7);
}

TEST(multisetLookups, lower_upper_bound) {
  multiset<int> my_multiset({5, 7, 2});
  my_multiset.insert_many(3, 5, 1);
  auto iterator_lower_bound = my_multiset.lower_bound(5);
  auto iterator_upper_bound = my_multiset.upper_bound(5);

  ASSERT_EQ(*iterator_lower_bound, 5);
  ASSERT_EQ(*iterator_upper_bound, 7);
}

TEST(multisetLookups, lower_upper_bound_end_of_map) {
  multiset<int> my_multiset({5, 7, 2});
  my_multiset.insert_many(3, 5, 1);
  auto iterator_lower_bound = my_multiset.lower_bound(7);
  auto iterator_upper_bound = my_multiset.upper_bound(7);

  ASSERT_EQ(*iterator_lower_bound, 7);
  ASSERT_EQ(iterator_upper_bound, my_multiset.end());
}

TEST(multisetLookups, lower_upper_bound_start_of_map) {
  multiset<int> my_multiset({5, 7, 2});
  my_multiset.insert_many(3, 5, 1);
  auto iterator_lower_bound = my_multiset.lower_bound(0);
  auto iterator_upper_bound = my_multiset.upper_bound(0);

  ASSERT_EQ(*iterator_lower_bound, 1);
  ASSERT_EQ(*iterator_upper_bound, 1);
}

TEST(multisetGroup, iterators_test_1) {
  const multiset<int> my_multiset{3, 5, 1, 9};
  const std::multiset<int> std_multiset{3, 5, 1, 9};
  auto my_iter = my_multiset.cbegin();
  auto std_iter = std_multiset.begin();
  ASSERT_EQ(*my_iter, *std_iter);
  my_iter++;
  std_iter++;
  ASSERT_EQ(*my_iter, *std_iter);
  my_iter--;
  std_iter--;
  ASSERT_EQ(*my_iter, *std_iter);
  auto my_iter2 = my_multiset.end();
  auto std_iter2 = std_multiset.end();
  --my_iter2;
  --std_iter2;
  ASSERT_EQ(*my_iter2, *std_iter2);
  --my_iter2;
  ++my_iter;
  ++my_iter;
  EXPECT_TRUE(my_iter2 == my_iter);
}

TEST(multisetGroup, iterators_test_2) {
  multiset<int> foo{1, 12, 7};
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
