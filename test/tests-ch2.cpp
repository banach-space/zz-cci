//========================================================================
// FILE:
//  test/tests-ch2.cpp
//
// AUTHOR:
//  banach-space@github
//
// DESCRIPTION:
//    Unit tests for:
//      * the implementation of cci::list<T> from chapter_2_list.hpp
//      * solutions to practice questions from Chapter 2 in [1]
//
//    Most of the tests adhere to this workflow:
//      1. Construct the test_list using the predefined elements
//      2. Apply an operation to the test_list
//      3. Check the state of the test_list after the operation and verify that it
//      matches the expected state.
//    For convenience, the elements defining test_lists as well as well the
//    elements defining the expected states after the operator are stored in
//    std::vector<T>. Each distinct test list (i.e. test vector) is referred to
//    as "test case". This is in a bit of clash with the nomenclature within
//    GTest, but hopefully won't be too confusing here.
//
//    [1] "Cracking the Coding Interview", Gayle Laakmann McDowell
//
// License: Apache License 2.0
//========================================================================
#include <chapter_2.hpp>
#include <chapter_2_list.hpp>
#include <gtest/gtest.h>

#include <numeric>
#include <vector>

//========================================================================
// Unit tests fot cci::list
//========================================================================
template <typename T>
class CciChapter2_list : public ::testing::Test {
};

using ListValTypes = ::testing::Types<int, unsigned int, float, double>;
TYPED_TEST_CASE(CciChapter2_list, ListValTypes);

TYPED_TEST(CciChapter2_list, appendToTail) {
  std::vector<std::vector<TypeParam>> test_cases = {
    {},
    {0, 1, 2, 3, 4, 5, 6, 7, 8, 9},
  };

  for (auto &test_case : test_cases) {
    cci::list<TypeParam> test_list;

    for (auto value : test_case) {
      test_list.appendToTail(value);
    }

    std::vector<TypeParam> out_vect = cci::extractAllValues(test_list);
    EXPECT_EQ(out_vect, test_case);
  }
}

TYPED_TEST(CciChapter2_list, deleteAllNodes) {
  std::vector<std::vector<TypeParam>> test_cases = {
    {},
    {0, 1, 2, 3, 4, 5, 6, 7, 8, 9},
    {1, 1, 1, 1, 1, 1, 1, 1, 1, 1},
  };

  std::vector<TypeParam> expected_vec{};
  for (auto &test_case : test_cases) {
    cci::list<TypeParam> test_list;

    for (auto value : test_case) {
      test_list.appendToTail(value);
    }

    typename cci::list<TypeParam>::Node *temp = test_list.getHead();
    while (nullptr != temp) {
      test_list.deleteNode(temp);
      temp = test_list.getHead();
    }

    std::vector<TypeParam> out_vect = cci::extractAllValues(test_list);
    EXPECT_EQ(out_vect, expected_vec);
  }
}

TYPED_TEST(CciChapter2_list, deleteNodesEqual_1) {
  std::vector<std::tuple<std::vector<TypeParam>, std::vector<TypeParam>>> test_cases = {
    {{}, {}},
    {{0, 1, 2, 3, 4, 5, 6, 7, 8, 9}, {0, 2, 3, 4, 5, 6, 7, 8, 9}},
    {{1, 1, 1, 1, 1, 1, 1, 1, 1, 1}, {}},
    {{1, 1, 1, 1, 1, 2, 2, 2, 2, 2}, {2, 2, 2, 2, 2}},
  };

  for (auto &test_case : test_cases) {
    cci::list<TypeParam> test_list;

    for (auto value : std::get<0>(test_case)) {
      test_list.appendToTail(value);
    }

    typename cci::list<TypeParam>::Node *temp = test_list.getHead();
    typename cci::list<TypeParam>::Node *prev = test_list.getHead();

    // Remove 1's at the beginning
    while ((nullptr != temp) && (1 == temp->val)) {
      test_list.deleteNode(temp);
      temp = test_list.getHead();
    }

    if (!test_list.isEmpty()) {
      temp = temp->next;
      while (nullptr != temp) {
        if (1 == temp->val) {
          test_list.deleteNode(temp);
          temp = prev->next;
          continue;
        }

        prev = temp;
        temp = temp->next;
      }
    }

    std::vector<TypeParam> out_vect = cci::extractAllValues(test_list);
    EXPECT_EQ(out_vect, std::get<1>(test_case));
  }
}

TYPED_TEST(CciChapter2_list, eraseNodesEqual_1) {
  std::vector<std::tuple<std::vector<TypeParam>, std::vector<TypeParam>>> test_cases = {
    {{}, {}},
    {{0, 1, 2, 3, 4, 5, 6, 7, 8, 9}, {0, 2, 3, 4, 5, 6, 7, 8, 9}},
    {{1, 1, 1, 1, 1, 1, 1, 1, 1, 1}, {}},
    {{1, 1, 1, 1, 1, 2, 2, 2, 2, 2}, {2, 2, 2, 2, 2}},
  };

  for (auto &test_case : test_cases) {
    cci::list<TypeParam> test_list;

    for (auto value : std::get<0>(test_case)) {
      test_list.appendToTail(value);
    }

    typename cci::list<TypeParam>::Node *it = test_list.getHead();

    // Remove 1's at the beginning
    while ((nullptr != it) && (1 == it->val)) {
      it = test_list.erase(it);
    }

    if (!test_list.isEmpty()) {
      while (nullptr != it) {
        if (1 == it->val) {
          it = test_list.erase(it);
          continue;
        }

        it = it->next;
      }
    }

    std::vector<TypeParam> out_vect = cci::extractAllValues(test_list);
    EXPECT_EQ(out_vect, std::get<1>(test_case));
  }
}

TYPED_TEST(CciChapter2_list, deleteNodesEqual_n) {
  // The initial state of the list
  std::vector<TypeParam> test_case_ref{0, 1, 2, 3, 4, 5, 6, 7, 8, 9};

  // Loop over all items in the list and try removing each (one at a time)
  for (auto item : test_case_ref) {
    // Construct a vector (test_case) using test_case_ref with "item" being
    // removed. This will be used as the expected output.
    std::vector<TypeParam> test_case(test_case_ref);
    auto it = std::find(test_case.begin(), test_case.end(), item);
    test_case.erase(it);

    // Construct a list using test_case_ref
    cci::list<TypeParam> test_list;
    for (auto value : test_case_ref) {
      test_list.appendToTail(value);
    }

    // Remove "item" from the list and extract the elements in the list.
    typename cci::list<TypeParam>::Node *temp = test_list.getHead();
    while (nullptr != temp && temp->val != item) {
      temp = temp->next;
    }
    test_list.deleteNode(temp);
    std::vector<TypeParam> out_vect = cci::extractAllValues(test_list);

    // Finally, do the comparison
    EXPECT_EQ(out_vect, test_case);
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
  std::vector<std::tuple<std::vector<int>, std::vector<int>>> test_cases = {
    {{}, {}},
    {{1, 2, 3, 4}, {1, 2, 3, 4}},
    {{1, 1, 2, 2, 3, 3, 4, 4}, {1, 2, 3, 4}},
    {{1, 2, 3, 4, 1, 2, 3, 4}, {1, 2, 3, 4}},
    {{1, 1, 1, 1, 1, 1, 1, 1, 1, 1}, {1}},
  };

  for (auto &test_case : test_cases) {
    TypeParam test_list;

    for (auto value : std::get<0>(test_case)) {
      test_list.push_back(value);
    }

    removeDuplicates(&test_list);

    std::vector<int> out_vect = cci::extractAllValues(test_list);
    EXPECT_EQ(out_vect, std::get<1>(test_case));
  }
}

//========================================================================
// Tests for solution to Q2
//========================================================================
// For Question 2 I can't used TYPED_TESTs because the interface for cci::list
// and std::list are too different (e.g. cci::list has no iterators, etc, so
// the implementation of the test must be different). I could re-factor
// cci::list to this end, but wanted to avoid it and focus on solving the
// puzzles instead.
static size_t k_q2_num_samples;

TEST(CciChapter2_Q2, findKthElement) {
  std::vector<int> test_case{};
  test_case.resize(k_q2_num_samples);
  std::iota(test_case.begin(), test_case.end(), 0);

  cci::list<int> test_list;
  for (auto ii = 0u; ii < k_q2_num_samples; ii++) {
    test_list.push_back(ii);
  }

  for (auto ii = 0u; ii < k_q2_num_samples; ii++) {
    auto result = findKthElement(test_list, ii);

    auto expected_val = test_case[k_q2_num_samples - 1 - ii];
    EXPECT_NE(nullptr, result);
    EXPECT_EQ(result->val, expected_val);
  }
}

TEST(CciChapter2_Q2, findKthElement2) {
  std::vector<int> test_case{};
  test_case.resize(k_q2_num_samples);
  std::iota(test_case.begin(), test_case.end(), 0);

  std::list<int> test_list;
  for (auto ii = 0u; ii < k_q2_num_samples; ii++) {
    test_list.push_back(ii);
  }

  for (auto ii = 0u; ii < k_q2_num_samples; ii++) {
    auto result = findKthElement(test_list, ii);

    auto expected_val = test_case[k_q2_num_samples - 1 - ii];
    EXPECT_EQ(*result, expected_val);
  }
}
