#include <gtest/gtest.h>

#include <list>

#include "../src/ps_list.h"

// Constructor tests

TEST(DefaultConstructorList, Test_1) {
  ps::list<int> ps_lst;
  std::list<int> std_lst;
  ASSERT_EQ(ps_lst.empty(), std_lst.empty());
  ASSERT_EQ(ps_lst.size(), std_lst.size());
}

TEST(ParameterizedConstructorList, Test_1) {
  auto ps_lst = ps::list<int>(3);
  auto std_lst = std::list<int>(3);
  ASSERT_EQ(ps_lst.size(), std_lst.size());
}

TEST(InitializerListConstructorList, Test_1) {
  ps::list<int> ps_lst = {1, 2, 3};
  std::list<int> std_lst = {1, 2, 3};
  ASSERT_EQ(ps_lst.front(), std_lst.front());
  ASSERT_EQ(ps_lst.back(), std_lst.back());
}

TEST(CopyConstructorList, Test_1) {
  ps::list<int> ps_lst = {1, 2, 3};
  std::list<int> std_lst = {1, 2, 3};
  ps::list<int> ps_copy(ps_lst);
  std::list<int> std_copy(std_lst);
  ASSERT_EQ(ps_copy.front(), std_copy.front());
  ASSERT_EQ(ps_copy.back(), std_copy.back());
}

TEST(MoveConstructorList, Test_1) {
  ps::list<int> ps_lst = {1, 2, 3, 4, 5};
  std::list<int> std_lst = {1, 2, 3, 4, 5};
  auto ps_move(std::move(ps_lst));
  auto std_move(std::move(std_lst));
  ASSERT_EQ(ps_move.front(), std_move.front());
  ASSERT_EQ(ps_move.back(), std_move.back());
}

// Operator tests

TEST(CopyOperatorTestList, Test_1) {
  const ps::list<int> lst1{0, 1, 2, 3, 4};
  ps::list<int> ps_res{1, 2, 3};
  ps_res = lst1;
  const std::list<int> lst2{0, 1, 2, 3, 4};
  std::list<int> std_res{1, 2, 3};
  std_res = lst2;
  ASSERT_EQ(ps_res.front(), std_res.front());
  ASSERT_EQ(ps_res.back(), std_res.back());
  ASSERT_EQ(ps_res.size(), std_res.size());
}

TEST(MoveOperatorTestList, Test_1) {
  ps::list<int> lst1{1, 2, 3};
  ps::list<int> lst2;
  lst2 = std::move(lst1);
  EXPECT_EQ(lst2.size(), 3);
  EXPECT_TRUE(lst1.empty());
}

TEST(MoveOperatorTestList, Test_2) {
  ps::list<int> lst1{0, 1, 2, 3, 4};
  ps::list<int> ps_res{1, 2, 3};
  ps_res = std::move(lst1);
  ASSERT_EQ(ps_res.front(), 0);
  ASSERT_EQ(ps_res.back(), 4);
  ASSERT_EQ(ps_res.size(), 5);
  EXPECT_TRUE(lst1.empty());
}

// Function tests

TEST(FrontBackFunctionList, Test_1) {
  ps::list<int> ps_lst = {1, 2, 3, 7, 9};
  std::list<int> std_lst = {1, 2, 3, 7, 9};
  auto iter_1 = ps_lst.cend();
  auto iter_2 = std_lst.end();
  auto iter_3 = ps_lst.end();
  iter_1--;
  iter_2--;
  iter_3--;
  EXPECT_TRUE(iter_3 == iter_1);
  ASSERT_EQ(*iter_1, *iter_3);
  ASSERT_EQ(*iter_1, *iter_2);
  ASSERT_EQ(ps_lst.front(), std_lst.front());
  ASSERT_EQ(ps_lst.back(), std_lst.back());
}

TEST(FrontBackConstFunctionList, Test_1) {
  const ps::list<int> ps_lst = {1, 2, 3, 7, 9};
  const std::list<int> std_lst = {1, 2, 3, 7, 9};
  ASSERT_EQ(ps_lst.front(), std_lst.front());
  ASSERT_EQ(ps_lst.back(), std_lst.back());
}

TEST(BeginFunctionList, Test_1) {
  ps::list<int> ps_lst = {1, 2, 3, 7, 9};
  std::list<int> std_lst = {1, 2, 3, 7, 9};
  ASSERT_EQ(*(ps_lst.begin()), *(std_lst.begin()));
  ASSERT_EQ(*(ps_lst.begin()++), *(std_lst.begin()++));
  auto iter_1 = ps_lst.cbegin();
  auto iter_2 = std_lst.cbegin();
  iter_1++;
  iter_2++;
  ASSERT_EQ(*iter_1, *iter_2);
  iter_1--;
  iter_2--;
  ASSERT_EQ(*iter_1, *iter_2);
}

TEST(BeginConstFunctionList, Test_1) {
  const ps::list<int> ps_lst = {1, 2, 3, 7, 9};
  const std::list<int> std_lst = {1, 2, 3, 7, 9};
  ASSERT_EQ(*(ps_lst.begin()), *(std_lst.begin()));
  EXPECT_TRUE(ps_lst.begin() != ps_lst.end());
  EXPECT_FALSE(ps_lst.begin() == ps_lst.end());
}

TEST(CBeginFunctionList, Test_1) {
  const ps::list<int> ps_lst = {1, 2, 3, 7, 9};
  const std::list<int> std_lst = {1, 2, 3, 7, 9};
  ASSERT_EQ(*(ps_lst.cbegin()), *(std_lst.cbegin()));
}

TEST(EndFunctionList, Test_1) {
  ps::list<int> ps_lst = {1, 2, 3, 7, 9};
  std::list<int> std_lst = {1, 2, 3, 7, 9};
  ASSERT_EQ(*(--ps_lst.end()), *(--std_lst.end()));
}

TEST(EndConstFunctionList, Test_1) {
  const ps::list<int> ps_lst = {1, 2, 3, 7, 9};
  const std::list<int> std_lst = {1, 2, 3, 7, 9};
  ASSERT_EQ(*(--ps_lst.end()), *(--std_lst.end()));
}

TEST(CEndFunctionList, Test_1) {
  const ps::list<int> ps_lst = {1, 2, 3, 7, 9};
  const std::list<int> std_lst = {1, 2, 3, 7, 9};
  ASSERT_EQ(*(--ps_lst.cend()), *(--std_lst.cend()));
}

TEST(EmptyFunctionList, Test_1) {
  ps::list<int> ps_lst = {1, 2, 3, 7, 9};
  std::list<int> std_lst = {1, 2, 3, 7, 9};
  ASSERT_EQ(ps_lst.empty(), std_lst.empty());
}

TEST(EmptyFunctionList, Test_2) {
  ps::list<int> ps_lst = {};
  std::list<int> std_lst = {};
  ASSERT_EQ(ps_lst.empty(), std_lst.empty());
}

TEST(SizeFunctionList, Test_1) {
  ps::list<int> ps_lst = {1, 2, 3, 7, 9};
  std::list<int> std_lst = {1, 2, 3, 7, 9};
  ASSERT_EQ(ps_lst.size(), std_lst.size());
}

TEST(MaxSizeFunctionList, Test_1) {
  ps::list<double> ps_lst = {1, 2.78943, 3, 7, 9};
  std::list<double> std_lst = {1, 278943, 3, 7, 9};
  ASSERT_EQ(ps_lst.max_size(), std_lst.max_size());
}

TEST(ClearFunctionList, Test_1) {
  ps::list<int> ps_lst = {1, 2, 3, 7, 9};
  std::list<int> std_lst = {1, 2, 3, 7, 9};
  ps_lst.clear();
  std_lst.clear();
  ASSERT_EQ(ps_lst.empty(), std_lst.empty());
}

TEST(InsertFunctionList, Test_1) {
  ps::list<int> ps_lst = {1, 2, 3, 7, 9};
  std::list<int> std_lst = {1, 2, 3, 7, 9};
  ps_lst.insert(++ps_lst.cbegin(), 5);
  ps_lst.insert(ps_lst.cbegin(), 8);
  ps_lst.insert(ps_lst.cend(), 10);
  std_lst.insert(++std_lst.cbegin(), 5);
  std_lst.insert(std_lst.cbegin(), 8);
  std_lst.insert(std_lst.cend(), 10);
  ASSERT_EQ(ps_lst.front(), std_lst.front());
  ASSERT_EQ(ps_lst.back(), std_lst.back());
  ASSERT_EQ(ps_lst.size(), std_lst.size());
  size_t i = ps_lst.size();
  auto iter_1 = ps_lst.cbegin();
  auto iter_2 = std_lst.cbegin();
  while (i != 0) {
    ASSERT_EQ(*iter_1, *iter_2);
    ++iter_1;
    ++iter_2;
    --i;
  }
  auto iter_3 = ps_lst.cbegin();
  auto iter_4 = std_lst.cbegin();
  iter_3++;
  iter_4++;
  ASSERT_EQ(*iter_3, *iter_4);
  iter_3--;
  iter_4--;
  ASSERT_EQ(*iter_3, *iter_4);
}

TEST(EraseFunctionList, Test_1) {
  ps::list<int> ps_lst = {1, 2, 3, 4, 5};
  std::list<int> std_lst = {1, 2, 3, 4, 5};
  ps_lst.erase(ps_lst.cbegin());
  std_lst.erase(std_lst.cbegin());
  ASSERT_EQ(ps_lst.front(), std_lst.front());
  ASSERT_EQ(ps_lst.back(), std_lst.back());
  ASSERT_EQ(ps_lst.size(), std_lst.size());
}

TEST(EraseFunctionList, Test_2) {
  ps::list<int> ps_lst{1, 2, 3, 7, 9};
  std::list<int> std_lst{1, 2, 3, 7, 9};
  ps::list<int>::const_iterator ps_it = ps_lst.cend();
  --ps_it;
  std::list<int>::const_iterator std_it = std_lst.cend();
  --std_it;
  ps_lst.erase(ps_it);
  std_lst.erase(std_it);
  ASSERT_EQ(ps_lst.front(), std_lst.front());
  ASSERT_EQ(ps_lst.back(), std_lst.back());
  ASSERT_EQ(ps_lst.size(), std_lst.size());
}

TEST(EraseFunctionList, Test_3) {
  ps::list<int> ps_lst{1, 2, 3, 7, 9};
  std::list<int> std_lst{1, 2, 3, 7, 9};
  ps::list<int>::const_iterator ps_it = ps_lst.cbegin();
  ++ps_it;
  std::list<int>::const_iterator std_it = std_lst.cbegin();
  ++std_it;
  ps_lst.erase(ps_it);
  std_lst.erase(std_it);
  ASSERT_EQ(ps_lst.front(), std_lst.front());
  ASSERT_EQ(ps_lst.back(), std_lst.back());
  ASSERT_EQ(ps_lst.size(), std_lst.size());
  size_t i = ps_lst.size();
  auto iter_1 = ps_lst.cbegin();
  auto iter_2 = std_lst.cbegin();
  while (i != 0) {
    ASSERT_EQ(*iter_1, *iter_2);
    ++iter_1;
    ++iter_2;
    --i;
  }
}

TEST(PushBackFunctionList, Test_1) {
  ps::list<int> ps_lst = {1, 2, 3, 4, 5};
  std::list<int> std_lst = {1, 2, 3, 4, 5};
  ps_lst.push_back(8);
  std_lst.push_back(8);
  ASSERT_EQ(ps_lst.front(), std_lst.front());
  ASSERT_EQ(ps_lst.back(), std_lst.back());
  ASSERT_EQ(ps_lst.size(), std_lst.size());
}

TEST(PushBackFunctionList, Test_2) {
  ps::list<int> ps_lst;
  std::list<int> std_lst;
  ps_lst.push_back(5);
  std_lst.push_back(5);
  ASSERT_EQ(ps_lst.front(), std_lst.front());
  ASSERT_EQ(ps_lst.back(), std_lst.back());
  ASSERT_EQ(ps_lst.size(), std_lst.size());
}

TEST(PopBackFunctionList, Test_1) {
  ps::list<int> ps_lst = {1, 2, 3, 4, 5};
  std::list<int> std_lst = {1, 2, 3, 4, 5};
  ps_lst.pop_back();
  std_lst.pop_back();
  ASSERT_EQ(ps_lst.front(), std_lst.front());
  ASSERT_EQ(ps_lst.back(), std_lst.back());
  ASSERT_EQ(ps_lst.size(), std_lst.size());
}

TEST(PushFrontFunctionList, Test_1) {
  ps::list<int> ps_lst = {1, 2, 3, 4, 5};
  std::list<int> std_lst = {1, 2, 3, 4, 5};
  ps_lst.push_front(8);
  std_lst.push_front(8);
  ASSERT_EQ(ps_lst.front(), std_lst.front());
  ASSERT_EQ(ps_lst.back(), std_lst.back());
  ASSERT_EQ(ps_lst.size(), std_lst.size());
}

TEST(PushFrontFunctionList, Test_2) {
  ps::list<int> ps_lst;
  std::list<int> std_lst;
  ps_lst.push_front(5);
  std_lst.push_front(5);
  ASSERT_EQ(ps_lst.front(), std_lst.front());
  ASSERT_EQ(ps_lst.back(), std_lst.back());
  ASSERT_EQ(ps_lst.size(), std_lst.size());
}

TEST(PopFrontFunctionList, Test_1) {
  ps::list<int> ps_lst = {1, 2, 3, 4, 5};
  std::list<int> std_lst = {1, 2, 3, 4, 5};
  ps_lst.pop_back();
  std_lst.pop_back();
  ASSERT_EQ(ps_lst.front(), std_lst.front());
  ASSERT_EQ(ps_lst.back(), std_lst.back());
  ASSERT_EQ(ps_lst.size(), std_lst.size());
}

TEST(ReverseFunctionList, Test_1) {
  ps::list<int> ps_lst = {1, 2, 3, 4, 5};
  std::list<int> std_lst = {1, 2, 3, 4, 5};
  ps_lst.reverse();
  std_lst.reverse();
  ASSERT_EQ(ps_lst.front(), std_lst.front());
  ASSERT_EQ(ps_lst.back(), std_lst.back());
  ASSERT_EQ(ps_lst.size(), std_lst.size());
  ASSERT_EQ(*(--ps_lst.cend()), *(--std_lst.cend()));
  size_t i = ps_lst.size();
  auto iter_1 = ps_lst.cbegin();
  auto iter_2 = std_lst.cbegin();
  while (i != 0) {
    ASSERT_EQ(*iter_1, *iter_2);
    ++iter_1;
    ++iter_2;
    --i;
  }
}

TEST(ReverseFunctionList, Test_2) {
  ps::list<int> ps_lst = {1, 2, 3, 4, 5, 6};
  std::list<int> std_lst = {1, 2, 3, 4, 5, 6};
  ps_lst.reverse();
  std_lst.reverse();
  ASSERT_EQ(ps_lst.front(), std_lst.front());
  ASSERT_EQ(ps_lst.back(), std_lst.back());
  ASSERT_EQ(ps_lst.size(), std_lst.size());
  ASSERT_EQ(*(--ps_lst.cend()), *(--std_lst.cend()));
  size_t i = ps_lst.size();
  auto iter_1 = ps_lst.cbegin();
  auto iter_2 = std_lst.cbegin();
  while (i != 0) {
    ASSERT_EQ(*iter_1, *iter_2);
    ++iter_1;
    ++iter_2;
    --i;
  }
}

TEST(ReverseFunctionList, Test_3) {
  ps::list<int> ps_lst = {1};
  std::list<int> std_lst = {1};
  ps_lst.reverse();
  std_lst.reverse();
  ASSERT_EQ(ps_lst.front(), std_lst.front());
  ASSERT_EQ(ps_lst.back(), std_lst.back());
  ASSERT_EQ(ps_lst.size(), std_lst.size());
  ASSERT_EQ(*(--ps_lst.cend()), *(--std_lst.cend()));
  size_t i = ps_lst.size();
  auto iter_1 = ps_lst.cbegin();
  auto iter_2 = std_lst.cbegin();
  while (i != 0) {
    ASSERT_EQ(*iter_1, *iter_2);
    ++iter_1;
    ++iter_2;
    --i;
  }
}

TEST(ReverseFunctionList, Test_4) {
  ps::list<int> ps_lst;
  std::list<int> std_lst;
  ps_lst.reverse();
  std_lst.reverse();
  ASSERT_EQ(ps_lst.size(), std_lst.size());
}

TEST(SwapFunctionList, Test_1) {
  ps::list<int> ps_lst = {1, 2, 3, 4, 5};
  std::list<int> std_lst = {1, 2, 3, 4, 5};
  ps::list<int> ps_lst2 = {1, 2, 3};
  std::list<int> std_lst2 = {1, 2, 3};
  ps_lst.swap(ps_lst2);
  std_lst.swap(std_lst2);
  ASSERT_EQ(ps_lst.front(), std_lst.front());
  ASSERT_EQ(ps_lst.back(), std_lst.back());
  ASSERT_EQ(ps_lst.size(), std_lst.size());
}

TEST(SwapFunctionList, Test_2) {
  ps::list<int> ps_lst = {1, 2, 2, 3, 4, 4, 4, 5};
  std::list<int> std_lst = {1, 2, 2, 3, 4, 4, 4, 5};
  ps::list<int> ps_lst_other = {1, 2, 2};
  std::list<int> std_lst_other = {1, 2, 2};
  ps_lst.swap(ps_lst_other);
  std_lst.swap(std_lst_other);
  ASSERT_EQ(ps_lst.front(), std_lst.front());
  ASSERT_EQ(ps_lst.back(), std_lst.back());
  ASSERT_EQ(ps_lst.size(), std_lst.size());
  size_t i = ps_lst.size();
  auto iter_1 = ps_lst.cbegin();
  auto iter_2 = std_lst.cbegin();
  while (i != 0) {
    ASSERT_EQ(*iter_1, *iter_2);
    ++iter_1;
    ++iter_2;
    --i;
  }
}

TEST(UniqueFunctionList, Test_1) {
  ps::list<int> ps_lst = {1, 2, 2, 3, 4, 4, 4, 5};
  std::list<int> std_lst = {1, 2, 2, 3, 4, 4, 4, 5};
  ps_lst.unique();
  std_lst.unique();
  ASSERT_EQ(ps_lst.front(), std_lst.front());
  ASSERT_EQ(ps_lst.back(), std_lst.back());
  ASSERT_EQ(ps_lst.size(), std_lst.size());
}

TEST(SpliceFunctionList, Test_1) {
  ps::list<int> ps_lst = {1, 2, 3, 4, 5};
  ps::list<int> ps_lst_other = {6, 7, 8};
  std::list<int> std_lst = {1, 2, 3, 4, 5};
  std::list<int> std_lst_other = {6, 7, 8};
  ps_lst.splice(ps_lst.cbegin(), ps_lst_other);
  std_lst.splice(std_lst.cbegin(), std_lst_other);
  ASSERT_EQ(ps_lst.front(), std_lst.front());
  ASSERT_EQ(ps_lst.back(), std_lst.back());
  ASSERT_EQ(ps_lst.size(), std_lst.size());
}

TEST(SpliceFunctionList, Test_2) {
  ps::list<int> ps_lst = {1, 2, 3, 4, 5};
  ps::list<int> ps_lst_other = {6, 7, 8};
  std::list<int> std_lst = {1, 2, 3, 4, 5};
  std::list<int> std_lst_other = {6, 7, 8};
  ps_lst.splice(--ps_lst.cend(), ps_lst_other);
  std_lst.splice(--std_lst.cend(), std_lst_other);
  ASSERT_EQ(ps_lst.front(), std_lst.front());
  ASSERT_EQ(ps_lst.back(), std_lst.back());
  ASSERT_EQ(ps_lst.size(), std_lst.size());
  size_t i = ps_lst.size();
  auto iter_1 = ps_lst.cbegin();
  auto iter_2 = std_lst.cbegin();
  while (i != 0) {
    ASSERT_EQ(*iter_1, *iter_2);
    ++iter_1;
    ++iter_2;
    --i;
  }
}

TEST(SpliceFunctionList, Test_3) {
  ps::list<int> ps_lst = {1, 2, 3, 4, 5};
  ps::list<int> ps_lst_other = {6, 7, 8};
  std::list<int> std_lst = {1, 2, 3, 4, 5};
  std::list<int> std_lst_other = {6, 7, 8};
  ps_lst.splice(ps_lst.cend(), ps_lst_other);
  std_lst.splice(std_lst.cend(), std_lst_other);
  ASSERT_EQ(ps_lst.front(), std_lst.front());
  ASSERT_EQ(ps_lst.back(), std_lst.back());
  ASSERT_EQ(ps_lst.size(), std_lst.size());
  size_t i = ps_lst.size();
  auto iter_1 = ps_lst.cbegin();
  auto iter_2 = std_lst.cbegin();
  while (i != 0) {
    ASSERT_EQ(*iter_1, *iter_2);
    ++iter_1;
    ++iter_2;
    --i;
  }
}

TEST(SortFunctionList, Test_1) {
  ps::list<int> ps_lst = {4, 5, 2, 6, 4, 8, 1, 4};
  std::list<int> std_lst = {4, 5, 2, 6, 4, 8, 1, 4};
  ps_lst.sort();
  std_lst.sort();
  ASSERT_EQ(ps_lst.front(), std_lst.front());
  ASSERT_EQ(ps_lst.back(), std_lst.back());
  ASSERT_EQ(ps_lst.size(), std_lst.size());
  size_t i = ps_lst.size();
  auto iter_1 = ps_lst.cbegin();
  auto iter_2 = std_lst.cbegin();
  while (i != 0) {
    ASSERT_EQ(*iter_1, *iter_2);
    ++iter_1;
    ++iter_2;
    --i;
  }
}

TEST(SortFunctionList, Test_2) {
  ps::list<int> ps_lst = {4};
  std::list<int> std_lst = {4};
  ps_lst.sort();
  std_lst.sort();
  ASSERT_EQ(ps_lst.front(), std_lst.front());
  ASSERT_EQ(ps_lst.back(), std_lst.back());
  ASSERT_EQ(ps_lst.size(), std_lst.size());
  size_t i = ps_lst.size();
  auto iter_1 = ps_lst.cbegin();
  auto iter_2 = std_lst.cbegin();
  while (i != 0) {
    ASSERT_EQ(*iter_1, *iter_2);
    ++iter_1;
    ++iter_2;
    --i;
  }
}

TEST(MergeFunctionList, Test_1) {
  ps::list<int> ps_lst = {1, 2, 3, 4, 5};
  ps::list<int> ps_lst_other = {1, 4, 6};
  std::list<int> std_lst = {1, 2, 3, 4, 5};
  std::list<int> std_lst_other = {1, 4, 6};
  ps_lst.merge(ps_lst_other);
  std_lst.merge(std_lst_other);
  ASSERT_EQ(ps_lst.front(), std_lst.front());
  ASSERT_EQ(ps_lst.back(), std_lst.back());
  ASSERT_EQ(ps_lst.size(), std_lst.size());
  size_t i = ps_lst.size();
  auto iter_1 = ps_lst.cbegin();
  auto iter_2 = std_lst.cbegin();
  while (i != 0) {
    ASSERT_EQ(*iter_1, *iter_2);
    ++iter_1;
    ++iter_2;
    --i;
  }
}

TEST(MergeFunctionList, Test_2) {
  ps::list<int> ps_lst = {1, 2, 3, 4, 10};
  ps::list<int> ps_lst_other = {0, 7, 8};
  std::list<int> std_lst = {1, 2, 3, 4, 10};
  std::list<int> std_lst_other = {0, 7, 8};
  ps_lst.merge(ps_lst_other);
  std_lst.merge(std_lst_other);
  ASSERT_EQ(ps_lst.front(), std_lst.front());
  ASSERT_EQ(ps_lst.back(), std_lst.back());
  ASSERT_EQ(ps_lst.size(), std_lst.size());
  size_t i = ps_lst.size();
  auto iter_1 = ps_lst.cbegin();
  auto iter_2 = std_lst.cbegin();
  while (i != 0) {
    ASSERT_EQ(*iter_1, *iter_2);
    ++iter_1;
    ++iter_2;
    --i;
  }
  ASSERT_EQ(ps_lst_other.size(), std_lst_other.size());
}

TEST(InsertManyFunctionList, Test_1) {
  ps::list<int> ps_lst = {1, 5, 6, 7};
  ps_lst.insert_many(++ps_lst.cbegin(), 4, 3, 2);
  auto iter_1 = ps_lst.begin();
  size_t i = 0;
  while (i < ps_lst.size()) {
    ASSERT_EQ(*iter_1, i + 1);
    ++iter_1;
    ++i;
  }
}

TEST(InsertManyBackFunctionList, Test_1) {
  ps::list<int> ps_lst = {1, 2, 3, 4};
  ps_lst.insert_many_back(5, 6, 7);
  auto iter = ps_lst.begin();
  size_t i = 0;
  while (i < ps_lst.size()) {
    ASSERT_EQ(*iter, i + 1);
    ++iter;
    ++i;
  }
}

TEST(InsertManyFrontFunctionList, Test_1) {
  ps::list<int> ps_lst = {4, 5, 6};
  ps_lst.insert_many_front(3, 2, 1);
  auto iter = ps_lst.begin();
  size_t i = 0;
  while (i < ps_lst.size()) {
    ASSERT_EQ(*iter, i + 1);
    ++iter;
    ++i;
  }
}