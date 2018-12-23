//========================================================================
// FILE:
//  test/tests-ch2.cpp
//
// AUTHOR:
//  banach-space@github
//
// DESCRIPTION:
//    Unit tests for solutions to practice questions from Chapter 2 in [1]
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

    removeDuplicates<TypeParam, int>(&test_list);

    std::vector<int> out_vect = cci::getVector<TypeParam, int>(test_list);
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
      test_list.push_back(value);
    }

    // Remove "item" from the list and extract the elements in the list.
    typename cci::List<int>::Node *temp = test_list.begin().get();
    while (nullptr != temp && temp->val_ != *it) {
      temp = temp->next_;
    }
    deleteNode<int>(temp);
    std::vector<int> out_vect = cci::getVector<cci::List<int>, int>(test_list);

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
    std::vector<int> out_vect = cci::getVector<TypeParam, int>(test_list);

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

    std::vector<int> out_vect = cci::getVector<TypeParam, int>(test_list);

    EXPECT_EQ(out_vect, std::get<1>(test_case));
  }
}

//------------------------------------------------------------------------
// Tests for Solution to Q5
//------------------------------------------------------------------------
template <typename T>
class CciChapter2_Q5 : public ::testing::Test {
};

using ListValTypes_Q5 = ::testing::Types<cci::List<int>, std::list<int>>;
TYPED_TEST_CASE(CciChapter2_Q5, ListValTypes_Q5);

TYPED_TEST(CciChapter2_Q5, sumNumbersAsAListReverse) {
  std::vector<std::tuple<std::vector<int>, std::vector<int>, std::vector<int>>>
    test_cases = {
    {{}, {}, {}},
    {{1, 2, 3}, {1, 2, 3}, {2, 4, 6}},
    {{1, 2, 3}, {9, 8, 7}, {0, 1, 1, 1}},
    {{1, 2, 3, 1, 1}, {9, 8, 7}, {0, 1, 1, 2, 1}},
  };

  for (auto test_case : test_cases) {
    // Construct input_list1 using the current test_case
    TypeParam test_list1;
    for (auto value : std::get<0>(test_case)) {
      test_list1.push_back(value);
    }

    // Construct input_list2 using the current test_case
    TypeParam test_list2;
    for (auto value : std::get<1>(test_case)) {
      test_list2.push_back(value);
    }

    auto out_list = sumNumbersAsAListReverse<TypeParam, int>(test_list1, test_list2);

    std::vector<int> out_vect = cci::getVector<TypeParam, int>(out_list);

    EXPECT_EQ(out_vect, std::get<2>(test_case));
  }
}

TYPED_TEST(CciChapter2_Q5, sumNumbersAsAList) {
  std::vector<std::tuple<std::vector<int>, std::vector<int>, std::vector<int>>>
    test_cases = {
    {{}, {}, {}},
    {{1, 2, 3}, {1, 2, 3}, {2, 4, 6}},
    {{1, 2, 3}, {9, 8, 7}, {1, 1, 1, 0}},
    {{1, 2, 3, 1, 1}, {9, 8, 7}, {1, 3, 2, 9, 8}},
  };

  for (auto test_case : test_cases) {
    // Construct input_list1 using the current test_case
    TypeParam test_list1;
    for (auto value : std::get<0>(test_case)) {
      test_list1.push_back(value);
    }

    // Construct input_list2 using the current test_case
    TypeParam test_list2;
    for (auto value : std::get<1>(test_case)) {
      test_list2.push_back(value);
    }

    auto out_list = sumNumbersAsAList<TypeParam, int>(test_list1, test_list2);

    std::vector<int> out_vect = cci::getVector<TypeParam, int>(out_list);

    EXPECT_EQ(out_vect, std::get<2>(test_case));
  }
}

//------------------------------------------------------------------------
// Tests for Solution to Q6
//------------------------------------------------------------------------
template <typename T>
class CciChapter2_Q6 : public ::testing::Test {
};

using ListValTypes_Q6 = ::testing::Types<cci::List<int>, std::list<int>>;
TYPED_TEST_CASE(CciChapter2_Q6, ListValTypes_Q6);

TYPED_TEST(CciChapter2_Q6, polindrone) {
  std::vector<std::tuple<std::vector<int>, bool>>
    test_cases = {
      std::make_tuple<std::vector<int>, bool>({}, true),
      // std::make_tuple<std::vector<int>, bool>({1, 2, 3}, false),
      // std::make_tuple<std::vector<int>, bool>({1, 2, 1}, true),
      // std::make_tuple<std::vector<int>, bool>({1, 2, 2, 1}, true),
  };

  for (auto test_case : test_cases) {
    TypeParam test_list;
    for (auto value : std::get<0>(test_case)) {
      test_list.push_back(value);
    }

    EXPECT_EQ(polindrone(test_list), std::get<1>(test_case));
  }
}
