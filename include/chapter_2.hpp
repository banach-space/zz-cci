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
#include <algorithm>

//------------------------------------------------------------------------
// Helper functions
//------------------------------------------------------------------------
namespace cci {
template<typename ListType, typename T>
std::vector<T> getVector(const ListType &List) {
  std::vector<T> all_vals {};

  if (List.empty()) {
    return all_vals;
  }

  for (auto &item : List) {
    all_vals.push_back(item);
  }

  return all_vals;
}
} // namespace cci

//------------------------------------------------------------------------
// Solution to Q1
//------------------------------------------------------------------------
template<typename ListType, typename T>
void removeDuplicates(ListType *list) {
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
  if (list.empty()) {
    return nullptr;
  }

  auto *it_first = list.begin().get();
  auto *it_second = it_first;

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
void deleteNode(typename cci::List<T>::Node *node_to_delete) {
  // Check if this is the last node in the list. If that's the case do nothing.
  if (nullptr == node_to_delete->next_) {
    return;
  }

  // Otherwise, copy the contents of node_to_delete->next_ into node_to_delete and
  // delete node_to_delete->next_ instead.
  typename cci::List<T>::Node* temp = node_to_delete->next_;
  node_to_delete->val_ = temp->val_;
  node_to_delete->next_ = temp->next_;

  delete temp;
}

//------------------------------------------------------------------------
// Solution to Q4
//------------------------------------------------------------------------
template<typename ListType, typename ElemType>
void partition(ListType &input_list, ElemType partition_point) {
  auto comp = [&](ElemType val) { return val <= partition_point;};
  auto bound = std::partition(input_list.begin(), input_list.end(), comp);
  (void)bound;
}

//------------------------------------------------------------------------
// Solution to Q5
//------------------------------------------------------------------------
// Most trivial solution - the digits are stored in reverse order
template<typename ListType, typename ElemType>
ListType sumNumbersAsAList(ListType &input_list1, ListType &input_list2) {
  ListType out_list {};
  ElemType carry {};

  constexpr ElemType kTen{10};

  // Make sure that the number of elements in each in list is identical (may
  // need to pad with 0s)
  if (input_list1.size() > input_list2.size()) {
    size_t size_diff =  input_list1.size() - input_list2.size();

    for (auto ii = 0; ii < size_diff; ii++) {
      input_list2.push_back(0);
    }
  } else if (input_list1.size() > input_list2.size()) {
    size_t size_diff =  input_list2.size() - input_list1.size();

    for (auto ii = 0; ii < size_diff; ii++) {
      input_list1.push_back(0);
    }
  }

  // Sum the elements
  for (auto it1 = input_list1.begin(), it2 = input_list2.begin();
      it1 != input_list1.end() && it2 != input_list2.end();
      ++it1, ++it2) {
    ElemType value {};
    value = *it1 + *it2 + carry;

    carry = value >= kTen ? 1 : 0;
    value = value % kTen;

    out_list.push_back(value);
  }

  if (1 == carry) {
    out_list.push_back(carry);
  }

  return out_list;
}

#endif
