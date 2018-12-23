//========================================================================
// FILE:
//  test/tests-List.cpp
//
// AUTHOR:
//  banach-space@github
//
// DESCRIPTION:
//    Unit tests for the implementation of cci::List<T> from chapter_2_list.hpp
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
#include <algorithm>

template <typename T>
class CciChapter2_list : public ::testing::Test {
};

using ListValTypes = ::testing::Types<int, unsigned int, float, double>;
TYPED_TEST_CASE(CciChapter2_list, ListValTypes);

TYPED_TEST(CciChapter2_list, push_back) {
  std::vector<std::vector<TypeParam>> test_cases = {
    {},
    {1},
    {0, 1, 2, 3, 4, 5, 6, 7, 8, 9},
    {1, 1, 1, 1, 1, 1, 1, 1, 1, 1},
  };

  for (auto &test_case : test_cases) {
    cci::List<TypeParam> test_list;

    for (auto value : test_case) {
      test_list.push_back(value);
    }

    auto out_vect = cci::getVector<cci::List<TypeParam>, TypeParam>(test_list);
    EXPECT_EQ(out_vect, test_case);
  }
}

TYPED_TEST(CciChapter2_list, push_front) {
  std::vector<std::vector<TypeParam>> test_cases = {
    {},
    {1},
    {0, 1, 2, 3, 4, 5, 6, 7, 8, 9},
    {1, 1, 1, 1, 1, 1, 1, 1, 1, 1},
  };

  for (auto &test_case : test_cases) {
    cci::List<TypeParam> test_list;

    for (auto value : test_case) {
      test_list.push_front(value);
    }

    std::reverse(test_case.begin(), test_case.end());
    auto out_vect = cci::getVector<cci::List<TypeParam>, TypeParam>(test_list);
    EXPECT_EQ(out_vect, test_case);
  }
}

TYPED_TEST(CciChapter2_list, erase_all_nodes) {
  std::vector<std::vector<TypeParam>> test_cases = {
    {},
    {1},
    {0, 1, 2, 3, 4, 5, 6, 7, 8, 9},
    {1, 1, 1, 1, 1, 1, 1, 1, 1, 1},
  };

  std::vector<TypeParam> expected_vec{};
  for (auto &test_case : test_cases) {
    cci::List<TypeParam> test_list;

    for (auto value : test_case) {
      test_list.push_back(value);
    }

    while (!test_list.empty()) {
      test_list.erase(test_list.begin());
    }

    auto out_vect = cci::getVector<cci::List<TypeParam>, TypeParam>(test_list);
    EXPECT_EQ(out_vect, expected_vec);
  }
}

TYPED_TEST(CciChapter2_list, erase_nodes_equal_1) {
  std::vector<std::tuple<std::vector<TypeParam>, std::vector<TypeParam>>> test_cases = {
    {{}, {}},
    {{1}, {}},
    {{0, 1, 2, 3, 4, 5, 6, 7, 8, 9}, {0, 2, 3, 4, 5, 6, 7, 8, 9}},
    {{1, 1, 1, 1, 1, 1, 1, 1, 1, 1}, {}},
    {{1, 1, 1, 1, 1, 2, 2, 2, 2, 2}, {2, 2, 2, 2, 2}},
  };

  for (auto &test_case : test_cases) {
    cci::List<TypeParam> test_list;

    for (auto value : std::get<0>(test_case)) {
      test_list.push_back(value);
    }

    auto it = test_list.begin();
    while (it != test_list.end())
    {
      if (1 == *it) {
        it = test_list.erase(it);
      } else {
        it++;
      }
    }

    auto out_vect = cci::getVector<cci::List<TypeParam>, TypeParam>(test_list);
    EXPECT_EQ(out_vect, std::get<1>(test_case));
  }
}

TYPED_TEST(CciChapter2_list, erase_nodes_equal_n) {
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
      test_list.push_back(value);
    }

    // Remove "item" from the list and extract the elements in the list.
    auto it2 = std::find(test_list.begin(), test_list.end(), item);
    test_list.erase(it2);
    auto out_vect = cci::getVector<cci::List<TypeParam>, TypeParam>(test_list);

    // Finally, do the comparison
    EXPECT_EQ(out_vect, test_case);
  }
}

TEST(CciChapter2_list, empty) {
  std::vector<std::tuple<std::vector<int>, bool>> test_cases = {
    {{}, true},
    {{1}, false},
    {{0, 1, 2, 3, 4, 5, 6, 7, 8, 9}, false},
  };

  for (auto &test_case : test_cases) {
    cci::List<int> test_list;

    for (auto value : std::get<0>(test_case)) {
      test_list.push_back(value);
    }

    EXPECT_EQ(test_list.empty(), std::get<1>(test_case));
  }
}

TEST(CciChapter2_list, size) {
  std::vector<std::tuple<std::vector<int>, size_t>> test_cases = {
    {{}, 0},
    {{1}, 1},
    {{0, 1, 2, 3, 4, 5, 6, 7, 8, 9}, 10},
  };

  for (auto &test_case : test_cases) {
    cci::List<int> test_list;

    for (auto value : std::get<0>(test_case)) {
      test_list.push_back(value);
    }

    EXPECT_EQ(test_list.size(), std::get<1>(test_case));
  }
}

template <typename T>
class CciChapter2_list_iterator : public ::testing::Test {
};

TEST(CciChapter2_list_iterator, begin_and_end) {
  std::vector<std::vector<int>> test_cases = {
    {1},
    {0, 1, 2, 3, 4, 5, 6, 7, 8, 9},
    {1, 1, 1, 1, 1, 1, 1, 1, 1, 1}, 
    {1, 1, 1, 1, 1, 2, 2, 2, 2, 2}, 
  };

  for (auto &test_case : test_cases) {
    cci::List<int> test_list;

    for (auto value : test_case) {
      test_list.push_back(value);
    }

    EXPECT_EQ(*test_list.begin(), *test_case.begin());
    EXPECT_EQ(*(--test_list.end()), *(--test_case.end()));

    EXPECT_EQ(*test_list.cbegin(), *test_case.cbegin());
    EXPECT_EQ(*(--test_list.cend()), *(--test_case.cend()));
  }
}

TEST(CciChapter2_list_iterator, begin_equals_end) {
  cci::List<int> test_list;

  EXPECT_EQ(test_list.begin(), test_list.end());
  EXPECT_EQ(test_list.cbegin(), test_list.cend());
}
