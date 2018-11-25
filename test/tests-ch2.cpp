//========================================================================
// FILE:
//  test/tests-ch2.cpp
//
// AUTHOR:
//  banach-space@github
//
// DESCRIPTION:
//    Unit tests for solutions to practice questions from Chapter 2 in [1] as
//    well as the implementation of the list from chapter_2_list.hpp.
//
//    [1] "Cracking the Coding Interview", Gayle Laakmann McDowell
//
// License: Apache License 2.0
//========================================================================
#include <gtest/gtest.h>
#include <vector>

#include <chapter_2.hpp>
#include <chapter_2_list.hpp>


//========================================================================
// Tests fot cci::list
//========================================================================
template <typename T>
class CciChapter2_list : public ::testing::Test {
};

using ListValTypes = ::testing::Types<int, unsigned int, float, double>;
TYPED_TEST_CASE(CciChapter2_list, ListValTypes);

TYPED_TEST(CciChapter2_list, appendToTail) {
  std::vector<std::vector<TypeParam>> test_lists = {
    {},
    {0, 1, 2, 3, 4, 5, 6, 7, 8, 9},
  };

  for (auto &test_case : test_lists) {
    cci::list<TypeParam> list;

    for (auto value : test_case) {
      list.appendToTail(value);
    }

    std::vector<TypeParam> out_vect = cci::extractAllValues(list);
    EXPECT_EQ(out_vect, test_case);
  }
}

TYPED_TEST(CciChapter2_list, deleteAllNodes) {
  std::vector<std::vector<TypeParam>> test_lists = {
    {},
    {0, 1, 2, 3, 4, 5, 6, 7, 8, 9},
    {1, 1, 1, 1, 1, 1, 1, 1, 1, 1},
  };

  std::vector<TypeParam> expected_vec{};
  for (auto &test_case : test_lists) {
    cci::list<TypeParam> list;

    for (auto value : test_case) {
      list.appendToTail(value);
    }

    typename cci::list<TypeParam>::Node *temp = list.getHead();
    while (nullptr != temp) {
      list.deleteNode(temp);
      temp = list.getHead();
    }

    std::vector<TypeParam> out_vect = cci::extractAllValues(list);
    EXPECT_EQ(out_vect, expected_vec);
  }
}

TYPED_TEST(CciChapter2_list, deleteNodesEqual_1) {
  std::vector<std::tuple<std::vector<TypeParam>, std::vector<TypeParam>>> test_lists = {
    {{}, {}},
    {{0, 1, 2, 3, 4, 5, 6, 7, 8, 9}, {0, 2, 3, 4, 5, 6, 7, 8, 9}},
    {{1, 1, 1, 1, 1, 1, 1, 1, 1, 1}, {}},
    {{1, 1, 1, 1, 1, 2, 2, 2, 2, 2}, {2, 2, 2, 2, 2}},
  };

  for (auto &test_case : test_lists) {
    cci::list<TypeParam> list;

    for (auto value : std::get<0>(test_case)) {
      list.appendToTail(value);
    }

    typename cci::list<TypeParam>::Node *temp = list.getHead();
    typename cci::list<TypeParam>::Node *prev = list.getHead();

    // Remove 1's at the beginning
    while ((nullptr != temp) && (1 == temp->val)) {
      list.deleteNode(temp);
      temp = list.getHead();
    }

    if (!list.isEmpty()) {
      temp = temp->next;
      while (nullptr != temp) {
        if (1 == temp->val) {
          list.deleteNode(temp);
          temp = prev->next;
          continue;
        }

        prev = temp;
        temp = temp->next;
      }
    }

    std::vector<TypeParam> out_vect = cci::extractAllValues(list);
    EXPECT_EQ(out_vect, std::get<1>(test_case));
  }
}

TYPED_TEST(CciChapter2_list, eraseNodesEqual_1) {
  std::vector<std::tuple<std::vector<TypeParam>, std::vector<TypeParam>>> test_lists = {
    {{}, {}},
    {{0, 1, 2, 3, 4, 5, 6, 7, 8, 9}, {0, 2, 3, 4, 5, 6, 7, 8, 9}},
    {{1, 1, 1, 1, 1, 1, 1, 1, 1, 1}, {}},
    {{1, 1, 1, 1, 1, 2, 2, 2, 2, 2}, {2, 2, 2, 2, 2}},
  };

  for (auto &test_case : test_lists) {
    cci::list<TypeParam> list;

    for (auto value : std::get<0>(test_case)) {
      list.appendToTail(value);
    }

    typename cci::list<TypeParam>::Node *it = list.getHead();

    // Remove 1's at the beginning
    while ((nullptr != it) && (1 == it->val)) {
      it = list.erase(it);
    }

    if (!list.isEmpty()) {
      while (nullptr != it) {
        if (1 == it->val) {
          it = list.erase(it);
          continue;
        }

        it = it->next;
      }
    }

    std::vector<TypeParam> out_vect = cci::extractAllValues(list);
    EXPECT_EQ(out_vect, std::get<1>(test_case));
  }
}

TYPED_TEST(CciChapter2_list, deleteNodesEqual_n) {
  std::vector<TypeParam> test_list_ref{0, 1, 2, 3, 4, 5, 6, 7, 8, 9};
  std::vector<TypeParam> test_list_ref2{0, 1, 2, 3, 4, 5, 6, 7, 8, 9};

  for (auto item : test_list_ref) {
    std::vector<TypeParam> test_list(test_list_ref);
    cci::list<TypeParam> list;

    for (auto value : test_list_ref2) {
      list.appendToTail(value);
    }

    typename cci::list<TypeParam>::Node *temp = list.getHead();
    while (nullptr != temp && temp->val != item) {
      temp = temp->next;
    }
    list.deleteNode(temp);

    auto it = std::find(test_list.begin(), test_list.end(), item);
    test_list.erase(it);
    std::vector<TypeParam> out_vect = cci::extractAllValues(list);
    EXPECT_EQ(out_vect, test_list);
  }
}

//========================================================================
// Tests for solution to Q1
//========================================================================
template <typename T>
class CciChapter2_Q1 : public ::testing::Test {
};

using ListValTypes_Q1 = ::testing::Types<cci::list<int>, std::list<int>>;
TYPED_TEST_CASE(CciChapter2_Q1, ListValTypes_Q1);

TYPED_TEST(CciChapter2_Q1, removeDuplicates) {
  std::vector<std::tuple<std::vector<int>, std::vector<int>>> test_lists = {
    {{}, {}},
    {{1, 2, 3, 4}, {1, 2, 3, 4}},
    {{1, 1, 2, 2, 3, 3, 4, 4}, {1, 2, 3, 4}},
    {{1, 2, 3, 4, 1, 2, 3, 4}, {1, 2, 3, 4}},
  };

  for (auto &test_case : test_lists) {
    TypeParam list;

    for (auto value : std::get<0>(test_case)) {
      list.push_back(value);
    }

    removeDuplicates(&list);

    std::vector<int> out_vect = cci::extractAllValues(list);
    EXPECT_EQ(out_vect, std::get<1>(test_case));
  }
}
