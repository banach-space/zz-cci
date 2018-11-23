//========================================================================
//  FILE:
//      include/chapter_2_list.hpp
//
//  AUTHOR:
//      banach-space@github
//
//  DESCRIPTION:
//    Implements a singly linked list, as required for solving the problems in
//    Chapter 2 in [1]. This implementation manages all the underlying memory.
//    and was designed with simplicity in mind and as a coding excerise. The
//    underlying data stored in the list is a template parameter. This file
//    contains both the declaration as well as the implementation of the
//    class.
//
//    [1] "Cracking the Coding Interview", Gayle Laakmann McDowell
//
//  License: Apache License 2.0
//========================================================================
#ifndef _CHAPTER_2_LIST_
#define _CHAPTER_2_LIST_

#include <iostream>
#include <map>
#include <vector>

namespace Cci {

//------------------------------------------------------------------------
// CLASS: List (declaration)
//
// Represents a singly linked list. Manages all the underlying memory.
// Implemented with simplicity in mind and as a coding excerise.
//------------------------------------------------------------------------
template<typename T>
class List {
public:
  explicit List() : head(nullptr) {};
  ~List();

  // A non-default constructor/destructor is required because this class deals
  // with raw memory. However, this triggers the generation of the following
  // special functions, which are not required. Hence they are "delete"d here.
  List(List&) = delete;
  List(List&&) = delete;
  List operator=(List) = delete;
  List operator=(List&&) = delete;

  bool isEmpty() { return (nullptr == head); };
  std::vector<T> getAllValues();
  void appendToTail(T newVal);
  void printAllVals();
  // Solution to Q1
  void removeDuplicates();

  struct Node {
    explicit Node(T newVal) : val(newVal), next(nullptr) {}
    T val;
    Node *next;
  };

  Node* getHead() {return head; }
  void deleteNode(Node *nodeToDelete);

private:
  Node *head;
};

//------------------------------------------------------------------------
// CLASS: List (implementation)
//------------------------------------------------------------------------
template<typename T>
List<T>::~List() {
  // The list is already empty - nothing to do
  if (nullptr == head) {
    return;
  }

  // If the list is not empty, use the "runner" technique to loop over all
  // nodes.
  Node *temp = head->next;
  Node *previous = head;

  while (nullptr != temp) {
    delete previous;
    previous = temp;
    temp = temp->next;
  }

  // The above technique doesn't capture/delete the final node. Do it now.
  delete previous;
}

template<typename T>
std::vector<T> List<T>::getAllValues() {
  std::vector<T> all_vals {};

  if (nullptr == head) {
    return all_vals;
  }

  all_vals.push_back(head->val);
  Node *temp = head;
  while (nullptr != temp->next) {
    temp = temp->next;
    all_vals.push_back(temp->val);
  }

  return all_vals;
}

template<typename T>
void List<T>::appendToTail(T newVal) {
  // If the list is still empty then this is defining the head
  if (nullptr == head) {
    auto *newNode = new Node(newVal);
    head = newNode;
    return;
  }

  // Otherwise, find the last node, create a new node and attach it to "next"
  // of the last node
  Node *temp = head;
  while (nullptr != temp->next) {
    temp = temp->next;
  }
  auto *newNode = new Node(newVal);
  temp->next = newNode;
}

template<typename T>
void List<T>::printAllVals() {
  Node *temp = head;
  while (nullptr != temp) {
    std::cout << temp->val << std::endl;
    temp = temp->next;
  }
}

template<typename T>
void List<T>::deleteNode(Node *nodeToDelete) {
  // If the list is empty then there's nothing to do
  if (nullptr == head) {
    return;
  }

  if (head == nodeToDelete) {
    Node *temp = head;
    head = head->next;
    delete temp;
    return;
  }

  // If the list is not empty, use the "runner" technique to loop over all
  // nodes and find the one that is to be deleted.
  Node *temp = head->next;
  Node *previous = head;

  while (nullptr != temp) {
    if (temp == nodeToDelete) {
      previous->next = temp->next;
      delete temp;
      return;
    }
    previous = temp;
    temp = temp->next;
  }
}

template<typename T>
  void List<T>::removeDuplicates() {
    // If the list is empty then there's nothing to do
    if (nullptr == head) {
      return;
    }

    // A hash table of items in the list
    std::map<T, unsigned int> entries {};

    Node *temp = head->next;
    Node *previous = head;

    entries.insert({head->val, 1u});

    while (nullptr != temp) {
      if (1 == entries.count(temp->val)) {
        deleteNode(temp);
        temp = previous->next;
      } else {
        entries.insert({temp->val, 1u});
        previous = temp;
        temp = temp->next;
      }
    }
  }
}  // namespace Cci


#endif
