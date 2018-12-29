//========================================================================
// FILE:
//  chapter_4_bst.cpp
//
// AUTHOR:
//  banach-space@github
//
// DESCRIPTION:
//    Implementations for the Bst class
//
// License: Apache License 2.0
//========================================================================
#include <chapter_4_Bst.hpp>
#include <cmath>
#include <algorithm>

namespace cci {
//------------------------------------------------------------------------
// CLASS: Bst (implementation)
//------------------------------------------------------------------------
void Bst::deleteSubtree(BstNode *node_to_delete) {
  if (nullptr == node_to_delete) {
    return;
  }

  deleteSubtree(node_to_delete->left_);
  deleteSubtree(node_to_delete->right_);

  delete node_to_delete;
}

void Bst::getValuesInOrder(BstNode *t, std::vector<int> *values) {
  if (nullptr == t) {
    return;
  }

  getValuesInOrder(t->left_, values);
  values->push_back(t->key_);
  getValuesInOrder(t->right_, values);
}

std::vector<int> Bst::getVector() {
  std::vector<int> key_values_in_order;
  key_values_in_order.reserve(num_of_elements_);

  getValuesInOrder(root_, &key_values_in_order);

  return key_values_in_order;
}

void Bst::insert(int key) {
  BstNode *new_node = new BstNode(key);

  // If there's no root then just create one
  if (nullptr == root_) {
    root_ = new_node;
    num_of_elements_++;
    return;
  }

  // Temp iterator used for traversing the tree
  BstNode *current = root_;

  // Find the right location to insert the node
  while (true) {
    // The node can be inserted on the right sub-tree. Do so and return.
    if (key >= current->key_ && (nullptr == current->right_)) {
      current->right_ = new_node;
      num_of_elements_++;
      return;
    }

    // The node can be inserted on the left sub-tree. Do so and return.
    if (key < current->key_ && (nullptr == current->left_)) {
      current->left_ = new_node;
      num_of_elements_++;
      return;
    }

    // Can't insert the node yet. Update current to one of it's children and
    // re-iterate.
    current = (key >= current->key_) ? current->right_ : current->left_;
  }
}

int Bst::isBalancedImpl(BstNode* subtree) {
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

bool Bst::isBalanced() {
  return (isBalancedImpl(this->root_) != -1 ? true : false);
}

}  // namespace cci
