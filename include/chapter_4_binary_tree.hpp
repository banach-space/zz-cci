//========================================================================
//  FILE:
//      include/chapter_4_binary_tree.hpp
//
//  AUTHOR:
//      banach-space@github
//
//  DESCRIPTION:
//    Binary and binary search tree for questions in Chapter 4 in [1].
//
//    [1] "Cracking the Coding Interview", Gayle Laakmann McDowell
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
// CLASS: BinaryTreeNode (declaration)
//
// Represents a node in a binary tree. It can be a binary search tree, but
// doesn't have to. The parent_ member variable was added as some question
// assume that it's available. It's not used in questions that don't make that
// assumption.
//------------------------------------------------------------------------
struct BinaryTreeNode {
  explicit BinaryTreeNode(int key_val)
      : key_(key_val), left_(nullptr), right_(nullptr), parent_(nullptr) {}
  int key_;
  struct BinaryTreeNode *left_, *right_, *parent_;
};

//------------------------------------------------------------------------
// CLASS: BinaryTree (declaration)
//
// Represents a Binary tree. Manages all the underlying memory.
//------------------------------------------------------------------------
class BinaryTree {
public:
  explicit BinaryTree(int root_key);
  explicit BinaryTree() = default;
  explicit BinaryTree(BinaryTreeNode *root);

  BinaryTree(BinaryTree &&other) noexcept;

  BinaryTree(BinaryTree &other) = delete;
  BinaryTree operator=(BinaryTree &&) = delete;

  virtual ~BinaryTree();

  // Insert node with the key equal to the argument
  virtual void insert(int key);

  // Returns a vector of keys from this tree, in left to right order. If this
  // is a binary search tree then the return vector will contain values in
  // ascending order.
  std::vector<int> getVector();

  // Solution to Q2
  // Returns true if the tree is balanced, false otherwise
  bool isBalanced();

  BinaryTreeNode *getRoot() { return root_;};
  void createRootNode(int key);

  bool isEmpty() { return nullptr == root_;}

  void incNumofElements() {num_of_elements_++;}

  // Returns a pointer to the node that contains value key.
  virtual BinaryTreeNode *getNode(int key);

private:
  // Deletes (frees memory) for all nodes in the subtree pointed to by the
  // input argument.
  void deleteSubtree(BinaryTreeNode *node_to_delete);

  // Checks whether the tree pointed to by the argument is balanced (i.e.
  // left and right sub-trees differ in height by no more than one). Returns
  // "-1" to indicate "false" (not balanced), or subtree height (a positive
  // number) to indicate "true" (balanced). Implemented as a recursive
  // function.
  int isBalancedImpl(BinaryTreeNode *root_of_subtree);

  void getValuesLeftToRight(BinaryTreeNode *t, std::vector<int> *values);

  BinaryTreeNode *root_{};
  size_t num_of_elements_{};
};

//------------------------------------------------------------------------
// CLASS: Bst (declaration)
//
// Represents a Binary Search tree. Manages all the underlying memory.
//------------------------------------------------------------------------
class Bst : public BinaryTree {
public:
  explicit Bst(int root_key);
  explicit Bst() = default;
  explicit Bst(BinaryTreeNode *root);

  Bst(Bst &&other) noexcept;

  Bst(const Bst &other) = delete;
  Bst operator=(Bst &&) = delete;

  ~Bst() override;

  // Insert node with the key equal to the argument
  void insert(int key) override;

  // Returns a pointer to the node that contains value key
  BinaryTreeNode *getNode(int key) override;
};

// Returns the left most child of node
BinaryTreeNode *leftMostChild(BinaryTreeNode *node);

} // namespace cci

#endif
