//========================================================================
// FILE:
//  test/tests-ch4-binary_tree.cpp
//
// AUTHOR:
//  banach-space@github
//
// DESCRIPTION:
//    Unit tests for cci::BinaryTree and cci::Bst
//
//    [1] "Cracking the Coding Interview", Gayle Laakmann McDowell
//
// License: Apache License 2.0
//========================================================================
#include <gtest/gtest.h>

#include <algorithm>
#include <numeric>
#include <vector>

#include <chapter_4_binary_tree.hpp>

template <typename T> class CciChapter4_BinaryTrees : public ::testing::Test {};

using TreeTypes = ::testing::Types<cci::BinaryTree, cci::Bst>;
TYPED_TEST_SUITE(CciChapter4_BinaryTrees, TreeTypes);

TYPED_TEST(CciChapter4_BinaryTrees, empty_tree) {

  std::vector<int> test_case{};
  TypeParam test_tree;

  for (auto value : test_case) {
    test_tree.insert(value);
  }

  EXPECT_TRUE(test_tree.isEmpty());
}

TEST(CciChapter4, build_basic_binary_tree) {
  // Vector used to generate the tree
  std::vector<int> test_case = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
  // Expected vector of values when calling getVector on the tree generated
  // with test_case.
  std::vector<int> expected_output = {8, 4, 9, 2, 10, 5, 1, 6, 3, 7};

  cci::BinaryTree test_tree;

  for (auto value : test_case) {
    test_tree.insert(value);
  }

  std::vector<int> out_vect = test_tree.getVector();
  EXPECT_EQ(out_vect, expected_output);
}

TEST(CciChapter4, build_basic_bst_tree) {
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
