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
//    This file is a bit bloated as I first designed and implemented my own
//    interface, and only then added methods for compability with
//    std::list. I've kept both implementation for learning purposes.
//
//    [1] "Cracking the Coding Interview", Gayle Laakmann McDowell
//
//  License: Apache License 2.0
//========================================================================
#ifndef _CHAPTER_2_LIST_
#define _CHAPTER_2_LIST_

#include <iostream>
#include <list>
#include <map>
#include <vector>

namespace cci {

//------------------------------------------------------------------------
// CLASS: List (declaration)
//
// Represents a singly linked list. Manages all the underlying memory.
// Implemented with simplicity in mind and as a coding excerise.
//------------------------------------------------------------------------
template<typename T>
class list {
public:
  explicit list() : head(nullptr) {};
  ~list();

  // A non-default constructor/destructor is required because this class deals
  // with raw memory. However, this triggers the generation of the following
  // special functions, which are not required. Hence they are "delete"d here.
  list(list&) = delete;
  list(list&&) = delete;
  list operator=(list) = delete;
  list operator=(list&&) = delete;

  bool isEmpty() const { return (nullptr == head); };
  void appendToTail(const T& newVal);
  void printAllVals();

  struct Node {
    explicit Node(T newVal) : val(newVal), next(nullptr) {}
    T val;
    Node *next;
  };

  // Marking this as "const" is a bit iffy. I should probably think of
  // something that mimics begin()/cbegin()
  Node* getHead() const {return head; }

  // Deletes the node pointed by the argument and invalidates the corresponding
  // pointer.
  void deleteNode(Node *nodeToDelete);

  // The following methods were implemented for compability with std::list.
  // They also make the interface much cleaner (only realised after
  // having implemented everything else).
  void push_back(const T& newVal) { appendToTail(newVal);}
  Node* erase(Node *nodeToDelete);

private:
  Node *head;
};

//------------------------------------------------------------------------
// CLASS: List (implementation)
//------------------------------------------------------------------------
template<typename T>
list<T>::~list() {
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
void list<T>::appendToTail(const T& newVal) {
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
void list<T>::printAllVals() {
  Node *temp = head;
  while (nullptr != temp) {
    std::cout << temp->val << std::endl;
    temp = temp->next;
  }
}

template<typename T>
std::vector<T> extractAllValues(const cci::list<T> &list) {
  std::vector<T> all_vals {};

  if (list.isEmpty()) {
    return all_vals;
  }

  auto *temp = list.getHead();
  all_vals.push_back(temp->val);;
  while (nullptr != temp->next) {
    temp = temp->next;
    all_vals.push_back(temp->val);
  }

  return all_vals;
}

template<typename T>
std::vector<T> extractAllValues(const std::list<T> &list) {
  std::vector<T> all_vals {};

  if (list.empty()) {
    return all_vals;
  }

  for (auto it = list.begin(); it != list.end(); it++) {
    all_vals.push_back(*it);
  }

  return all_vals;
}

template<typename T>
void list<T>::deleteNode(Node *nodeToDelete) {
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
typename list<T>::Node* list<T>::erase(Node *nodeToDelete) {
  // If the list is empty then there's nothing to do
  if (nullptr == head) {
    return head;
  }

  if (head == nodeToDelete) {
    Node *temp = head;
    head = head->next;
    delete temp;
    return head;
  }

  // If the list is not empty, use the "runner" technique to loop over all
  // nodes and find the one that is to be deleted.
  Node *temp = head->next;
  Node *previous = head;

  while (nullptr != temp) {
    if (temp == nodeToDelete) {
      previous->next = temp->next;
      delete temp;
      return previous->next;
    }
    previous = temp;
    temp = temp->next;
  }

  return temp;
}
}  // namespace cci

#endif
