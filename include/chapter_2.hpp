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
// A solution for cci::list<T>
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

// A solution for std::list<T>
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

//------------------------------------------------------------------------
// Solution to Q2
//------------------------------------------------------------------------
// A solution for cci::list<T>
template<typename T>
typename cci::list<T>::Node* findKthElement(const cci::list<T> &list, size_t k) {
  if (list.isEmpty()) {
    return nullptr;
  }

  auto *it_first = list.getHead();
  auto *it_second = list.getHead();

  for (size_t i = 0; i < k; i++) {
    it_first = it_first->next;
  }

  while (nullptr != it_first->next) {
    it_first = it_first->next;
    it_second = it_second->next;
  }

  return it_second;
}

// A solution for std::list<T>
template<typename T>
typename std::list<T>::const_iterator findKthElement(const std::list<T> &list, size_t k) {
  if (list.empty()) {
    return list.end();
  }

  auto it_first = list.begin();
  auto it_second = list.begin();

  for (size_t i = 0; i < k; i++) {
    it_first++;
  }

  while (list.end() != ++it_first) {
    it_second++;
  }

  return it_second;
}

#endif
