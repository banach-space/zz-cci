//========================================================================
// FILE:
//  test/tests-ch4.cpp
//
// AUTHOR:
//  banach-space@github
//
// DESCRIPTION:
//    Unit tests for solutions to practice questions from Chapter 4 in [1]
//
//    [1] "Cracking the Coding Interview", Gayle Laakmann McDowell
//
// License: Apache License 2.0
//========================================================================
#include <gtest/gtest.h>

#include <algorithm>
#include <numeric>
#include <vector>

#include <chapter_4.hpp>
#include <chapter_4_Bst.hpp>

//-----------------------------------------------------------------------------
// Tests for Solution to Q1
//-----------------------------------------------------------------------------
TEST(CciChapter4_Q1, balanced) {
  std::vector<std::tuple<std::vector<int>, bool>> test_cases = {
      {std::vector<int>{}, true},
      {{1, 2, 3, 4, 5, 6, 7, 8, 9, 10}, false},
      {{10, 9, 8, 7, 6, 5, 4, 3, 2, 1}, false},
      {{5, 3, 8, 2, 4, 6, 9, 1, 7}, true},
  };

  for (auto &test_case : test_cases) {
    cci::Bst test_tree;

    for (auto value : std::get<0>(test_case)) {
      test_tree.insert(value);
    }

    EXPECT_EQ(test_tree.isBalanced(), std::get<1>(test_case));
  }
}

//-----------------------------------------------------------------------------
// Tests for Solution to Q2
//-----------------------------------------------------------------------------
// TODO

//-----------------------------------------------------------------------------
// Tests for Solution to Q3
//-----------------------------------------------------------------------------
TEST(CciChapter4_Q3, create_min_bst) {
  std::vector<std::vector<int>> test_cases = {
      {},
      {1},
      {1, 2},
      {1, 2, 3, 4, 5, 6, 7, 8, 9, 10},
      {1, 10, 100, 1000, 10000, 100000, 10000000},
      {1, 12, 123, 1234, 12345, 123456, 1234567, 12345678, 123456789}};

  for (auto &test_case : test_cases) {
    cci::Bst test_tree = cci::createMinBst(test_case);

    std::vector<int> out_vect = test_tree.getVector();

    EXPECT_EQ(out_vect, test_case);
    EXPECT_TRUE(test_tree.isBalanced());
  }
}
