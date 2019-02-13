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
#include <algorithm>
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

  createLevelLinkedListImpl(std::forward<BinaryTreeNode *>(root), &array, 0u);

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
  if (nullptr == root) {
    return false;
  }
  if (root == p) {
    return true;
  }

  return covers(root->left_, p) || covers(root->right_, p);
}

static BinaryTreeNode *commonAncestorHelper(BinaryTreeNode *root,
                                            BinaryTreeNode *p,
                                            BinaryTreeNode *q) {
  if (nullptr == root) {
    return nullptr;
  }
  if (root == p || root == q) {
    return root;
  }

  bool is_p_on_left = covers(root->left_, p);
  bool is_q_on_left = covers(root->left_, q);

  // If p and q are on different sides, return root.
  if (is_p_on_left != is_q_on_left) {
    return root;
  }

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

//------------------------------------------------------------------------
// Solution to Q8
//------------------------------------------------------------------------
static bool matchTree(BinaryTreeNode *node_t1, BinaryTreeNode *node_t2) {
  // If both are empty
  if (nullptr == node_t2 && nullptr == node_t1) {
    return true;
  }

  // If one, but not both are empty
  if (nullptr == node_t1 || nullptr == node_t2) {
    return false;
  }

  // If kyes don't match
  if (node_t1->key_ != node_t2->key_) {
    return false;
  }

  return (matchTree(node_t1->left_, node_t2->left_) &&
          matchTree(node_t1->right_, node_t2->right_));
}

static bool subTree(BinaryTreeNode *node_t1, BinaryTreeNode *node_t2) {
  if (nullptr == node_t1) {
    // T1 is empty and subtree still not found
    return false;
  }

  if (node_t1->key_ == node_t2->key_) {
    if (matchTree(node_t1, node_t2)) {
      return true;
    }
  }
  return (subTree(node_t1->left_, node_t2) ||
          subTree(node_t1->right_, node_t2));
}

bool cci::containsTree(BinaryTreeNode *root_t1, BinaryTreeNode *root_t2) {
  if (nullptr == root_t2) {
    return true;
  }

  return subTree(root_t1, root_t2);
}

//------------------------------------------------------------------------
// Solution to Q9
//------------------------------------------------------------------------
// Calculates the depth of the input node
static int depth(BinaryTreeNode *node) {
  if (nullptr == node) {
    return 0;
  }

  return (1 + std::max(depth(node->left_), depth(node->right_)));
}

static void findSumImpl(BinaryTreeNode *node, int sum,
                        std::vector<int> current_path, int level,
                        std::vector<std::vector<int>> *solutions) {
  if (nullptr == node) {
    return;
  }

  // Insert current node into the current path. Note that current_path is
  // passed by value and hence the new value is only visible in the current
  // call frame and the call frames created by this call.
  current_path[level] = node->key_;

  // Look for paths with a sum that ends at this node
  int temp_sum = 0;
  for (int ii = level; ii >= 0; ii--) {
    temp_sum += current_path[ii];
    if (temp_sum == sum) {
      // There's a path within the path v
      solutions->emplace_back(std::vector<int>(current_path.begin() + ii,
                                               current_path.begin() + level));
    }
  }

  // Search nodes beneath this one
  findSumImpl(node->left_, sum, current_path, level + 1, solutions);
  findSumImpl(node->right_, sum, current_path, level + 1, solutions);

  // Remove current node from path
  current_path[level] = 0;
}

std::vector<std::vector<int>> cci::findSum(BinaryTreeNode *root, int sum) {
  // The output vector
  std::vector<std::vector<int>> solutions;

  int tree_depth = depth(root);
  // path in a can be at most tree_depth logn. It will be passed by value, so
  // each recursive call will have it's own copy and will add and remove
  // nodes (keys) to it.
  std::vector<int> path(tree_depth);

  findSumImpl(root, sum, path, 0, &solutions);

  return solutions;
}
