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

namespace cci {
Bst createMinBst(const std::vector<int> &);

BstNode *createBstNodeForMinBst(const std::vector<int> &,
                                std::vector<int>::const_iterator,
                                std::vector<int>::const_iterator);

} // namespace cci

#endif
