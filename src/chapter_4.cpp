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

//-----------------------------------------------------------------------------
// Solution to Q4
//-----------------------------------------------------------------------------
// This solution creates an array of lists of key values rather than nodes.
// This makes managing the memory much much easier, yet the underlying
// algorithim is almost identical.
void cci::createLevelLinkedListImpl(BstNode *root, arrayBstLevels *array,
                                    unsigned level) {
  if (nullptr == root) {
    // Base case
    return;
  }

  if (array->size() == level) {
    // Level not contained in list - need to create a new list
    array->emplace_back();
  }

  auto *levelList = &array->at(level);

  levelList->emplace_back(root->key_);
  createLevelLinkedListImpl(root->left_, array, level + 1u);
  createLevelLinkedListImpl(root->right_, array, level + 1u);
}

cci::arrayBstLevels cci::createLevelLinkedList(BstNode *root) {
  cci::arrayBstLevels array;

  createLevelLinkedListImpl(std::forward<cci::BstNode*>(root), &array, 0u);

  return array;
}

//-----------------------------------------------------------------------------
// Solution to Q5
//-----------------------------------------------------------------------------
// This solution can't handle duplicate values in the tree properly.
bool cci::checkBst(BstNode *root, int *last_printed) {
  if (nullptr == root) {
    return true;
  }

  // Chech / recurse left
  if (!checkBst(root->left_, last_printed)) {
      return false;
  }

  // Check current
  if (root->key_ <= *last_printed) {
    return false;
  }
  *last_printed = root->key_;

  // Check / recurse right
  if (!checkBst(root->right_, last_printed)) {
    return false;
  }

  return true;
}
