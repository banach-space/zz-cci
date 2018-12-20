//========================================================================
// FILE:
//  test/tests-ch2.cpp
//
// AUTHOR:
//  banach-space@github
//
// DESCRIPTION:
//    Unit tests for:
//      * the implementation of cci::List<T> from chapter_2_list.hpp
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
// Unit tests fot cci::List
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
    cci::List<TypeParam> test_list;

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
    cci::List<TypeParam> test_list;

    for (auto value : test_case) {
      test_list.appendToTail(value);
    }

    typename cci::List<TypeParam>::Node *temp = test_list.getHead();
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
    cci::List<TypeParam> test_list;

    for (auto value : std::get<0>(test_case)) {
      test_list.appendToTail(value);
    }

    typename cci::List<TypeParam>::Node *temp = test_list.getHead();
    typename cci::List<TypeParam>::Node *prev = test_list.getHead();

    // Remove 1's at the beginning
    while ((nullptr != temp) && (1 == temp->val_)) {
      test_list.deleteNode(temp);
      temp = test_list.getHead();
    }

    if (!test_list.isEmpty()) {
      temp = temp->next_;
      while (nullptr != temp) {
        if (1 == temp->val_) {
          test_list.deleteNode(temp);
          temp = prev->next_;
          continue;
        }

        prev = temp;
        temp = temp->next_;
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
    cci::List<TypeParam> test_list;

    for (auto value : std::get<0>(test_case)) {
      test_list.appendToTail(value);
    }

    typename cci::List<TypeParam>::Node *it = test_list.getHead();

    // Remove 1's at the beginning
    while ((nullptr != it) && (1 == it->val_)) {
      it = test_list.erase(it);
    }

    if (!test_list.isEmpty()) {
      while (nullptr != it) {
        if (1 == it->val_) {
          it = test_list.erase(it);
          continue;
        }

        it = it->next_;
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
    cci::List<TypeParam> test_list;
    for (auto value : test_case_ref) {
      test_list.appendToTail(value);
    }

    // Remove "item" from the list and extract the elements in the list.
    typename cci::List<TypeParam>::Node *temp = test_list.getHead();
    while (nullptr != temp && temp->val_ != item) {
      temp = temp->next_;
    }
    test_list.deleteNode(temp);
    std::vector<TypeParam> out_vect = cci::extractAllValues(test_list);

    // Finally, do the comparison
    EXPECT_EQ(out_vect, test_case);
  }
}

//========================================================================
// Tests for solutions to the questions in Chapter 2
//========================================================================
//------------------------------------------------------------------------
// Tests for Solution to Q1
//------------------------------------------------------------------------
template <typename T>
class CciChapter2_Q1 : public ::testing::Test {
};

using ListValTypes_Q1 = ::testing::Types<cci::List<int>, std::list<int>>;
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

//------------------------------------------------------------------------
// Tests for Solution to Q2
//------------------------------------------------------------------------
// For Question 2 I can't used TYPED_TESTs because the interface for cci::List
// and std::list are too different (e.g. cci::List has no iterators, etc, so
// the implementation of the test must be different). I could re-factor
// cci::List to this end, but wanted to avoid it and focus on solving the
// puzzles instead.
static size_t k_q2_num_samples;

TEST(CciChapter2_Q2, findKthElementBasic) {
  std::vector<int> test_case{};
  test_case.resize(k_q2_num_samples);
  std::iota(test_case.begin(), test_case.end(), 0);

  cci::List<int> test_list;
  for (auto ii = 0u; ii < k_q2_num_samples; ii++) {
    test_list.push_back(ii);
  }

  for (auto ii = 0u; ii < k_q2_num_samples; ii++) {
    typename cci::List<int>::Node* result = findKthElementBasic(test_list, ii);

    auto expected_val = test_case[k_q2_num_samples - 1 - ii];
    EXPECT_NE(nullptr, result);
    EXPECT_EQ(result->val_, expected_val);
  }
}

template <typename T>
class CciChapter2_Q2 : public ::testing::Test {
};

using ListValTypes_Q2 = ::testing::Types<cci::List<int>, std::list<int>>;
TYPED_TEST_CASE(CciChapter2_Q2, ListValTypes_Q2);

TYPED_TEST(CciChapter2_Q2, findKthElement3) {
  std::vector<int> test_case{};
  test_case.resize(k_q2_num_samples);
  std::iota(test_case.begin(), test_case.end(), 0);

  TypeParam test_list;
  for (auto ii = 0u; ii < k_q2_num_samples; ii++) {
    test_list.push_back(ii);
  }

  for (auto k = 0u; k < k_q2_num_samples; k++) {
    typename TypeParam::const_iterator result = findKthElement(test_list, k);

    auto expected_val = test_case[k_q2_num_samples - 1 - k];
    EXPECT_EQ(*result, expected_val);
  }

}

//------------------------------------------------------------------------
// Tests for Solution to Q3
//------------------------------------------------------------------------
TEST(CciChapter2_Q3, deleteNodePtr) {

  // The initial state of the list
  std::vector<int> test_case_ref{0, 1, 2, 3, 4, 5, 6, 7, 8, 9};

  // Loop over all items in the list and try removing each (one at a time)
  for (auto it = test_case_ref.begin(); it < test_case_ref.end(); it++) {
    // deleteNode can't delete the last node in a list, so skip it
    if (it == --test_case_ref.end()) {
      return;
    }

    // Construct a list using test_case_ref
    cci::List<int> test_list;
    for (auto value : test_case_ref) {
      test_list.appendToTail(value);
    }

    // Remove "item" from the list and extract the elements in the list.
    typename cci::List<int>::Node *temp = test_list.getHead();
    while (nullptr != temp && temp->val_ != *it) {
      temp = temp->next_;
    }
    deleteNode<int>(temp);
    std::vector<int> out_vect = cci::extractAllValues(test_list);

    // Construct a vector (test_case) using test_case_ref with item pointed by
    // "it" being removed. This will be used as the expected output.
    std::vector<int> test_case(test_case_ref);
    auto it2 = std::find(std::begin(test_case), std::end(test_case), *it);
    test_case.erase(it2);

    // Finally, do the comparison
    EXPECT_EQ(out_vect, test_case);
  }
}

template <typename T>
class CciChapter2_Q3 : public ::testing::Test {
};

using ListValTypes_Q3 = ::testing::Types<cci::List<int>, std::list<int>>;
TYPED_TEST_CASE(CciChapter2_Q3, ListValTypes_Q3);

TYPED_TEST(CciChapter2_Q3, deleteNodeIterator) {
  // The initial state of the list
  std::vector<int> test_case_ref{0, 1, 2, 3, 4, 5, 6, 7, 8, 9};

  // Loop over all items in the list and try removing each (one at a time)
  for (auto it = test_case_ref.begin(); it < test_case_ref.end(); it++) {
    // deleteNode can't delete the last node in a list, so skip it
    if (it == --test_case_ref.end()) {
      return;
    }

    // Construct a list using test_case_ref
    TypeParam test_list;
    for (auto value : test_case_ref) {
      test_list.push_back(value);
    }

    // Remove "item" from the list and extract the elements in the list.
    typename TypeParam::iterator temp = test_list.begin();
    if (*temp != *it) {
      do {
        temp++;
      }
      while (test_list.end() != temp && *temp != *it);
    }
    test_list.erase(temp);
    std::vector<int> out_vect = cci::extractAllValues(test_list);

    // Construct a vector (test_case) using test_case_ref with item pointed by
    // "it" being removed. This will be used as the expected output.
    std::vector<int> test_case(test_case_ref);
    auto it2 = std::find(std::begin(test_case), std::end(test_case), *it);
    test_case.erase(it2);

    // Finally, do the comparison
    EXPECT_EQ(out_vect, test_case);
  }
}

//------------------------------------------------------------------------
// Tests for Solution to Q4
//------------------------------------------------------------------------
template <typename T>
class CciChapter2_Q4 : public ::testing::Test {
};

using ListValTypes_Q4 = ::testing::Types<cci::List<int>, std::list<int>>;
TYPED_TEST_CASE(CciChapter2_Q4, ListValTypes_Q4);

TYPED_TEST(CciChapter2_Q4, partition) {

  std::vector<std::tuple<std::vector<int>, std::vector<int>, int>> test_cases = {
    {{}, {}, 5},
    {{0, 9, 0, 9, 0, 9, 0, 9, 0, 9}, {0, 0, 0, 0, 0, 9, 9, 9, 9, 9}, 5},
    {{1, 1, 1, 1, 1, 1, 1, 1, 1, 1}, {1, 1, 1, 1, 1, 1, 1, 1, 1, 1}, 5},
    {{13, 13, 13, 13, 13, 7, 7}, {13, 13, 13, 13, 13, 7, 7}, 5},
    {{1, 2, 3, 4, 5, 6, 7, 8, 9}, {1, 2, 3, 4, 5, 6, 7, 8, 9}, 5},
  };

  for (auto test_case : test_cases) {
    // Construct a list using the current test_case
    TypeParam test_list;
    for (auto value : std::get<0>(test_case)) {
      test_list.push_back(value);
    }

    partition<TypeParam, int>(test_list, std::get<2>(test_case));

    std::vector<int> out_vect = cci::extractAllValues(test_list);

    EXPECT_EQ(out_vect, std::get<1>(test_case));
  }
}

TEST(CciChapter2_Q4, partition2) {

  std::vector<std::tuple<std::vector<int>, std::vector<int>, int>> test_cases = {
    {{}, {}, 5},
    {{0, 9, 0, 9, 0, 9, 0, 9, 0, 9}, {0, 0, 0, 0, 0, 9, 9, 9, 9, 9}, 5},
    {{1, 1, 1, 1, 1, 1, 1, 1, 1, 1}, {1, 1, 1, 1, 1, 1, 1, 1, 1, 1}, 5},
    {{13, 13, 13, 13, 13, 7, 7}, {13, 13, 13, 13, 13, 7, 7}, 5},
    {{1, 2, 3, 4, 5, 6, 7, 8, 9}, {1, 2, 3, 4, 5, 6, 7, 8, 9}, 5},
  };

  for (auto test_case : test_cases) {
    // Construct a list using the current test_case
    cci::List<int> test_list;
    for (auto value : std::get<0>(test_case)) {
      test_list.push_back(value);
    }

    auto out_list = partition2<int>(test_list, std::get<2>(test_case));

    std::vector<int> out_vect = cci::extractAllValues(out_list);

    EXPECT_EQ(out_vect, std::get<1>(test_case));
  }
}
