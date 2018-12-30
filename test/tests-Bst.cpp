//========================================================================
// FILE:
//  test/tests-ch4.cpp
//
// AUTHOR:
//  banach-space@github
//
// DESCRIPTION:
//    Unit tests for cci::Bst
//
//    [1] "Cracking the Coding Interview", Gayle Laakmann McDowell
//
// License: Apache License 2.0
//========================================================================
#include <gtest/gtest.h>

#include <algorithm>
#include <numeric>
#include <vector>

#include <chapter_4_Bst.hpp>

//-----------------------------------------------------------------------------
// Tests for cci::Bst
//-----------------------------------------------------------------------------
TEST(CciChapter4, Bst) {
  std::vector<std::vector<int>> test_cases = {
      {1, 2, 3, 4, 5, 6, 7, 8, 9, 10},
      {10, 9, 8, 7, 6, 5, 4, 3, 2, 1},
      {13, 7, 1234, 777, 987, 84, 45, 18}};

  for (auto &test_case : test_cases) {
    cci::Bst test_tree;

    for (auto value : test_case) {
      test_tree.insert(value);
    }

    std::sort(test_case.begin(), test_case.end());

    std::vector<int> out_vect = test_tree.getVector();
    EXPECT_EQ(out_vect, test_case);
  }
}
