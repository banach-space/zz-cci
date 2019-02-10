//========================================================================
// FILE:
//  chapter_4_binary_tree.cpp
//
// AUTHOR:
//  banach-space@github
//
// DESCRIPTION:
//    Implementation of binary and binary search tree for questions in Chapter
//    4.
//
// License: Apache License 2.0
//========================================================================
#include <chapter_4_binary_tree.hpp>

#include <algorithm>
#include <cmath>
#include <queue>
#include <cassert>

namespace cci {
//------------------------------------------------------------------------
// CLASS: BinaryTree (implementation)
//------------------------------------------------------------------------
BinaryTree::BinaryTree(int root_key) {
  root_ = new BinaryTreeNode(root_key);
  num_of_elements_++;
}

BinaryTree::BinaryTree(BinaryTreeNode *root) : root_(root) { num_of_elements_++; }

BinaryTree::BinaryTree(BinaryTree &&other) noexcept {
  root_ = other.root_;
  num_of_elements_ = other.num_of_elements_;

  other.root_ = nullptr;
  other.num_of_elements_ = 0;
}

BinaryTree::~BinaryTree() { deleteSubtree(root_); }

void BinaryTree::deleteSubtree(BinaryTreeNode *node_to_delete) {
  if (nullptr == node_to_delete) {
    return;
  }

  deleteSubtree(node_to_delete->left_);
  deleteSubtree(node_to_delete->right_);

  delete node_to_delete;
}

void BinaryTree::getValuesLeftToRight(BinaryTreeNode *t, std::vector<int> *values) {
  if (nullptr == t) {
    return;
  }

  getValuesLeftToRight(t->left_, values);
  values->push_back(t->key_);
  getValuesLeftToRight(t->right_, values);
}

std::vector<int> BinaryTree::getVector() {
  std::vector<int> key_values_left_to_right;
  key_values_left_to_right.reserve(num_of_elements_);

  getValuesLeftToRight(root_, &key_values_left_to_right);

  return key_values_left_to_right;
}

static BinaryTreeNode *getNodeImpl(BinaryTreeNode *current, int key) {
  // The case when the tree is empty
  if (nullptr == current) {
    return nullptr;
  }

  if (current->key_ == key) {
    return current;
  }

  auto find_left = getNodeImpl(current->left_, key);
  if (nullptr != find_left) {
    return find_left;
  }

  auto find_right = getNodeImpl(current->right_, key);
  if (nullptr != find_right) {
    return find_right;
  }

  return nullptr;
}

BinaryTreeNode *BinaryTree::getNode(int key) {
  return getNodeImpl(root_, key);
}

// Do iterative level order traversal of the given tree using queue. If a node
// whose left child is empty is found, make new key as left child of the node.
// Else if a node whose right child is empty is found, make new key as right
// child. Keep traversing the tree until a node whose either left or right is
// empty is found.
void BinaryTree::insert(int key) {
  BinaryTreeNode *new_node = new BinaryTreeNode(key);

  // The case when the tree is empty
  if (nullptr == root_) {
    root_ = new_node;
    return;
  }

  std::queue<struct BinaryTreeNode *> bt_node_q;
  bt_node_q.push(root_);

  // Do level order traversal until we find an empty place.
  while (!bt_node_q.empty()) {
    struct BinaryTreeNode *temp = bt_node_q.front();
    bt_node_q.pop();

    if (nullptr == temp->left_) {
      temp->left_ = new_node;
      return;
    } else {
      bt_node_q.push(temp->left_);
    }

    if (nullptr == temp->right_) {
      temp->right_ = new_node;
      return;
    } else {
      bt_node_q.push(temp->right_);
    }
  }
}

int BinaryTree::isBalancedImpl(BinaryTreeNode *subtree) {
  if (nullptr == subtree) {
    // Height is 0
    return 0;
  }

  // Check if left sub-tree is balanced
  int left_height = isBalancedImpl(subtree->left_);
  if (-1 == left_height) {
    // Not balanced
    return -1;
  }

  // Check if right sub-tree is balanced
  int right_height = isBalancedImpl(subtree->right_);
  if (-1 == right_height) {
    // Not balanced
    return -1;
  }

  // Check if current node is balanced
  int height_diff = left_height - right_height;
  if (abs(height_diff) > 1) {
    // Not balanced
    return -1;
  }

  return std::max(left_height, right_height) + 1;
}

bool BinaryTree::isBalanced() {
  return (isBalancedImpl(this->root_) != -1 ? true : false);
}

void BinaryTree::createRootNode(int key) {
  assert(nullptr == root_ && "Creating root node for a non-empty tree.");
  BinaryTreeNode *new_node = new BinaryTreeNode(key);

  root_ = new_node;
  num_of_elements_++;
}

//------------------------------------------------------------------------
// CLASS: Bst (implementation)
//------------------------------------------------------------------------
Bst::Bst(int root_key) : BinaryTree(root_key) {}

Bst::Bst(BinaryTreeNode *root) : BinaryTree(root) {}

Bst::Bst(Bst &&other) noexcept : BinaryTree(std::move(other)) { }

Bst::~Bst() { }

void Bst::insert(int key) {
  // If the tree is empty then we need new root
  if (isEmpty()) {
    createRootNode(key);
    return;
  }

  // Otherwise, create a new node and find a good place to insert it
  BinaryTreeNode *new_node = new BinaryTreeNode(key);

  // Temp iterator used for traversing the tree
  BinaryTreeNode *current = getRoot();;

  // Find the right location to insert the node
  while (true) {
    // The node can be inserted on the right sub-tree. Do so and return.
    if (key >= current->key_ && (nullptr == current->right_)) {
      new_node->parent_ = current;

      current->right_ = new_node;
      incNumofElements();

      return;
    }

    // The node can be inserted on the left sub-tree. Do so and return.
    if (key < current->key_ && (nullptr == current->left_)) {
      new_node->parent_ = current;

      current->left_ = new_node;
      incNumofElements();

      return;
    }

    // Can't insert the node yet. Update current to one of it's children and
    // re-iterate.
    current = (key >= current->key_) ? current->right_ : current->left_;
  }
}

BinaryTreeNode *Bst::getNode(int key) {
  BinaryTreeNode *root = getRoot();
  if (nullptr == root) {
    return nullptr;
  }

  if (root->key_ == key) {
    return root;
  }

  BinaryTreeNode *candidate = root;
  while (nullptr != candidate) {
    if (candidate->key_ == key) {
      return candidate;
    }

    candidate = candidate->key_ > key ? candidate->left_ : candidate->right_;
  }

  return nullptr;
}

BinaryTreeNode *leftMostChild(BinaryTreeNode *node) {
  if (nullptr == node) {
    return nullptr;
  }

  while (nullptr != node->left_) {
    node = node->left_;
  }

  return node;
}

} // namespace cci
