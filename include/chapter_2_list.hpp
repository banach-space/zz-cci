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

  // A non-default constructor/destructor is required because this class deals
  // with raw memory. However, this triggers the generation of the following
  // special functions, which are not required. Hence they are "delete"d here.
  List(List&) = delete;
  List(List&&) = delete;
  List operator=(List) = delete;
  List operator=(List&&) = delete;

  bool isEmpty() const { return (nullptr == head_); };
  void appendToTail(const T& newVal);
  void printAllVals();

  // A struct representing a node in the List
  struct Node {
    explicit Node(T newVal) : val(newVal), next_(nullptr) {}
    T val;
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
      swap(itr, other.iter);
    }

    ForwardIterator &operator++() // Pre-increment
    {
      assert(itr != nullptr && "Out-of-bounds iterator increment!");
      itr = itr->next_;
      return *this;
    }

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

    Type &operator*() const {
      assert(itr != nullptr && "Invalid iterator dereference!");
      return itr->val;
    }

    Type &operator->() const {
      assert(itr != nullptr && "Invalid iterator dereference!");
      return itr->val;
    }

    // One way conversion: iterator -> const_iterator
    operator ForwardIterator<const Type>() const {
      return ForwardIterator<const Type>(itr);
    }
  };

  // Marking this as "const" is a bit iffy. I should probably think of
  // something that mimics begin()/cbegin()
  Node* getHead() const {return head_; }

  // Deletes the node pointed by the argument and invalidates the corresponding
  // pointer.
  void deleteNode(Node *nodeToDelete);

  // The following methods were implemented for compability with std::list.
  // They also make the interface much cleaner (only realised after
  // having implemented everything else).
  void push_back(const T& newVal) { appendToTail(newVal);}
  Node* erase(Node *nodeToDelete);
  bool empty() const { return isEmpty(); };

  // Iterators
  using iterator = ForwardIterator<T>;
  using const_iterator = ForwardIterator<const T>;

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
void List<T>::appendToTail(const T& newVal) {
  // If the List is still empty then this is defining the head
  if (nullptr == head_) {
    auto *newNode = new Node(newVal);
    head_ = newNode;
    return;
  }

  // Otherwise, find the last node, create a new node and attach it to "next_"
  // of the last node
  Node *temp = head_;
  while (nullptr != temp->next_) {
    temp = temp->next_;
  }
  auto *newNode = new Node(newVal);
  temp->next_ = newNode;
}

template<typename T>
void List<T>::printAllVals() {
  Node *temp = head_;
  while (nullptr != temp) {
    std::cout << temp->val << std::endl;
    temp = temp->next_;
  }
}

template<typename T>
void List<T>::deleteNode(Node *nodeToDelete) {
  // If the List is empty then there's nothing to do
  if (nullptr == head_) {
    return;
  }

  if (head_ == nodeToDelete) {
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
    if (temp == nodeToDelete) {
      previous->next_ = temp->next_;
      delete temp;
      return;
    }
    previous = temp;
    temp = temp->next_;
  }
}

template<typename T>
typename List<T>::Node* List<T>::erase(Node *nodeToDelete) {
  // If the List is empty then there's nothing to do
  if (nullptr == head_) {
    return head_;
  }

  if (head_ == nodeToDelete) {
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
    if (temp == nodeToDelete) {
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
