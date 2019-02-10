//========================================================================
//  FILE:
//      include/chapter_4.hpp
//
//  AUTHOR:
//      banach-space@github
//
//  DESCRIPTION:
//    Solutions to practice questions from Chapter 4 in [1] - declarations.
//
//    "Cracking the Coding Interview", Gayle Laakmann McDowell
//
//  License: Apache License 2.0
//========================================================================
#ifndef _CHAPTER_4_
#define _CHAPTER_4_

#include <chapter_4_binary_tree.hpp>
#include <vector>
#include <list>

namespace cci {
//------------------------------------------------------------------------
// Solution to Q3
//------------------------------------------------------------------------
Bst createMinBst(const std::vector<int> &);

//------------------------------------------------------------------------
// Solution to Q4
//------------------------------------------------------------------------
using arrayBstLevels = std::vector<std::list<int>>;
arrayBstLevels createLevelLinkedList(BinaryTreeNode *root);

//------------------------------------------------------------------------
// Solution to Q5
//------------------------------------------------------------------------
bool isBst(BinaryTreeNode *root, int *last_printed);

//------------------------------------------------------------------------
// Solution to Q6
//
// Given a node in a binary search tree (i.e. it is assumed that the input node
// is a binary search tree node), find and return it's successor (or nullptr if
// there's no successor in the tree).
//------------------------------------------------------------------------
BinaryTreeNode *inorderSucc(BinaryTreeNode *node);

//------------------------------------------------------------------------
// Solution to Q7
//
// Given two nodes in a binary tree, return their first common ancestor (or
// null if there's no such).
//------------------------------------------------------------------------
BinaryTreeNode *commonAncestor(BinaryTreeNode *root, BinaryTreeNode *p,
    BinaryTreeNode *q);
} // namespace cci


#endif
