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

#include <chapter_4_Bst.hpp>
#include <vector>
#include <list>

namespace cci {
//------------------------------------------------------------------------
// Solution to Q3
//------------------------------------------------------------------------
Bst createMinBst(const std::vector<int> &);

BstNode *createBstNodeForMinBst(const std::vector<int> &,
                                std::vector<int>::const_iterator,
                                std::vector<int>::const_iterator);

//------------------------------------------------------------------------
// Solution to Q4
//------------------------------------------------------------------------
using arrayBstLevels = std::vector<std::list<int>>;
arrayBstLevels createLevelLinkedList(cci::BstNode *root);

void createLevelLinkedListImpl(BstNode *root, arrayBstLevels *array,
                               unsigned level);

//------------------------------------------------------------------------
// Solution to Q5
//------------------------------------------------------------------------
bool checkBst(BstNode *root, int *last_printed);

//------------------------------------------------------------------------
// Solution to Q6
//------------------------------------------------------------------------
BstNode *inorderSucc(BstNode *node);
} // namespace cci


#endif
