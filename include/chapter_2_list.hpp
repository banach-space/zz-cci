//========================================================================
//  FILE:
//      include/chapter_2_List.hpp
//
//  AUTHOR:
//      banach-space@github
//
//  DESCRIPTION:
//    Implements a singly linked List, as required for solving the problems in
//    Chapter 2 in [1]. This implementation:
//      * manages all the underlying memory
//      * was designed with simplicity in mind and as a coding excerise
//      * includes an implementation of a ForwardIterator class
//    The type of the data stored in the List is a template parameter.  This
//    file contains both the declaration as well as the implementation of the
//    class.
//
//    This file is a bit bloated as I first designed and implemented my own
//    interface, and only then added methods for compability with std::list.
//    I've kept both implementations (i.e. the original one and the one
//    compatible with std::list) for learning purposes.
//
//    TODO A "real" implementation of const_iterator
//
//    [1] "Cracking the Coding Interview", Gayle Laakmann McDowell
//
//  License: Apache License 2.0
//========================================================================
#ifndef _CHAPTER_2_LIST_
#define _CHAPTER_2_LIST_

#include <cassert>
#include <iostream>
#include <iterator>
#include <map>
#include <vector>

namespace cci {

//------------------------------------------------------------------------
// CLASS: List (declaration)
//
// Represents a singly linked List. Manages all the underlying memory.
// Implemented with simplicity in mind and as a coding excerise.
//------------------------------------------------------------------------
template<typename T>
class List {
public:
  explicit List() : head_(nullptr) {};
  ~List();
  List(List&& other) {
    head_ = other.head_;
    other.head_ = nullptr;
  };

  // A non-default constructor/destructor is required because this class deals
  // with raw memory. However, this triggers the generation of the following
  // special functions, which are not required. Hence they are "delete"d here.
  List(List&) = delete;
  List operator=(List) = delete;
  List operator=(List&&) = delete;

  bool isEmpty() const { return (nullptr == head_); };
  // Marks the list as empty. Can be used when the underlying nodes have been
  // attached/linked to a different list.
  void markAsEmpty() { head_ = nullptr; };
  void appendToTail(const T& new_val);
  void printAllVals();

  // A struct representing a node in the List
  struct Node {
    explicit Node(T new_val) : val_(new_val), next_(nullptr) {}
    T val_;
    Node *next_;
  };

  // The implementation of the iterator class. You can't just forward declare
  // it here (which would make the code much cleaner) because of the way
  // "const_iterator" is hacked, i.e. it's a dependent template and hence
  // SFINAE doesn't apply. Moving this definition outside of this class will
  // make the compiler complain with: 
  //    implicit instantiation of undefined template 'class'
  // A very good explanation of this issue is here:
  //    https://stackoverflow.com/questions/14626033/implicit-instantiation-of-undefined-template-class?rq=1
  template <class Type, class UnqualifiedType = std::remove_cv_t<Type>>
  class ForwardIterator
      : public std::iterator<std::forward_iterator_tag, UnqualifiedType,
                             std::ptrdiff_t, Type *, Type &> {
    using Node = typename List<UnqualifiedType>::Node;
    Node *itr;

  public:
    explicit ForwardIterator(Node *nd) : itr(nd) {}
    ForwardIterator() // Default construct gives end.
        : itr(nullptr) {}

    void swap(ForwardIterator &other) noexcept {
      using std::swap;
      swap(itr, other.itr);
    }

    void updateNode(ForwardIterator &other) noexcept {
      itr->val_ = other.itr->val_;
      itr->next_ = other.itr->next_;
    }

    ForwardIterator &operator++() // Pre-increment
    {
      assert(itr != nullptr && "Out-of-bounds iterator increment!");
      itr = itr->next_;
      return *this;
    }

    Node* get() { return itr;}

    const ForwardIterator operator++(int) // Post-increment
    {
      assert(itr != nullptr && "Out-of-bounds iterator increment!");
      ForwardIterator tmp(*this);
      itr = itr->next_;
      return tmp;
    }

    // two-way comparison: v.begin() == v.cbegin() and vice versa
    template <class OtherType>
    bool operator==(const ForwardIterator<OtherType> &rhs) const {
      return itr == rhs.itr;
    }

    template <class OtherType>
    bool operator!=(const ForwardIterator<OtherType> &rhs) const {
      return itr != rhs.itr;
    }

    template <class OtherType>
    bool operator<(const ForwardIterator<OtherType> &rhs) const {
      return itr < rhs.itr;
    }

    Type &operator*() const {
      assert(itr != nullptr && "Inval_id iterator dereference!");
      return itr->val_;
    }

    Type &operator->() const {
      assert(itr != nullptr && "Inval_id iterator dereference!");
      return itr->val_;
    }

    // One way conversion: iterator -> const_iterator
    operator ForwardIterator<const Type>() const {
      return ForwardIterator<const Type>(itr);
    }
  };

  // Marking this as "const" is a bit iffy. I should probably think of
  // something that mimics begin()/cbegin()
  Node* getHead() const {return head_; }

  // Deletes the node pointed by the argument and inval_idates the corresponding
  // pointer.
  void deleteNode(Node *node_to_delete);

  // The following methods were implemented for compability with std::list.
  // They also make the interface much cleaner (only realised after
  // having implemented everything else).
  void push_back(const T& new_val) { appendToTail(new_val);}
  Node* erase(Node *node_to_delete);
  bool empty() const { return isEmpty(); };

  // Iterators
  using iterator = ForwardIterator<T>;
  using const_iterator = ForwardIterator<const T>;

  // Added as solution to Q3. Like the implementation from std::list, returns
  // an iterator pointing to the element after the deleted element. Takes an
  // iterator pointing to the element to be removed.
  iterator erase(iterator node_to_delete);

  const_iterator cbegin() const noexcept {
    return const_iterator(this->head_);
  }

  const_iterator cend() const noexcept { return const_iterator(nullptr); }

  iterator begin() noexcept {
    return iterator(this->head_);
  }

  iterator end() noexcept {
    return iterator(nullptr);
  }

private:
  Node *head_;
};

//------------------------------------------------------------------------
// CLASS: List (implementation)
//------------------------------------------------------------------------
template<typename T>
List<T>::~List() {
  // The List is already empty - nothing to do
  if (nullptr == head_) {
    return;
  }

  // If the List is not empty, use the "runner" technique to loop over all
  // nodes.
  Node *temp = head_->next_;
  Node *previous = head_;

  while (nullptr != temp) {
    delete previous;
    previous = temp;
    temp = temp->next_;
  }

  // The above technique doesn't capture/delete the final node. Do it now.
  delete previous;
}

template<typename T>
void List<T>::appendToTail(const T& new_val) {
  // If the List is still empty then this is defining the head
  if (nullptr == head_) {
    auto *new_node = new Node(new_val);
    head_ = new_node;
    return;
  }

  // Otherwise, find the last node, create a new node and attach it to "next_"
  // of the last node
  Node *temp = head_;
  while (nullptr != temp->next_) {
    temp = temp->next_;
  }
  auto *new_node = new Node(new_val);
  temp->next_ = new_node;
}

template<typename T>
void List<T>::printAllVals() {
  Node *temp = head_;
  while (nullptr != temp) {
    std::cout << temp->val_ << std::endl;
    temp = temp->next_;
  }
}

template<typename T>
void List<T>::deleteNode(Node *node_to_delete) {
  // If the List is empty then there's nothing to do
  if (nullptr == head_) {
    return;
  }

  if (head_ == node_to_delete) {
    Node *temp = head_;
    head_ = head_->next_;
    delete temp;
    return;
  }

  // If the List is not empty, use the "runner" technique to loop over all
  // nodes and find the one that is to be deleted.
  Node *temp = head_->next_;
  Node *previous = head_;

  while (nullptr != temp) {
    if (temp == node_to_delete) {
      previous->next_ = temp->next_;
      delete temp;
      return;
    }
    previous = temp;
    temp = temp->next_;
  }
}

template<typename T>
typename List<T>::iterator List<T>::erase(typename List<T>::iterator node_to_delete) {
  // Check if this is the last node in the list. If that's the case do nothing.
  typename List<T>::iterator next = node_to_delete;
  if (node_to_delete == end() || ++next == end()) {
    return end();
  }

  // Otherwise, copy the contents of node_to_delete->next_ into node_to_delete and
  // delete node_to_delete->next_ instead.
  node_to_delete.updateNode(next);
  delete next.get();

  return node_to_delete;
}

template<typename T>
typename List<T>::Node* List<T>::erase(Node *node_to_delete) {
  // If the List is empty then there's nothing to do
  if (nullptr == head_) {
    return head_;
  }

  if (head_ == node_to_delete) {
    Node *temp = head_;
    head_ = head_->next_;
    delete temp;
    return head_;
  }

  // If the List is not empty, use the "runner" technique to loop over all
  // nodes and find the one that is to be deleted.
  Node *temp = head_->next_;
  Node *previous = head_;

  while (nullptr != temp) {
    if (temp == node_to_delete) {
      previous->next_ = temp->next_;
      delete temp;
      return previous->next_;
    }
    previous = temp;
    temp = temp->next_;
  }

  return temp;
}

}  // namespace cci

#endif
