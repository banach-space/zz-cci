//========================================================================
//  FILE:
//      include/chapter_2.hpp
//
//  AUTHOR:
//      banach-space@github
//
//  DESCRIPTION:
//    Solutions to practice questions from Chapter 2 in [1] as well as helper
//    data structures.
//
//    Since I wanted to play with templates in Chapter 2, most of the
//    implementation is in header files.
//
//    "Cracking the Coding Interview", Gayle Laakmann McDowell
//
//  License: Apache License 2.0
//========================================================================
#ifndef _CHAPTER_2_
#define _CHAPTER_2_

#include <chapter_2_list.hpp>
#include <list>

//------------------------------------------------------------------------
// Solution to Q1
//------------------------------------------------------------------------
// cci::list<T>
template<typename T>
void removeDuplicates(cci::list<T> *list) {
  // If the list is empty then there's nothing to do
  if (list->isEmpty()) {
    return;
  }

  // A hash table of items in the list
  std::map<T, unsigned int> entries {};

  auto *it = list->getHead();
  while (nullptr != it) {
    if (1 == entries.count(it->val)) {
      it = list->erase(it);
    } else {
      entries.insert({it->val, 1u});
      it = it->next;
    }
  }
}

// std::list<T>
template<typename T>
void removeDuplicates(std::list<T> *list) {
  // If the list is empty then there's nothing to do
  if (list->empty()) {
    return;
  }

  // A hash table of items in the list
  std::map<T, unsigned int> entries {};

  for (auto it = list->begin(); it != list->end();) {
    if (1 == entries.count(*it)) {
      it = list->erase(it);
    } else {
      entries.insert({*it, 1u});
      it++;
    }
  }
}

#endif
