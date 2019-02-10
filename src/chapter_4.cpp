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

using namespace cci;

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
static BinaryTreeNode *
createBinaryTreeNodeForMinBst(std::vector<int>::const_iterator,
                              std::vector<int>::const_iterator);

Bst cci::createMinBst(const std::vector<int> &array) {
  if (array.empty()) {
    return Bst();
  }

  return Bst(createBinaryTreeNodeForMinBst(array.begin(), array.end() - 1));
}

BinaryTreeNode *
createBinaryTreeNodeForMinBst(std::vector<int>::const_iterator start,
                              std::vector<int>::const_iterator end) {
  if (end < start) {
    return nullptr;
  }

  int dist = std::distance(start, end);
  std::vector<int>::const_iterator middle = start + dist / 2;
  BinaryTreeNode *new_node = new BinaryTreeNode(*middle);

  std::vector<int>::const_iterator new_end = middle - 1;
  new_node->left_ = createBinaryTreeNodeForMinBst(start, new_end);

  std::vector<int>::const_iterator new_start = middle + 1;
  new_node->right_ = createBinaryTreeNodeForMinBst(new_start, end);

  return new_node;
}

//-----------------------------------------------------------------------------
// Solution to Q4
//-----------------------------------------------------------------------------
// This solution creates an array of lists of key values rather than nodes.
// This makes managing the memory much much easier, yet the underlying
// algorithim is almost identical.
static void createLevelLinkedListImpl(BinaryTreeNode *root,
                                      arrayBstLevels *array, unsigned level);

static void createLevelLinkedListImpl(BinaryTreeNode *root,
                                      arrayBstLevels *array, unsigned level) {
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

arrayBstLevels cci::createLevelLinkedList(BinaryTreeNode *root) {
  arrayBstLevels array;

  createLevelLinkedListImpl(std::forward<BinaryTreeNode*>(root), &array, 0u);

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

  // Check / recurse left
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
BinaryTreeNode *cci::inorderSucc(BinaryTreeNode *node) {
  if (nullptr == node) {
    return nullptr;
  }

  // Found right children -> return leftmost node of right subtree
  if (nullptr != node->right_) {
    return leftMostChild(node->right_);
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

//------------------------------------------------------------------------
// Solution to Q7
//------------------------------------------------------------------------
// Returns true if p is a descendant of root
static bool covers(BinaryTreeNode *root, BinaryTreeNode *p) {
  if (nullptr == root ) {return false;}
  if (root == p) { return true;}

  return covers(root->left_, p) || covers(root->right_, p);
}

static BinaryTreeNode *commonAncestorHelper(BinaryTreeNode *root,
                                            BinaryTreeNode *p,
                                            BinaryTreeNode *q) {
  if (nullptr == root) {return nullptr;}
  if (root == p || root == q) {return root;}

  bool is_p_on_left = covers(root->left_, p);
  bool is_q_on_left = covers(root->left_, q);

  // If p and q are on different sides, return root.
  if (is_p_on_left != is_q_on_left) { return root;}

  // Else, they are on the same side. Traverse this side.
  BinaryTreeNode *child_side = is_p_on_left ? root->left_ : root->right_;
  return commonAncestorHelper(child_side, p, q);
}

BinaryTreeNode *cci::commonAncestor(BinaryTreeNode *root, BinaryTreeNode *p,
    BinaryTreeNode *q) {
  if (!covers(root, p) || !covers(root, q)) {
    return nullptr;
  }

  return commonAncestorHelper(root, p, q);
}
