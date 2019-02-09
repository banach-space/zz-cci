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
// Solution to Q1
//-----------------------------------------------------------------------------
// See Bst::isBalanced

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
      createBinaryTreeNodeForMinBst(array, array.begin(), array.end() - 1));
}

cci::BinaryTreeNode *
cci::createBinaryTreeNodeForMinBst(const std::vector<int> &array,
                            std::vector<int>::const_iterator start,
                            std::vector<int>::const_iterator end) {
  if (end < start) {
    return nullptr;
  }

  int dist = std::distance(start, end);
  std::vector<int>::const_iterator middle = start + dist / 2;
  BinaryTreeNode *new_node = new BinaryTreeNode(*middle);

  std::vector<int>::const_iterator new_end = middle - 1;
  new_node->left_ = createBinaryTreeNodeForMinBst(array, start, new_end);

  std::vector<int>::const_iterator new_start = middle + 1;
  new_node->right_ = createBinaryTreeNodeForMinBst(array, new_start, end);

  return new_node;
}

//-----------------------------------------------------------------------------
// Solution to Q4
//-----------------------------------------------------------------------------
// This solution creates an array of lists of key values rather than nodes.
// This makes managing the memory much much easier, yet the underlying
// algorithim is almost identical.
void cci::createLevelLinkedListImpl(BinaryTreeNode *root, arrayBstLevels *array,
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

cci::arrayBstLevels cci::createLevelLinkedList(BinaryTreeNode *root) {
  cci::arrayBstLevels array;

  createLevelLinkedListImpl(std::forward<cci::BinaryTreeNode*>(root), &array, 0u);

  return array;
}

//-----------------------------------------------------------------------------
// Solution to Q5
//-----------------------------------------------------------------------------
// This solution can't handle duplicate values in the tree properly.
bool cci::isBst(BinaryTreeNode *root, int *last_printed) {
  if (nullptr == root) {
    return true;
  }

  // Chech / recurse left
  if (!isBst(root->left_, last_printed)) {
      return false;
  }

  // Check current
  if (root->key_ <= *last_printed) {
    return false;
  }
  *last_printed = root->key_;

  // Check / recurse right
  if (!isBst(root->right_, last_printed)) {
    return false;
  }

  return true;
}

//-----------------------------------------------------------------------------
// Solution to Q6
//-----------------------------------------------------------------------------
cci::BinaryTreeNode *cci::inorderSucc(cci::BinaryTreeNode *node) {
  if (nullptr == node) {
    return nullptr;
  }

  // Found right children -> return leftmost node of right subtree
  if (nullptr != node->right_) {
    return cci::leftMostChild(node->right_);
  } else {
    BinaryTreeNode *q = node;
    BinaryTreeNode *x = q->parent_;
    // Go up until we're on left instead of rigt
    while (nullptr != x && x->left_ != q) {
      q = x;
      x = x->parent_;
    }
    return x;
  }

  return nullptr;
}
