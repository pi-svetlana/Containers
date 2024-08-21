#include <gtest/gtest.h>

#include <deque>

#include "../src/ps_deque.h"

// Constructor tests

TEST(DefaultConstructorDeque, Test_1) {
  auto deq1 = ps::deque<int>();
  auto deq2 = std::deque<int>();
  ASSERT_EQ(deq1.size(), deq2.size());
}

TEST(InitializerListConstructorDeque, Test_1) {
  auto deq1 = ps::deque<int>{1, 2, 3};
  auto deq2 = std::deque<int>{1, 2, 3};
  ASSERT_EQ(deq1.size(), deq2.size());
  ASSERT_EQ(deq1.back(), deq2.back());
  ASSERT_EQ(deq1.front(), deq2.front());
}

TEST(CopyConstructorTestDeque, Test_1) {
  ps::deque<int> deq1{1, 2, 3};
  auto ps_res(deq1);
  std::deque<int> deq2{1, 2, 3};
  auto std_res(deq2);
  ASSERT_EQ(ps_res.size(), std_res.size());
  ASSERT_EQ(ps_res.back(), std_res.back());
  ASSERT_EQ(ps_res.front(), std_res.front());
}

TEST(MoveConstructorTestDeque, Test_1) {
  ps::deque<int> deq1{1, 2, 3, 4, 5};
  auto ps_res(std::move(deq1));
  std::deque<int> deq2{1, 2, 3, 4, 5};
  auto std_res(std::move(deq2));
  ASSERT_EQ(ps_res.size(), std_res.size());
  ASSERT_EQ(ps_res.back(), std_res.back());
  ASSERT_EQ(ps_res.front(), std_res.front());
}

// Operator tests

TEST(CopyOperatorTestDeque, Test_1) {
  ps::deque<int> ps_deq{1, 2, 3};
  ps::deque<int> ps_res{4, 5};
  ps_res = ps_deq;
  std::deque<int> std_deq{1, 2, 3};
  std::deque<int> std_res{4, 5};
  std_res = std_deq;
  ASSERT_EQ(ps_res.size(), std_res.size());
  ASSERT_EQ(ps_res.back(), std_res.back());
  ASSERT_EQ(ps_res.front(), std_res.front());
  ASSERT_EQ(ps_deq.size(), std_deq.size());
  ASSERT_EQ(ps_deq.back(), std_deq.back());
  ASSERT_EQ(ps_deq.front(), std_deq.front());
}

TEST(MoveOperatorTestDeque, Test_1) {
  ps::deque<int> ps_deq{1, 2, 3};
  ps::deque<int> ps_res{4, 5};
  ps_res = std::move(ps_deq);
  std::deque<int> std_deq{1, 2, 3};
  std::deque<int> std_res{4, 5};
  std_res = std::move(std_deq);
  ASSERT_EQ(ps_res.size(), std_res.size());
  ASSERT_EQ(ps_res.back(), std_res.back());
  ASSERT_EQ(ps_res.front(), std_res.front());
  ASSERT_EQ(ps_deq.size(), std_deq.size());
}

// Function tests

TEST(BackFrontConstFunctionTestDeque, Test_1) {
  const ps::deque<int> deq1{1, 2, 3};
  const std::deque<int> deq2{1, 2, 3};
  ASSERT_EQ(deq1.size(), deq2.size());
  ASSERT_EQ(deq1.back(), deq2.back());
  ASSERT_EQ(deq1.front(), deq2.front());
}

TEST(EmptyFunctionTestDeque, Test_1) {
  ps::deque<int> deq1{1, 2, 3};
  std::deque<int> deq2{1, 2, 3};
  ASSERT_EQ(deq1.empty(), deq2.empty());
}

TEST(EmptyFunctionTestDeque, Test_2) {
  auto deq1 = ps::deque<int>();
  auto deq2 = std::deque<int>();
  ASSERT_EQ(deq1.empty(), deq2.empty());
}

TEST(PushBackFunctionTestDeque, Test_1) {
  ps::deque<int> deq1{1, 2, 3};
  deq1.push_back(7);
  std::deque<int> deq2{1, 2, 3};
  deq2.push_back(7);
  ASSERT_EQ(deq1.size(), deq2.size());
  ASSERT_EQ(deq1.back(), deq2.back());
  ASSERT_EQ(deq1.front(), deq2.front());
}

TEST(PushFrontFunctionTestDeque, Test_1) {
  ps::deque<int> deq1{1, 2, 3};
  deq1.push_front(7);
  std::deque<int> deq2{1, 2, 3};
  deq2.push_front(7);
  ASSERT_EQ(deq1.size(), deq2.size());
  ASSERT_EQ(deq1.back(), deq2.back());
  ASSERT_EQ(deq1.front(), deq2.front());
}

TEST(PopBackFunctionTestDeque, Test_1) {
  ps::deque<int> deq1{1, 2, 3};
  deq1.pop_back();
  std::deque<int> deq2{1, 2, 3};
  deq2.pop_back();
  ASSERT_EQ(deq1.size(), deq2.size());
  ASSERT_EQ(deq1.back(), deq2.back());
  ASSERT_EQ(deq1.front(), deq2.front());
}

TEST(PopBackFunctionTestDeque, Test_2) {
  ps::deque<int> deq1{1};
  deq1.pop_back();
  std::deque<int> deq2{1};
  deq2.pop_back();
  ASSERT_EQ(deq1.size(), deq2.size());
}

TEST(PopFrontFunctionTestDeque, Test_1) {
  ps::deque<int> deq1{1, 2, 3};
  deq1.pop_front();
  std::deque<int> deq2{1, 2, 3};
  deq2.pop_front();
  ASSERT_EQ(deq1.size(), deq2.size());
  ASSERT_EQ(deq1.back(), deq2.back());
  ASSERT_EQ(deq1.front(), deq2.front());
}

TEST(ClearFunctionTestDeque, Test_1) {
  ps::deque<int> deq1{1, 2, 3};
  deq1.clear();
  std::deque<int> deq2{1, 2, 3};
  deq2.clear();
  ASSERT_EQ(deq1.size(), deq2.size());
}

TEST(SwapFunctionTestDeque, Test_1) {
  ps::deque<int> deq1{1, 2, 3, 4, 5};
  ps::deque<int> deq2{2, 1, 0};
  deq1.swap(deq2);
  std::deque<int> deq3{1, 2, 3, 4, 5};
  std::deque<int> deq4{2, 1, 0};
  deq3.swap(deq4);

  ASSERT_EQ(deq2.size(), deq4.size());
  ASSERT_EQ(deq2.back(), deq4.back());
  ASSERT_EQ(deq2.front(), deq4.front());
  ASSERT_EQ(deq1.size(), deq3.size());
  ASSERT_EQ(deq1.back(), deq3.back());
  ASSERT_EQ(deq1.front(), deq3.front());
}