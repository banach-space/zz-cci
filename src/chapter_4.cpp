//========================================================================
// FILE:
//  chapter_4.cpp
//
// AUTHOR:
//  banach-space@github
//
// DESCRIPTION:
//    Solutions to practice questions from Chapter 4 in [1] - implementation.
//
//    [1] "Cracking the Coding Interview", Gayle Laakmann McDowell
//
// License: Apache License 2.0
//========================================================================
#include <chapter_4.hpp>
#include <vector>

//-----------------------------------------------------------------------------
// Solution to Q2
//-----------------------------------------------------------------------------
// TODO

//-----------------------------------------------------------------------------
// Solution to Q3
//-----------------------------------------------------------------------------
cci::Bst cci::createMinBst(const std::vector<int> &array) {
  if (array.empty()) {
    return Bst();
  }

  return cci::Bst(
      createBstNodeForMinBst(array, array.begin(), array.end() - 1));
}

cci::BstNode *
cci::createBstNodeForMinBst(const std::vector<int> &array,
                            std::vector<int>::const_iterator start,
                            std::vector<int>::const_iterator end) {
  if (end < start) {
    return nullptr;
  }

  int dist = std::distance(start, end);
  std::vector<int>::const_iterator middle = start + dist / 2;
  BstNode *new_node = new BstNode(*middle);

  std::vector<int>::const_iterator new_end = middle - 1;
  new_node->left_ = createBstNodeForMinBst(array, start, new_end);

  std::vector<int>::const_iterator new_start = middle + 1;
  new_node->right_ = createBstNodeForMinBst(array, new_start, end);

  return new_node;
}
