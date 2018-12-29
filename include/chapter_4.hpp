//========================================================================
//  FILE:
//      include/chapter_4.hpp
//
//  AUTHOR:
//      banach-space@github
//
//  DESCRIPTION:
//    Solutions to practice questions from Chapter 4 in [1] as well as helper
//    data structures.
//
//    "Cracking the Coding Interview", Gayle Laakmann McDowell
//
//  License: Apache License 2.0
//========================================================================
#ifndef _CHAPTER_4_
#define _CHAPTER_4_

#include <vector>

//------------------------------------------------------------------------
// Helper data structures
//------------------------------------------------------------------------
namespace cci {

struct BstNode 
{ 
    explicit BstNode(int key_val) : key_(key_val), left_(nullptr), right_(nullptr) {}
    int key_; 
    struct BstNode *left_, *right_; 
}; 
   
class Bst {
  public:
  explicit Bst(int root_key) {
    root_ = new BstNode(root_key);
  }
  explicit Bst() = default;

  ~Bst() {
    deleteSubtree(root_);
  }

  void insert(int key) {
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

  // Returns a vector of keys from this tree, sorted in ascending order
  std::vector<int> getVector() {
    std::vector<int> key_values_in_order;
    key_values_in_order.reserve(num_of_elements_);

    getValuesInOrder(root_, &key_values_in_order);

    return key_values_in_order;
  }

  private:
    // Deletes (frees memory) for all nodes in the subtree pointed to by the
    // input argument.
    void deleteSubtree(BstNode* node_to_delete)
    {
      if (nullptr == node_to_delete) {return;}

      deleteSubtree(node_to_delete->left_);
      deleteSubtree(node_to_delete->right_);

      delete node_to_delete;
    }

    void getValuesInOrder(BstNode* t, std::vector<int> *values)
    {
      if (nullptr == t) { return;}

      getValuesInOrder(t->left_, values);
      values->push_back(t->key_);
      getValuesInOrder(t->right_, values);
    }

    BstNode *root_ {};
    size_t num_of_elements_ {};
};

} // namespace cci

#endif
