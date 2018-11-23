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

// TEST(CciChapter2_List, smokeTest) {
//   std::vector<std::vector<int>> test_lists = {
//     {},
//     {0, 1, 2, 3, 4, 5, 6, 7, 8, 9},
//   };

//   for (auto &test_case : test_lists) {
//     Cci::List<int> list;

//     for (auto value : test_case) {
//       list.appendToTail(value);
//     }

//     std::vector<int> out_vect = list.getAllValues();
//     EXPECT_EQ(out_vect, test_case);
//   }
// }

template <typename T>
class CciChapter2_List : public ::testing::Test {

};

using ListValTypes = ::testing::Types<int, unsigned int, float, double>;
TYPED_TEST_CASE(CciChapter2_List, ListValTypes);

TYPED_TEST(CciChapter2_List, SmokeTest) {
  std::vector<std::vector<TypeParam>> test_lists = {
    {},
    {0, 1, 2, 3, 4, 5, 6, 7, 8, 9},
  };

  for (auto &test_case : test_lists) {
    Cci::List<TypeParam> list;

    for (auto value : test_case) {
      list.appendToTail(value);
    }

    std::vector<TypeParam> out_vect = list.getAllValues();
    EXPECT_EQ(out_vect, test_case);
  }
}

TYPED_TEST(CciChapter2_List, deleteAllNodes) {
  std::vector<std::vector<TypeParam>> test_lists = {
    {},
    {0, 1, 2, 3, 4, 5, 6, 7, 8, 9},
    {1, 1, 1, 1, 1, 1, 1, 1, 1, 1},
  };

  std::vector<TypeParam> expected_vec{};
  for (auto &test_case : test_lists) {
    Cci::List<TypeParam> list;

    for (auto value : test_case) {
      list.appendToTail(value);
    }

    typename Cci::List<TypeParam>::Node *temp = list.getHead();
    while (nullptr != temp) {
      list.deleteNode(temp);
      temp = list.getHead();
    }

    std::vector<TypeParam> out_vect = list.getAllValues();
    EXPECT_EQ(out_vect, expected_vec);
  }
}

TYPED_TEST(CciChapter2_List, deleteNodesEqual_1) {
  std::vector<std::tuple<std::vector<TypeParam>, std::vector<TypeParam>>> test_lists = {
    {{}, {}},
    {{0, 1, 2, 3, 4, 5, 6, 7, 8, 9}, {0, 2, 3, 4, 5, 6, 7, 8, 9}},
    {{1, 1, 1, 1, 1, 1, 1, 1, 1, 1}, {}},
    {{1, 1, 1, 1, 1, 2, 2, 2, 2, 2}, {2, 2, 2, 2, 2}},
  };

  for (auto &test_case : test_lists) {
    Cci::List<TypeParam> list;

    for (auto value : std::get<0>(test_case)) {
      list.appendToTail(value);
    }

    typename Cci::List<TypeParam>::Node *temp = list.getHead();
    typename Cci::List<TypeParam>::Node *prev = list.getHead();

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

    std::vector<TypeParam> out_vect = list.getAllValues();
    EXPECT_EQ(out_vect, std::get<1>(test_case));
  }
}

TYPED_TEST(CciChapter2_List, deleteNodesEqual_n) {
  std::vector<TypeParam> test_list_ref{0, 1, 2, 3, 4, 5, 6, 7, 8, 9};
  std::vector<TypeParam> test_list_ref2{0, 1, 2, 3, 4, 5, 6, 7, 8, 9};

  for (auto item : test_list_ref) {
    std::vector<TypeParam> test_list(test_list_ref);
    Cci::List<TypeParam> list;

    for (auto value : test_list_ref2) {
      list.appendToTail(value);
    }

    typename Cci::List<TypeParam>::Node *temp = list.getHead();
    while (nullptr != temp && temp->val != item) {
      temp = temp->next;
    }
    list.deleteNode(temp);

    auto it = std::find(test_list.begin(), test_list.end(), item);
    test_list.erase(it);
    std::vector<TypeParam> out_vect = list.getAllValues();
    EXPECT_EQ(out_vect, test_list);
  }
}

TEST(CciChapter2_Q1, removeDuplicates) {
  std::vector<std::tuple<std::vector<int>, std::vector<int>>> test_lists = {
    {{}, {}},
    {{1, 2, 3, 4}, {1, 2, 3, 4}},
    {{1, 1, 2, 2, 3, 3, 4, 4}, {1, 2, 3, 4}},
    {{1, 2, 3, 4, 1, 2, 3, 4}, {1, 2, 3, 4}},
  };

  for (auto &test_case : test_lists) {
    Cci::List<int> list;

    for (auto value : std::get<0>(test_case)) {
      list.appendToTail(value);
    }

    list.removeDuplicates();

    std::vector<int> out_vect = list.getAllValues();
    EXPECT_EQ(out_vect, std::get<1>(test_case));
  }
}
