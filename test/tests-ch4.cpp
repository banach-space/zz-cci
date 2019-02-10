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
#include <climits>

#include <chapter_4.hpp>
#include <chapter_4_binary_tree.hpp>

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

//-----------------------------------------------------------------------------
// Tests for Solution to Q4
//-----------------------------------------------------------------------------
TEST(CciChapter4_Q4, create_level_linked_lists) {
  std::vector<std::tuple<std::vector<int>, std::vector<std::list<int>>>>
    test_cases = {
    {{}, {}},
    {{1}, {{1}}},
    {{5, 3, 8, 2, 4, 6, 9, 1, 7}, {{5}, {3, 8}, {2, 4, 6, 9}, {1, 7}}}
  };

  for (auto &test_case : test_cases) {
    cci::Bst test_tree;

    for (auto value : std::get<0>(test_case)) {
      test_tree.insert(value);
    }

    cci::arrayBstLevels out_vect =
      createLevelLinkedList(test_tree.getRoot());

    size_t num_expected_lists = std::get<1>(test_case).size();

    EXPECT_EQ(num_expected_lists, out_vect.size());
    // for (size_t ii = 0; ii < num_expected_lists; ii++) {
      // EXPECT_EQ(std::get<1>(test_case)[ii], out_vect[ii]);
    // }
  }
}

//-----------------------------------------------------------------------------
// Tests for Solution to Q5
//-----------------------------------------------------------------------------
TEST(CciChapter4_Q5, check_bt_false) {
  std::vector<std::vector<int>> test_cases = {
      {1, 2},
      {1, 2, 3, 4, 5, 6, 7, 8},
  };

  int last_printed = 0;
  for (auto &test_case : test_cases) {
    cci::BinaryTree test_tree;

    for (auto value : test_case) {
      test_tree.insert(value);
    }

    last_printed = INT_MIN;
    EXPECT_EQ(cci::isBst(test_tree.getRoot(), &last_printed), false);
  }
}

TEST(CciChapter4_Q5, check_bt_true) {
  std::vector<std::vector<int>> test_cases = {
      std::vector<int>{},
      {1},
      {2, 1},
      {5, 3, 8, 2, 4, 6, 9, 1}
  };

  int last_printed = 0;
  for (auto &test_case : test_cases) {
    cci::BinaryTree test_tree;

    for (auto value : test_case) {
      test_tree.insert(value);
    }

    last_printed = INT_MIN;
    EXPECT_EQ(cci::isBst(test_tree.getRoot(), &last_printed), true);
  }
}

TEST(CciChapter4_Q5, check_bst_true){
  std::vector<std::vector<int>> test_cases = {
      std::vector<int>{},
      {1, 2, 3, 4, 5, 6, 7, 8, 9, 10},
      {10, 9, 8, 7, 6, 5, 4, 3, 2, 1},
      {5, 3, 8, 2, 4, 6, 9, 1, 7},
  };
  const bool is_bst = true;

  int last_printed = 0;
  for (auto &test_case : test_cases) {
    cci::Bst test_tree;

    for (auto value : test_case) {
      test_tree.insert(value);
    }

    last_printed = INT_MIN;
    EXPECT_EQ(cci::isBst(test_tree.getRoot(), &last_printed), is_bst);
  }
}

TEST(CciChapter4_Q5, check_bst_false) {
  std::vector<std::vector<int>> test_cases = {
      {1, 2, 3, 4, 5, 6, 7, 8, 9, 10},
      {5, 3, 8, 2, 4, 6, 9, 1, 7}
  };
  const bool is_bst = false;

  int last_printed = 0;
  for (auto &test_case : test_cases) {
    cci::Bst test_tree;

    for (auto value : test_case) {
      test_tree.insert(value);
    }

    // "Break" the tree (make it non-bst tree)
    test_tree.getRoot()->key_ = 100;

    last_printed = INT_MIN;
    EXPECT_EQ(cci::isBst(test_tree.getRoot(), &last_printed), is_bst);
  }
}

//-----------------------------------------------------------------------------
// Tests for Solution to Q6
//-----------------------------------------------------------------------------
TEST(CciChapter4_Q6, successor_exists) {
  // Bst, node to find the successor for, the successor (key values)
  std::vector<std::tuple<std::vector<int>, int, int>> test_cases = {
      {{1, 2}, 1, 2},
      {{2, 1}, 1, 2},
      {{1, 2, 3, 4, 5, 6, 7, 8, 9, 10}, 9, 10},
      {{5, 3, 8, 2, 4, 6, 9, 1, 7}, 4, 5},
  };

  for (auto &test_case : test_cases) {
    cci::Bst test_tree;

    for (auto value : std::get<0>(test_case)) {
          test_tree.insert(value);
    }

    cci::BinaryTreeNode *succ_for = test_tree.getNode(std::get<1>(test_case));
    cci::BinaryTreeNode *succ = inorderSucc(succ_for);

    EXPECT_EQ(succ->key_, std::get<2>(test_case));
  }
}

TEST(CciChapter4_Q6, no_successor) {
  // Bst, node to find the successor for (there's no successor though)
  std::vector<std::tuple<std::vector<int>, int>> test_cases = {
      {{1, 2}, 2},
      {{2, 1}, 2},
      {{1, 2, 3, 4, 5, 6, 7, 8, 9, 10}, 10},
      {{5, 3, 8, 2, 4, 6, 9, 1, 7}, 9},
  };

  for (auto &test_case : test_cases) {
    cci::Bst test_tree;

    for (auto value : std::get<0>(test_case)) {
          test_tree.insert(value);
    }

    cci::BinaryTreeNode *succ_for = test_tree.getNode(std::get<1>(test_case));
    cci::BinaryTreeNode *succ = inorderSucc(succ_for);

    EXPECT_EQ(nullptr, succ);
  }
}

//-----------------------------------------------------------------------------
// Tests for Solution to Q7
//-----------------------------------------------------------------------------
TEST(CciChapter4_Q7, ancestor_exists) {
  // Bst, nodes to find common ancestor for, the common ancestor (key values)
  std::vector<std::tuple<std::vector<int>, int, int, int>> test_cases = {
      {{1, 2}, 1, 2, 1},
      {{2, 1}, 1, 2, 2},
      {{1, 2, 3, 4, 5, 6, 7, 8, 9, 10}, 9, 10, 2},
      {{1, 2, 3, 4, 5, 6, 7, 8, 9, 10}, 6, 7, 3},
      {{1, 2, 3, 4, 5, 6, 7, 8, 9, 10}, 6, 10, 1},
  };

  for (auto &test_case : test_cases) {
    cci::BinaryTree test_tree;

    for (auto value : std::get<0>(test_case)) {
          test_tree.insert(value);
    }

    cci::BinaryTreeNode *ancestor = cci::commonAncestor(
        test_tree.getRoot(), test_tree.getNode(std::get<1>(test_case)),
        test_tree.getNode(std::get<2>(test_case)));

    EXPECT_EQ(ancestor->key_, std::get<3>(test_case));
  }
}
