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
#ifndef _CHAPTER_4_BST_
#define _CHAPTER_4_BST_

#include <vector>

//------------------------------------------------------------------------
// Helper data structures
//------------------------------------------------------------------------
namespace cci {

//------------------------------------------------------------------------
// CLASS: BstNode (declaration)
//
// Represents a node in a binary search tree
//------------------------------------------------------------------------
struct BstNode {
  explicit BstNode(int key_val)
      : key_(key_val), left_(nullptr), right_(nullptr), parent_(nullptr) {}
  int key_;
  struct BstNode *left_, *right_, *parent_;
};

//------------------------------------------------------------------------
// CLASS: Bst (declaration)
//
// Represents a Binary Search tree. Manages all the underlying memory.
//------------------------------------------------------------------------
class Bst {
public:
  explicit Bst(int root_key) {
    root_ = new BstNode(root_key);
    num_of_elements_++;
  }
  explicit Bst() = default;
  explicit Bst(BstNode *root) : root_(root) { num_of_elements_++; }

  Bst(Bst &&other) {
    root_ = other.root_;
    num_of_elements_ = other.num_of_elements_;

    other.root_ = nullptr;
    other.num_of_elements_ = 0;
  }

  Bst(Bst &other) = delete;
  Bst operator=(Bst &&) = delete;

  ~Bst() { deleteSubtree(root_); }

  // Insert node with the key equal to the argument
  void insert(int key);

  // Returns a vector of keys from this tree, sorted in ascending order
  std::vector<int> getVector();

  // Solution to Q2
  // Returns true if the tree is balanced, false otherwise
  bool isBalanced();

  BstNode *getRoot() { return root_;};

  // Returns a pointer to the node that contains value key
  BstNode *getNode(int key);

private:
  // Deletes (frees memory) for all nodes in the subtree pointed to by the
  // input argument.
  void deleteSubtree(BstNode *node_to_delete);
  void getValuesInOrder(BstNode *t, std::vector<int> *values);

  // Checks whether the tree pointed to by the argument is balanced (i.e.
  // left and right sub-trees differ in height by no more than one). Returns
  // "-1" to indicate "false" (not balanced), or subtree height (a positive
  // number) to indicate "true" (balanced). Implemented as a recursive
  // function.
  int isBalancedImpl(BstNode *root_of_subtree);

  BstNode *root_{};
  size_t num_of_elements_{};
};

// Returns the left most child of node
BstNode *leftMostChild(BstNode *node);

} // namespace cci

#endif
