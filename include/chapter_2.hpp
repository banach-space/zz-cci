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
// Helper functions
//------------------------------------------------------------------------
namespace cci {
template<typename T>
std::vector<T> extractAllValues(const cci::List<T> &List) {
  std::vector<T> all_vals {};

  if (List.isEmpty()) {
    return all_vals;
  }

  auto *temp = List.getHead();
  all_vals.push_back(temp->val);;
  while (nullptr != temp->next_) {
    temp = temp->next_;
    all_vals.push_back(temp->val);
  }

  return all_vals;
}

template<typename T>
std::vector<T> extractAllValues(const std::list<T> &List) {
  std::vector<T> all_vals {};

  if (List.empty()) {
    return all_vals;
  }

  for (auto it = List.begin(); it != List.end(); it++) {
    all_vals.push_back(*it);
  }

  return all_vals;
}
} // namespace cci

//------------------------------------------------------------------------
// Solution to Q1
//------------------------------------------------------------------------
// A solution for cci::List<T>
template<typename T>
void removeDuplicates(cci::List<T> *list) {
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
      it = it->next_;
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
// A Basic solution for cci::List<T> (not using iterators)
template<typename T>
typename cci::List<T>::Node* findKthElementBasic(const cci::List<T> &list, size_t k) {
  if (list.isEmpty()) {
    return nullptr;
  }

  auto *it_first = list.getHead();
  auto *it_second = list.getHead();

  for (size_t i = 0; i < k; i++) {
    it_first = it_first->next_;
  }

  while (nullptr != it_first->next_) {
    it_first = it_first->next_;
    it_second = it_second->next_;
  }

  return it_second;
}

// A solution for std::list<T> and cci::List<T> (using iterators)
template<typename ListType>
typename ListType::const_iterator findKthElement(const ListType &list, size_t k) {
  if (list.empty()) {
    return list.cend();
  }

  auto it_first = list.cbegin();
  auto it_second = list.cbegin();

  for (size_t i = 0; i < k; i++) {
    it_first++;
  }

  while (list.cend() != ++it_first) {
    it_second++;
  }

  return it_second;
}

//------------------------------------------------------------------------
// Solution to Q3
//------------------------------------------------------------------------
// Note that this implementation is not capable of removing the last node in
// the list. And in general it is not possible unless you have acces to the
// list.
template<typename T>
void deleteNode(typename cci::List<T>::Node *nodeToDelete) {
  // Check if this is the last node in the list. If that's the case do nothing.
  if (nullptr == nodeToDelete->next_) {
    return;
  }

  // Otherwise, copy the contents of nodeToDelete->next_ into nodeToDelete and
  // delete nodeToDelete->next_ instead.
  typename cci::List<T>::Node* temp = nodeToDelete->next_;
  nodeToDelete->val = temp->val;
  nodeToDelete->next_ = temp->next_;

  delete temp;
}

#endif
