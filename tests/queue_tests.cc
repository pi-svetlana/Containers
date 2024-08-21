#include <gtest/gtest.h>

#include <deque>
#include <queue>

#include "../src/ps_queue.h"

// Constructor tests

TEST(DefaultConstructorQueue, Test_1) {
  auto que1 = ps::queue<int>();
  auto que2 = std::queue<int>();
  ASSERT_EQ(que1.size(), que2.size());
}

TEST(InitializerListConstructorQueue, Test_1) {
  auto que1 = ps::queue<int, ps::deque<int>>{1, 2, 3};
  auto que2 = std::queue<int>{std::deque<int>{1, 2, 3}};
  ASSERT_EQ(que1.size(), que2.size());
  ASSERT_EQ(que1.back(), que2.back());
  ASSERT_EQ(que1.front(), que2.front());
}

TEST(CopyConstructorTestQueue, Test_1) {
  auto que1 = ps::queue<int, ps::deque<int>>{1, 2, 3};
  auto ps_res(que1);
  auto que2 = std::queue<int>{std::deque<int>{1, 2, 3}};
  auto std_res(que2);
  ASSERT_EQ(ps_res.size(), std_res.size());
  ASSERT_EQ(ps_res.back(), std_res.back());
  ASSERT_EQ(ps_res.front(), std_res.front());
}

TEST(MoveConstructorTestQueue, Test_1) {
  auto que1 = ps::queue<int, ps::deque<int>>{1, 2, 3, 4, 5};
  auto ps_res(std::move(que1));
  auto que2 = std::queue<int>{std::deque<int>{1, 2, 3, 4, 5}};
  auto std_res(std::move(que2));
  ASSERT_EQ(ps_res.size(), std_res.size());
  ASSERT_EQ(ps_res.back(), std_res.back());
  ASSERT_EQ(ps_res.front(), std_res.front());
}

// Operator tests

TEST(CopyOperatorTestQueue, Test_1) {
  auto ps_que = ps::queue<int, ps::deque<int>>{1, 2, 3};
  auto ps_res = ps::queue<int, ps::deque<int>>{4, 5};
  ps_res = ps_que;
  auto std_que = std::queue<int>{std::deque<int>{1, 2, 3}};
  auto std_res = std::queue<int>{std::deque<int>{4, 5}};
  std_res = std_que;
  ASSERT_EQ(ps_res.size(), std_res.size());
  ASSERT_EQ(ps_res.back(), std_res.back());
  ASSERT_EQ(ps_res.front(), std_res.front());
  ASSERT_EQ(ps_que.size(), std_que.size());
  ASSERT_EQ(ps_que.back(), std_que.back());
  ASSERT_EQ(ps_que.front(), std_que.front());
}

TEST(MoveOperatorTestQuque, Test_1) {
  auto ps_que = ps::queue<int, ps::deque<int>>{1, 2, 3};
  auto ps_res = ps::queue<int, ps::deque<int>>{4, 5};
  ps_res = std::move(ps_que);
  auto std_que = std::queue<int>{std::deque<int>{1, 2, 3}};
  auto std_res = std::queue<int>{std::deque<int>{4, 5}};
  std_res = std::move(std_que);
  ASSERT_EQ(ps_res.size(), std_res.size());
  ASSERT_EQ(ps_res.back(), std_res.back());
  ASSERT_EQ(ps_res.front(), std_res.front());
  ASSERT_EQ(ps_que.size(), std_que.size());
}

// Function tests

TEST(BackFrontConstFunctionTestQueue, Test_1) {
  const auto que1 = ps::queue<int, ps::deque<int>>{1, 2, 3};
  const auto que2 = std::queue<int>{std::deque<int>{1, 2, 3}};
  ASSERT_EQ(que1.size(), que2.size());
  ASSERT_EQ(que1.back(), que2.back());
  ASSERT_EQ(que1.front(), que2.front());
}

TEST(EmptyFunctionTestQueue, Test_1) {
  auto que1 = ps::queue<int, ps::deque<int>>{1, 2, 3};
  auto que2 = std::queue<int>{std::deque<int>{1, 2, 3}};
  ASSERT_EQ(que1.empty(), que2.empty());
}

TEST(EmptyFunctionTestQueue, Test_2) {
  auto que1 = ps::queue<int>();
  auto que2 = std::queue<int>();
  ASSERT_EQ(que1.empty(), que2.empty());
}

TEST(PushFunctionTestQueue, Test_1) {
  auto que1 = ps::queue<int, ps::deque<int>>{1, 2, 3};
  que1.push(7);
  auto que2 = std::queue<int>{std::deque<int>{1, 2, 3}};
  que2.push(7);
  ASSERT_EQ(que1.size(), que2.size());
  ASSERT_EQ(que1.back(), que2.back());
  ASSERT_EQ(que1.front(), que2.front());
}

TEST(PopFunctionTestQueue, Test_1) {
  auto que1 = ps::queue<int, ps::deque<int>>{1, 2, 3};
  que1.pop();
  auto que2 = std::queue<int>{std::deque<int>{1, 2, 3}};
  que2.pop();
  ASSERT_EQ(que1.size(), que2.size());
  ASSERT_EQ(que1.back(), que2.back());
  ASSERT_EQ(que1.front(), que2.front());
}

TEST(SwapFunctionTestQueue, Test_1) {
  auto que1 = ps::queue<int>{1, 2, 3, 4, 5};
  auto que2 = ps::queue<int>{2, 1, 0};
  que1.swap(que2);
  auto que3 = std::queue<int>{std::deque<int>{1, 2, 3, 4, 5}};
  auto que4 = std::queue<int>{std::deque<int>{2, 1, 0}};
  que3.swap(que4);

  ASSERT_EQ(que2.size(), que4.size());
  ASSERT_EQ(que2.back(), que4.back());
  ASSERT_EQ(que2.front(), que4.front());
  ASSERT_EQ(que1.size(), que3.size());
  ASSERT_EQ(que1.back(), que3.back());
  ASSERT_EQ(que1.front(), que3.front());
}

TEST(InsertManyBackQueue, Test_1) {
  ps::queue<int> ps_que;
  ps_que.insert_many_back(1, 2, 3);
  ASSERT_EQ(ps_que.front(), 1);
  ASSERT_EQ(ps_que.back(), 3);
}