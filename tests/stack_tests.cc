#include <gtest/gtest.h>

#include <deque>
#include <stack>

#include "../src/ps_stack.h"

// Constructor tests

TEST(DefaultConstructorStack, Test_1) {
  auto st1 = ps::stack<int>();
  auto st2 = std::stack<int>();
  ASSERT_EQ(st1.size(), st2.size());
}

TEST(InitializerListConstructorStack, Test_1) {
  auto st1 = ps::stack<int, ps::deque<int>>{1, 2, 3};
  auto st2 = std::stack<int>{std::deque<int>{1, 2, 3}};
  ASSERT_EQ(st1.size(), st2.size());
  ASSERT_EQ(st1.top(), st2.top());
}

TEST(CopyConstructorTestStack, Test_1) {
  auto st1 = ps::stack<int, ps::deque<int>>{1, 2, 3};
  auto ps_res(st1);
  auto st2 = std::stack<int>{std::deque<int>{1, 2, 3}};
  auto std_res(st2);
  ASSERT_EQ(ps_res.size(), std_res.size());
  ASSERT_EQ(ps_res.top(), std_res.top());
}

TEST(MoveConstructorTestStack, Test_1) {
  auto st1 = ps::stack<int, ps::deque<int>>{1, 2, 3, 4, 5};
  auto ps_res(std::move(st1));
  auto st2 = std::stack<int>{std::deque<int>{1, 2, 3, 4, 5}};
  auto std_res(std::move(st2));
  ASSERT_EQ(ps_res.size(), std_res.size());
  ASSERT_EQ(ps_res.top(), std_res.top());
}

// Operator tests

TEST(CopyOperatorTestStack, Test_1) {
  auto ps_st = ps::stack<int, ps::deque<int>>{1, 2, 3};
  auto ps_res = ps::stack<int, ps::deque<int>>{4, 5};
  ps_res = ps_st;
  auto std_st = std::stack<int>{std::deque<int>{1, 2, 3}};
  auto std_res = std::stack<int>{std::deque<int>{4, 5}};
  std_res = std_st;
  ASSERT_EQ(ps_res.size(), std_res.size());
  ASSERT_EQ(ps_res.top(), std_res.top());
  ASSERT_EQ(ps_st.size(), std_st.size());
}

TEST(MoveOperatorTestStack, Test_1) {
  auto ps_st = ps::stack<int, ps::deque<int>>{1, 2, 3};
  auto ps_res = ps::stack<int, ps::deque<int>>{4, 5};
  ps_res = std::move(ps_st);
  auto std_st = std::stack<int>{std::deque<int>{1, 2, 3}};
  auto std_res = std::stack<int>{std::deque<int>{4, 5}};
  std_res = std::move(std_st);
  ASSERT_EQ(ps_res.size(), std_res.size());
  ASSERT_EQ(ps_res.top(), std_res.top());
  ASSERT_EQ(ps_st.size(), std_st.size());
}

// Function tests

TEST(TopConstFunctionTestStack, Test_1) {
  const auto st1 = ps::stack<int, ps::deque<int>>{1, 2, 3};
  const auto st2 = std::stack<int>{std::deque<int>{1, 2, 3}};
  ASSERT_EQ(st1.size(), st2.size());
  ASSERT_EQ(st1.top(), st2.top());
}

TEST(EmptyFunctionTestStack, Test_1) {
  auto st1 = ps::stack<int, ps::deque<int>>{1, 2, 3};
  auto st2 = std::stack<int>{std::deque<int>{1, 2, 3}};
  ASSERT_EQ(st1.empty(), st2.empty());
}

TEST(EmptyFunctionTestStack, Test_2) {
  auto st1 = ps::stack<int>();
  auto st2 = std::stack<int>();
  ASSERT_EQ(st1.empty(), st2.empty());
}

TEST(PushFunctionTestStack, Test_1) {
  auto st1 = ps::stack<int, ps::deque<int>>{1, 2, 3};
  st1.push(7);
  auto st2 = std::stack<int>{std::deque<int>{1, 2, 3}};
  st2.push(7);
  ASSERT_EQ(st1.size(), st2.size());
  ASSERT_EQ(st1.top(), st2.top());
}

TEST(PopFunctionTestStack, Test_1) {
  auto st1 = ps::stack<int, ps::deque<int>>{1, 2, 3};
  st1.pop();
  auto st2 = std::stack<int>{std::deque<int>{1, 2, 3}};
  st2.pop();
  ASSERT_EQ(st1.size(), st2.size());
  ASSERT_EQ(st1.top(), st2.top());
}

TEST(SwapFunctionTestStack, Test_1) {
  auto st1 = ps::stack<int>{1, 2, 3, 4, 5};
  auto st2 = ps::stack<int>{2, 1, 0};
  st1.swap(st2);
  auto st3 = std::stack<int>{std::deque<int>{1, 2, 3, 4, 5}};
  auto st4 = std::stack<int>{std::deque<int>{2, 1, 0}};
  st3.swap(st4);

  ASSERT_EQ(st2.size(), st4.size());
  ASSERT_EQ(st2.top(), st4.top());
  ASSERT_EQ(st1.size(), st3.size());
  ASSERT_EQ(st1.top(), st3.top());
}

TEST(InsertManyFrontStack, Test_1) {
  ps::stack<int> ps_st;
  ps_st.insert_many_front(1, 2, 3);
  ASSERT_EQ(ps_st.top(), 1);
}

TEST(InsertManyFrontStack, Test_2) {
  auto st = ps::stack<int, ps::deque<int>>{1, 2, 5};
  st.insert_many_front(1, 2, 3);
  ASSERT_EQ(st.top(), 5);
}
