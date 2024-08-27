#include <gtest/gtest.h>
#include <stdlib.h>
#include <time.h>

#include "../src/ps_map.h"

using namespace ps;

TEST(mapConstructors, constructor_creates_map) {
  map<int, int> my_map;
  ASSERT_EQ(my_map.contains(5), false);
  ASSERT_EQ(my_map.empty(), true);
}

TEST(mapConstructors, copy_constructor_copying_tree) {
  map<int, int> my_map;
  my_map[5] = 6;
  map<int, int> copy_map(my_map);
  ASSERT_EQ(copy_map[5], 6);
}

TEST(mapConstructors, copy_constructor_uses_different_memory) {
  map<int, int> my_map;
  my_map[5] = 6;
  map<int, int> copy_map(my_map);
  copy_map[5] = 7;
  ASSERT_EQ(my_map[5], 6);
}

TEST(mapConstructors, copy_assignment) {
  map<int, int> map_1;
  auto map_2 = map<int, int>{std::pair(4, 8), std::pair(5, 9)};
  map_1 = map_2;

  ASSERT_EQ(map_1[5], 9);
  ASSERT_EQ(map_1[4], 8);
}

TEST(mapConstructors, move_assignment) {
  map<int, int> map_1;
  auto map_2 = map<int, int>{std::pair(4, 8), std::pair(5, 9)};
  map_1 = std::move(map_2);

  ASSERT_EQ(map_1[5], 9);
  ASSERT_EQ(map_1[4], 8);
}

TEST(mapConstructors, move_constructor) {
  map<int, int> my_map;
  my_map[5] = 6;
  map<int, int> moved_map = std::move(my_map);
  ASSERT_EQ(moved_map.size(), 1);
  ASSERT_EQ(moved_map[5], 6);
}

TEST(mapConstructors, initializer_list_constructor) {
  using pair = std::pair<int, int>;
  map<int, int> my_map({pair(5, 5), pair(6, 6), pair(7, 7), pair(8, 8)});
  ASSERT_EQ(my_map.size(), 4);
  ASSERT_EQ(my_map.at(5), 5);
  ASSERT_EQ(my_map.at(6), 6);
}

TEST(mapModifiers, clear_map) {
  map<int, int> my_map;
  my_map[5] = 8;
  my_map[6] = 8;
  my_map[3] = 8;
  my_map.clear();
  ASSERT_EQ(my_map.contains(8), false);
  ASSERT_EQ(my_map.size(), 0);
  ASSERT_EQ(my_map.empty(), true);
}

TEST(mapModifiers, insert_map_pair) {
  map<int, int> my_map;
  std::pair<map<int, int>::iterator, bool> value_iterator =
      my_map.insert(std::pair<int, int>(5, 6));

  ASSERT_EQ(value_iterator.second, true);
  ASSERT_EQ(my_map[5], 6);
}

TEST(mapModifiers, insert_map_pair_twice) {
  map<int, int> my_map;
  my_map.insert(std::pair<int, int>(5, 6));
  std::pair<map<int, int>::iterator, bool> value_iterator =
      my_map.insert(std::pair<int, int>(5, 7));

  ASSERT_EQ(value_iterator.second, false);
  ASSERT_EQ(my_map[5], 6);
}

TEST(mapModifiers, insert_or_assign_map) {
  map<int, int> my_map;
  std::pair<map<int, int>::iterator, bool> value_iterator =
      my_map.insert_or_assign(5, 7);

  ASSERT_EQ(value_iterator.second, true);
  ASSERT_EQ(my_map[5], 7);
}

TEST(mapModifiers, insert_or_assign_map_twice) {
  map<int, int> my_map;
  my_map.insert(std::pair<int, int>(5, 6));
  std::pair<map<int, int>::iterator, bool> value_iterator =
      my_map.insert_or_assign(5, 7);

  ASSERT_EQ(value_iterator.second, false);
  ASSERT_EQ(my_map[5], 7);
}

TEST(mapModifiers, insert_map_key_value) {
  map<int, int> my_map;
  my_map[3] = 4;
  std::pair<map<int, int>::iterator, bool> value_iterator = my_map.insert(5, 6);

  ASSERT_EQ(my_map.contains(8), false);
  ASSERT_EQ(my_map[5], 6);
}

TEST(mapModifiers, erase_map) {
  map<int, int> my_map;
  my_map[3] = 4;
  std::pair<map<int, int>::iterator, bool> inserted_pair = my_map.insert(5, 6);

  my_map.erase(my_map.begin());

  ASSERT_EQ(my_map.contains(3), false);
  ASSERT_EQ(my_map.contains(5), true);
}

TEST(mapModifiers, swap_map) {
  map<char, int> foo, bar;

  foo['x'] = 100;
  foo['y'] = 200;

  bar['a'] = 11;
  bar['b'] = 22;
  bar['c'] = 33;

  foo.swap(bar);

  ASSERT_EQ(foo['a'], 11);
  ASSERT_EQ(foo['b'], 22);
  ASSERT_EQ(foo['c'], 33);
  ASSERT_EQ(foo.size(), 3);
  ASSERT_EQ(bar['x'], 100);
  ASSERT_EQ(bar['y'], 200);
  ASSERT_EQ(bar.size(), 2);
}

TEST(mapModifiers, merge_map) {
  map<int, std::string> ma{{1, "apple"}, {5, "pear"}, {10, "banana"}};
  map<int, std::string> mb{
      {2, "zorro"}, {4, "batman"}, {5, "X"}, {8, "alpaca"}};
  map<int, std::string> u;
  u.merge(ma);
  ASSERT_EQ(ma.empty(), true);
  u.merge(mb);
  ASSERT_EQ(mb.size(), 1);

  ASSERT_EQ(mb.at(5), "X");

  ASSERT_EQ(u.at(1), "apple");
  ASSERT_EQ(u.at(2), "zorro");
  ASSERT_EQ(u.at(4), "batman");
  ASSERT_EQ(u.at(5), "pear");
  ASSERT_EQ(u.at(8), "alpaca");
  ASSERT_EQ(u.at(10), "banana");
}

TEST(mapIterators, begin_iterator) {
  map<int, int> foo;

  foo.insert(5, 6);
  foo.insert(7, 8);
  foo.insert(9, 10);
  foo.insert(4, 3);

  auto iterator = foo.begin();
  using pair = std::pair<const int, int>;
  ASSERT_EQ(*iterator, pair(4, 3));
  iterator++;
  ASSERT_EQ(*iterator, pair(5, 6));
  iterator++;
  ASSERT_EQ(*iterator, pair(7, 8));
  iterator++;
  ASSERT_EQ(*iterator, pair(9, 10));
}

TEST(mapIterators, end_iterator) {
  map<int, int> foo;

  foo.insert(5, 6);
  foo.insert(7, 8);
  foo.insert(9, 10);
  foo.insert(4, 3);

  auto iterator = foo.end();

  using pair = std::pair<const int, int>;
  iterator--;
  ASSERT_EQ(*iterator, pair(9, 10));
  iterator--;
  ASSERT_EQ(*iterator, pair(7, 8));
  iterator--;
  ASSERT_EQ(*iterator, pair(5, 6));
  iterator--;
  ASSERT_EQ(*iterator, pair(4, 3));
}

TEST(mapRandomTest, random_test) {
  map<int, int> foo;
  std::map<int, int> bar;
  srand(static_cast<uint>(time(nullptr)));

  auto random_numbers = std::vector<int>{};
  for (int i = 0; i < 100; i++) {
    random_numbers.push_back(rand() % 1000);
  }
  for (auto i : random_numbers) {
    foo.insert(std::pair<int, int>(i, i));
    bar.insert(std::pair<int, int>(i, i));
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

TEST(mapRandomTest, insert_case_infinity_iteration_case) {
  map<int, int> foo;
  foo.insert(std::pair<int, int>(358, 0));
  foo.insert(std::pair<int, int>(80, 0));
  foo.insert(std::pair<int, int>(242, 0));
  foo.insert(std::pair<int, int>(883, 0));
  foo.insert(std::pair<int, int>(814, 0));
  foo.insert(std::pair<int, int>(679, 0));
  foo.insert(std::pair<int, int>(436, 0));
  foo.insert(std::pair<int, int>(142, 0));
  foo.insert(std::pair<int, int>(225, 0));
  foo.insert(std::pair<int, int>(298, 0));
  foo.insert(std::pair<int, int>(387, 0));
  ASSERT_EQ(foo.size(), 11);
}

TEST(mapRandomTest, erase_case_segfault) {
  map<int, int> foo;
  auto insertion_arr =
      std::array<int, 10>{{686, 687, 407, 220, 653, 42, 608, 623, 504, 632}};
  auto erase_arr = std::array<int, 5>{{407, 632, 653, 220, 608}};

  for (auto i : insertion_arr) {
    foo.insert(std::pair<int, int>(i, 0));
  }

  for (auto i : erase_arr) {
    foo.erase(i);
  }
  ASSERT_EQ(foo.size(), 5);
}

TEST(mapRandomTest, erase_case_segfault2) {
  map<int, int> foo;
  auto insertion_arr =
      std::array<int, 10>{{555, 958, 102, 868, 532, 731, 215, 858, 50, 947}};
  auto erase_arr =
      std::array<int, 10>{{215, 555, 947, 868, 532, 958, 50, 858, 731, 102}};

  for (auto i : insertion_arr) {
    foo.insert(std::pair<int, int>(i, 0));
  }

  for (auto i : erase_arr) {
    foo.erase(i);
  }
  ASSERT_EQ(foo.empty(), true);
}

TEST(mapRandomTest, erase_case_segfault3) {
  map<int, int> foo;
  auto insertion_arr =
      std::array<int, 10>{{195, 281, 174, 96, 211, 27, 102, 401, 346, 942}};
  auto erase_arr = std::array<int, 5>{{401, 102, 27, 942, 195}};

  for (auto i : insertion_arr) {
    foo.insert(std::pair<int, int>(i, 0));
  }

  for (auto i : erase_arr) {
    foo.erase(i);
  }
  ASSERT_EQ(foo.size(), 5);
}

TEST(mapModifiers, max_size_int) {
  using pair = std::pair<int, int>;
  map<int, double> my_map({pair(5, 5.89), pair(6, 6), pair(7, 7), pair(8, 8)});
  std::map<int, double> std_map(
      {pair(5, 5.89), pair(6, 6), pair(7, 7), pair(8, 8)});
  ASSERT_EQ(my_map.max_size(), std_map.max_size());
}

TEST(mapModifiers, insert_many_test_1) {
  map<int, int> foo;
  using pair = std::pair<const int, int>;
  foo.insert_many(pair(5, 6), pair(9, 10), pair(7, 8), pair(4, 3));
  auto iterator = foo.begin();
  ASSERT_EQ(*iterator, pair(4, 3));
  iterator++;
  ASSERT_EQ(*iterator, pair(5, 6));
  iterator++;
  ASSERT_EQ(*iterator, pair(7, 8));
  iterator++;
  ASSERT_EQ(*iterator, pair(9, 10));
}

TEST(mapModifiers, insert_many_test_2) {
  using pair = std::pair<const int, int>;
  map<int, int> foo({pair(1, 2), pair(12, 0)});
  foo.insert_many(pair(5, 6), pair(9, 10), pair(7, 8), pair(4, 3));
  auto iterator = foo.begin();
  ASSERT_EQ(*iterator, pair(1, 2));
  iterator++;
  ASSERT_EQ(*iterator, pair(4, 3));
  iterator++;
  ASSERT_EQ(*iterator, pair(5, 6));
  iterator++;
  ASSERT_EQ(*iterator, pair(7, 8));
  iterator++;
  ASSERT_EQ(*iterator, pair(9, 10));
  iterator++;
  ASSERT_EQ(*iterator, pair(12, 0));
}

TEST(mapGroup, iterators_test_1) {
  using pair = std::pair<int, double>;
  const map<int, double> my_map(
      {pair(5, 5.89), pair(6, 6), pair(7, 7), pair(8, 8)});
  const std::map<int, double> std_map(
      {pair(5, 5.89), pair(6, 6), pair(7, 7), pair(8, 8)});
  auto my_iter = my_map.begin();
  auto std_iter = std_map.begin();
  ASSERT_EQ(*my_iter, *std_iter);
  my_iter++;
  std_iter++;
  ASSERT_EQ(*my_iter, *std_iter);
  my_iter--;
  std_iter--;
  ASSERT_EQ(*my_iter, *std_iter);
  auto my_iter2 = my_map.end();
  auto std_iter2 = std_map.end();
  --my_iter2;
  --std_iter2;
  ASSERT_EQ(*my_iter2, *std_iter2);
  --my_iter2;
  ++my_iter;
  ++my_iter;
  EXPECT_TRUE(my_iter2 == my_iter);
  ASSERT_EQ(my_map.at(6), std_map.at(6));
  ASSERT_ANY_THROW(my_map.at(2));
  ASSERT_EQ(my_map[6], 6);
}

TEST(mapGroup, iterators_test_2) {
  using pair = std::pair<const int, int>;
  map<int, int> foo({pair(1, 2), pair(12, 0), pair(3, 8)});
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

TEST(mapGroup, test_3) {
  using pair = std::pair<int, int>;
  map<int, int> my_map({pair(5, 5), pair(6, 6), pair(7, 7), pair(8, 8)});
  std::map<int, int> std_map({pair(5, 5), pair(6, 6), pair(7, 7), pair(8, 8)});
  auto iter1 = my_map.begin();
  auto iter2 = my_map.end();
  EXPECT_FALSE(iter1 == iter2);
  my_map.insert(pair(3, 4));
  std_map.insert(pair(3, 4));
  map<int, int> my_map2({pair(6, 7), pair(3, 6), pair(1, 5), pair(10, 9)});
  std::map<int, int> std_map2(
      {pair(6, 7), pair(3, 6), pair(1, 5), pair(10, 9)});
  my_map.merge(my_map2);
  std_map.merge(std_map2);
  ASSERT_EQ(my_map.size(), std_map.size());
  my_map.erase(5);
  std_map.erase(5);
  ASSERT_EQ(my_map.size(), std_map.size());
  auto my_iter = my_map.begin();
  auto std_iter = std_map.begin();
  for (size_t i = 0; i < my_map.size(); i++) {
    ASSERT_EQ(*my_iter, *std_iter);
    my_iter++;
    std_iter++;
  }
}

TEST(mapGroup, test_4) {
  using pair = std::pair<int, int>;
  map<int, int> my_map({pair(5, 5), pair(6, 6), pair(7, 7), pair(8, 8)});
  std::map<int, int> std_map({pair(5, 5), pair(6, 6), pair(7, 7), pair(8, 8)});
  map<int, int> my_map2({pair(6, 7), pair(3, 6), pair(1, 5), pair(10, 9)});
  std::map<int, int> std_map2(
      {pair(6, 7), pair(3, 6), pair(1, 5), pair(10, 9)});
  my_map.swap(my_map2);
  std_map.swap(std_map2);
  ASSERT_EQ(my_map.size(), std_map.size());
  ASSERT_EQ(my_map2.size(), std_map2.size());
  auto my_iter = my_map.begin();
  auto std_iter = std_map.begin();
  EXPECT_ANY_THROW(my_map.at(17));
  for (size_t i = 0; i < my_map.size(); i++) {
    ASSERT_EQ(*my_iter, *std_iter);
    my_iter++;
    std_iter++;
  }
  my_map.clear();
  std_map.clear();
  ASSERT_EQ(my_map.size(), std_map.size());
}