#include <gtest/gtest.h>

#include <vector>

#include "../src/ps_vector.h"

// Constructor tests

TEST(DefaultConstructorVector, Test_1) {
  auto vect1 = ps::vector<int>();
  auto vect2 = std::vector<int>();
  ASSERT_EQ(vect1.size(), vect2.size());
  ASSERT_EQ(vect1.capacity(), vect2.capacity());
  ASSERT_EQ(vect1.data(), vect2.data());
}

TEST(ParameterizedConstructorVector, Test_1) {
  auto vect1 = ps::vector<int>(3);
  auto vect2 = std::vector<int>(3);
  ASSERT_EQ(vect1.size(), vect2.size());
  ASSERT_EQ(vect1.capacity(), vect2.capacity());
}

TEST(InitializerListConstructorVector, Test_1) {
  ps::vector<int> vect1{1, 2, 3};
  std::vector<int> vect2{1, 2, 3};
  ASSERT_EQ(vect1.size(), vect2.size());
  ASSERT_EQ(vect1.capacity(), vect2.capacity());
  for (size_t i = 0; i < 3; ++i) {
    ASSERT_EQ(vect1[i], vect2[i]);
  }
}

TEST(CopyConstructorTestVector, Test_1) {
  ps::vector<int> vect1{1, 2, 3};
  auto ps_res(vect1);
  std::vector<int> vect2{1, 2, 3};
  auto std_res(vect2);
  for (size_t i = 0; i < 3; ++i) {
    ASSERT_EQ(ps_res[i], std_res[i]);
  }
}

TEST(MoveConstructorTestVector, Test_1) {
  ps::vector<int> vect1{0, 1, 2, 3, 4};
  auto ps_res(std::move(vect1));
  std::vector<int> vect2{0, 1, 2, 3, 4};
  auto std_res(std::move(vect2));
  for (size_t i = 0; i < 5; ++i) {
    ASSERT_EQ(ps_res[i], std_res[i]);
  }
  ASSERT_EQ(vect1.size(), vect2.size());
  ASSERT_EQ(vect1.capacity(), vect2.capacity());
  ASSERT_EQ(vect1.data(), vect2.data());
}

// Operator tests

TEST(CopyOperatorTestVector, Test_1) {
  const ps::vector<int> vect1{0, 1, 2, 3, 4};
  ps::vector<int> ps_res{1, 2, 3};
  ps_res = vect1;
  const std::vector<int> vect2{0, 1, 2, 3, 4};
  std::vector<int> std_res{1, 2, 3};
  std_res = vect2;
  for (size_t i = 0; i < ps_res.size(); ++i) {
    ASSERT_EQ(ps_res[i], std_res[i]);
  }
  for (size_t i = 0; i < vect1.size(); ++i) {
    ASSERT_EQ(vect1[i], vect2[i]);
  }
}

TEST(MoveOperatorTestVector, Test_1) {
  ps::vector<int> vect1{1, 2, 3};
  ps::vector<int> vect2;
  vect2 = std::move(vect1);
  EXPECT_EQ(vect2.size(), 3);
  EXPECT_TRUE(vect1.empty());
}

TEST(MoveOperatorTestVector, Test_2) {
  ps::vector<int> vect1{0, 1, 2, 3, 4};
  ps::vector<int> ps_res{};
  ps_res = std::move(vect1);
  std::vector<int> vect2{0, 1, 2, 3, 4};
  std::vector<int> std_res{};
  std_res = std::move(vect2);
  for (size_t i = 0; i < ps_res.size(); ++i) {
    ASSERT_EQ(ps_res[i], i);
  }
}

// Function tests

TEST(AtFunctionTestVector, Test_1) {
  auto vect = ps::vector<double>(5);
  EXPECT_THROW(vect.at(7), std::out_of_range);
}

TEST(AtConstFunctionTestVector, Test_2) {
  const auto vect = ps::vector<double>(0);
  ASSERT_ANY_THROW(vect.at(3));
}

TEST(AtFunctionTestVector, Test_3) {
  ps::vector<int> vect1{0, 1, 2};
  std::vector<int> vect2{0, 1, 2};
  ASSERT_EQ(vect1.at(2), vect2.at(2));
}

TEST(AtConstFunctionTestVector, Test_4) {
  const ps::vector<int> vect1{0, 1, 2};
  const std::vector<int> vect2{0, 1, 2};
  ASSERT_EQ(vect1.at(2), vect2.at(2));
}

TEST(FrontFunctionTestVector, Test_1) {
  ps::vector<int> vect1{5, 1, 2};
  std::vector<int> vect2{5, 1, 2};
  ASSERT_EQ(vect1.front(), vect2.front());
}

TEST(FrontConstFunctionTestVector, Test_1) {
  const ps::vector<int> vect1{8, 1, 2};
  const std::vector<int> vect2{8, 1, 2};
  ASSERT_EQ(vect1.front(), vect2.front());
}

TEST(BackConstFunctionTestVector, Test_1) {
  const ps::vector<int> vect1{5, 1, 2};
  const std::vector<int> vect2{5, 1, 2};
  ASSERT_EQ(vect1.back(), vect2.back());
}

TEST(BackFunctionTestVector, Test_1) {
  ps::vector<int> vect1{5, 1, 2, 7};
  std::vector<int> vect2{5, 1, 2, 7};
  ASSERT_EQ(vect1.back(), vect2.back());
}

TEST(DataFunctionTestVector, Test_1) {
  ps::vector<int> vect1{1, 2, 3, 4, 5};
  auto ptr1 = vect1.data();
  std::vector<int> vect2{1, 2, 3, 4, 5};
  auto ptr2 = vect2.data();
  EXPECT_EQ(*ptr1, *ptr2);
}

TEST(DataFunctionTestVector, Test_2) {
  ps::vector<int> vect1(0);
  auto ptr1 = vect1.data();
  std::vector<int> vect2(0);
  auto ptr2 = vect2.data();
  EXPECT_EQ(ptr1, ptr2);
}

TEST(DataConstFunctionTestVector, Test_3) {
  const ps::vector<int> vect{1, 2, 3, 4, 5};
  const auto ptr1 = vect.data();
  const std::vector<int> vect2{1, 2, 3, 4, 5};
  const auto ptr2 = vect2.data();
  EXPECT_EQ(*ptr1, *ptr2);
}

TEST(DataConstFunctionTestVector, Test_4) {
  const ps::vector<int> vect(0);
  const auto ptr1 = vect.data();
  const std::vector<int> vect2(0);
  const auto ptr2 = vect2.data();
  EXPECT_EQ(ptr1, ptr2);
}

TEST(BeginFunctionTestVector, Test_1) {
  ps::vector<int> vect1{1, 2, 3, 4, 5};
  auto ptr1 = vect1.begin();
  std::vector<int> vect2{1, 2, 3, 4, 5};
  auto ptr2 = vect2.begin();
  EXPECT_EQ(*ptr1, *ptr2);
}

TEST(BeginConstFunctionTestVector, Test_1) {
  const ps::vector<int> vect1{1, 2, 3, 4, 5};
  const auto ptr1 = vect1.begin();
  const std::vector<int> vect2{1, 2, 3, 4, 5};
  const auto ptr2 = vect2.begin();
  EXPECT_EQ(*ptr1, *ptr2);
}

TEST(BeginConstFunctionTestVector, Test_2) {
  const ps::vector<int> vect1{1, 2, 3, 4, 5};
  const auto ptr1 = vect1.begin();
  const std::vector<int> vect2{1, 2, 3, 4, 5};
  const auto ptr2 = vect2.begin();
  EXPECT_EQ(*ptr1, *ptr2);
}

TEST(СBeginFunctionTestVector, Test_3) {
  ps::vector<int> vect1{1, 2, 3, 4, 5};
  auto ptr1 = vect1.cbegin();
  const std::vector<int> vect2{1, 2, 3, 4, 5};
  const auto ptr2 = vect2.begin();
  EXPECT_EQ(*ptr1, *ptr2);
}

TEST(EndFunctionTestVector, Test_1) {
  ps::vector<int> vect1{1, 2, 3, 4, 5};
  auto ptr1 = vect1.end();
  --ptr1;
  std::vector<int> vect2{1, 2, 3, 4, 5};
  auto ptr2 = vect2.end();
  --ptr2;
  EXPECT_EQ(*ptr1, *ptr2);
}

TEST(EndConstFunctionTestVector, Test_2) {
  const ps::vector<int> vect1{1, 2, 3, 4, 8};
  auto ptr1 = vect1.end();
  --ptr1;
  const std::vector<int> vect2{1, 2, 3, 4, 8};
  auto ptr2 = vect2.end();
  --ptr2;
  EXPECT_EQ(*ptr1, *ptr2);
}

TEST(CEndFunctionTestVector, Test_3) {
  const ps::vector<int> vect1{1, 2, 3};
  auto ptr1 = vect1.cend();
  --ptr1;
  const std::vector<int> vect2{1, 2, 3};
  auto ptr2 = vect2.cend();
  --ptr2;
  EXPECT_EQ(*ptr1, *ptr2);
}

TEST(EmptyFunctionTestVector, Test_1) {
  auto vect1 = ps::vector<int>(4);
  bool res1 = vect1.empty();
  auto vect2 = std::vector<int>(4);
  bool res2 = vect2.empty();
  ASSERT_EQ(res1, res2);
}

TEST(EmptyFunctionTestVector, Test_2) {
  auto vect1 = ps::vector<int>(0);
  bool res1 = vect1.empty();
  auto vect2 = std::vector<int>(0);
  bool res2 = vect2.empty();
  ASSERT_EQ(res1, res2);
}

TEST(SizeFunctionTestVector, Test_1) {
  auto vect1 = ps::vector<int>(8);
  auto vect2 = std::vector<int>(8);
  ASSERT_EQ(vect1.size(), vect2.size());
}

TEST(MaxSizeFunctionTestVector, Test_1) {
  auto vect1 = ps::vector<int>(8);
  auto vect2 = std::vector<int>(8);
  ASSERT_EQ(vect1.max_size(), vect2.max_size());
}

TEST(ReserveFunctionTestVector, Test_1) {
  ps::vector<int> vect1{1, 2, 3};
  vect1.reserve(10);
  std::vector<int> vect2{1, 2, 3};
  vect2.reserve(10);
  ASSERT_EQ(vect1.size(), vect2.size());
  ASSERT_EQ(vect1.capacity(), vect2.capacity());
}

TEST(ReserveFunctionTestVector, Test_2) {
  ps::vector<int> vect1{1, 2, 3, 4, 5, 6, 7};
  vect1.reserve(5);
  std::vector<int> vect2{1, 2, 3, 4, 5, 6, 7};
  vect2.reserve(5);
  ASSERT_EQ(vect1.size(), vect2.size());
  ASSERT_EQ(vect1.capacity(), vect2.capacity());
}

TEST(ShrinkToFitFunctionTestVector, Test_2) {
  ps::vector<int> vect1{1, 2, 3, 4, 5};
  vect1.reserve(10);
  vect1.shrink_to_fit();
  std::vector<int> vect2{1, 2, 3, 4, 5};
  vect2.reserve(10);
  vect2.shrink_to_fit();
  ASSERT_EQ(vect1.size(), vect2.size());
  ASSERT_EQ(vect1.capacity(), vect2.capacity());
}

TEST(SwapFunctionTestVector, Test_1) {
  ps::vector<int> vect1{1, 2, 3, 4, 5};
  ps::vector<int> vect2{2, 1, 0};
  vect1.swap(vect2);
  std::vector<int> vect3{1, 2, 3, 4, 5};
  std::vector<int> vect4{2, 1, 0};
  vect3.swap(vect4);
  for (size_t i = 0; i < 5; ++i) {
    ASSERT_EQ(vect2[i], vect4[i]);
  }
  ASSERT_EQ(vect2.size(), vect4.size());
  int j = 2;
  for (size_t i = 0; i < 3; ++i) {
    ASSERT_EQ(vect1[i], j);
    --j;
  }
  ASSERT_EQ(vect1.size(), vect3.size());
}

TEST(ClearFunctionTestVector, Test_1) {
  auto vect1 = ps::vector<int>(4);
  vect1.clear();
  auto vect2 = std::vector<int>(4);
  vect2.clear();
  ASSERT_EQ(vect1.size(), vect2.size());
}

TEST(EraseFunctionTestVector, Test_1) {
  ps::vector<int> vect1{1, 2, 3, 4, 5, 6, 7};
  auto it1 = vect1.erase(vect1.begin());
  std::vector<int> vect2{1, 2, 3, 4, 5, 6, 7};
  auto it2 = vect2.erase(vect2.begin());
  ASSERT_EQ(vect1.size(), vect2.size());
  ASSERT_EQ(*it1, *it2);
}

TEST(EraseFunctionTestVector, Test_2) {
  ps::vector<int> vect1{1, 2, 3, 4, 5, 6, 7};
  auto it1 = vect1.erase(vect1.begin() + 5);
  std::vector<int> vect2{1, 2, 3, 4, 5, 6, 7};
  auto it2 = vect2.erase(vect2.begin() + 5);
  ASSERT_EQ(vect1.size(), vect2.size());
  ASSERT_EQ(*it1, *it2);
}

TEST(EraseFunctionTestVector, Test_3) {
  ps::vector<int> vect1{1, 2, 3, 4, 5, 6, 7};
  auto it1 = vect1.erase(vect1.begin() + 10);
  ASSERT_EQ(*(--it1), 7);
}

TEST(PopBackFunctionTestVector, Test_1) {
  ps::vector<int> vect1{1, 2, 3, 4, 5};
  std::vector<int> vect2{1, 2, 3, 4, 5};
  ASSERT_EQ(vect1.size(), vect2.size());
  vect1.pop_back();
  vect2.pop_back();
  ASSERT_EQ(vect1.size(), vect2.size());
  for (size_t i = 0; i < vect1.size(); ++i) {
    ASSERT_EQ(vect1[i], vect2[i]);
  }
}

TEST(PushBackFunctionTestVector, Test_1) {
  ps::vector<int> vect1{1, 2, 3, 4, 5};
  std::vector<int> vect2{1, 2, 3, 4, 5};
  ASSERT_EQ(vect1.size(), vect2.size());
  vect1.push_back(6);
  vect2.push_back(6);
  ASSERT_EQ(vect1.size(), vect2.size());
  for (size_t i = 0; i < vect1.size(); ++i) {
    ASSERT_EQ(vect1[i], vect2[i]);
  }
}

TEST(InsertFunctionTestVector, Test_1) {
  ps::vector<int> vect1{0, 2, 3, 4, 5};
  std::vector<int> vect2{0, 2, 3, 4, 5};
  ASSERT_EQ(vect1.size(), vect2.size());
  vect1.insert(vect1.begin() + 1, 1);
  vect2.insert(vect2.begin() + 1, 1);
  ASSERT_EQ(vect1.size(), vect2.size());
  for (size_t i = 0; i < vect1.size(); ++i) {
    ASSERT_EQ(vect1[i], vect2[i]);
  }
}

TEST(InsertFunctionTestVector, Test_2) {
  ps::vector<int> vect1{1, 2, 3, 4, 5};
  std::vector<int> vect2{1, 2, 3, 4, 5};
  ASSERT_EQ(vect1.size(), vect2.size());
  vect1.insert(vect1.begin(), 0);
  vect2.insert(vect2.begin(), 0);
  ASSERT_EQ(vect1.size(), vect2.size());
  for (size_t i = 0; i < vect1.size(); ++i) {
    ASSERT_EQ(vect1[i], vect2[i]);
  }
}

TEST(InsertFunctionTestVector, Test_3) {
  ps::vector<int> vect{1, 2, 3, 4, 5};
  ASSERT_EQ(vect.size(), 5);
  EXPECT_THROW(vect.insert(vect.begin() + 8, 0), std::out_of_range);
}

TEST(InsertFunctionTestVector, Test_4) {
  ps::vector<int> vect{1, 2, 3, 4, 5};
  vect.reserve(7);
  vect.insert(vect.begin(), 0);
  ASSERT_EQ(vect.size(), 6);
  for (size_t i = 0; i < vect.size(); ++i) {
    ASSERT_EQ(vect[i], i);
  }
}

TEST(InsertManyBackFunctionVector, Test_1) {
  ps::vector<int> ps_vect{1, 2, 3, 4};
  ps_vect.insert_many_back(5, 6, 7);
  auto iter = ps_vect.begin();
  size_t i = 0;
  while (i < ps_vect.size()) {
    ASSERT_EQ(*iter, i + 1);
    ++iter;
    ++i;
  }
}

TEST(InsertManyFunctionVector, Test_1) {
  ps::vector<int> ps_vect{5, 6, 7};
  ps_vect.insert_many(ps_vect.begin(), 4, 3, 2, 1);
  auto iter_1 = ps_vect.begin();
  size_t i = 0;
  while (i < ps_vect.size()) {
    ASSERT_EQ(*iter_1, i + 1);
    ++iter_1;
    ++i;
  }
}