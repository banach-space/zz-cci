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
#include <list>
#include <vector>

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

//------------------------------------------------------------------------
// Solution to Q8
//
//  Given 2 binary treens, decide whether T2 is a subtree of T1
//------------------------------------------------------------------------
bool containsTree(BinaryTreeNode *root_t1, BinaryTreeNode *root_t2);

//------------------------------------------------------------------------
// Solution to Q9
//
//  Find all paths int the input tree which sum to a given value. Return the
//  solution as a vector of solutions where each solution is represented as
//  a vector of nodes (more precisely, a vector nodes' keys).
//------------------------------------------------------------------------
std::vector<std::vector<int>> findSum(BinaryTreeNode *root, int sum);
} // namespace cci

#endif
