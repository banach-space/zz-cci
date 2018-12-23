//========================================================================
//  FILE:
//      include/chapter_2_List.hpp
//
//  AUTHOR:
//      banach-space@github
//
//  DESCRIPTION:
//    Implements a doubly linked List, as required for solving the problems in
//    Chapter 2 in [1]. This implementation:
//      * manages all the underlying memory
//      * includes an implementation of a Iterator class
//      * implements an API that mimics std::list
//      * uses a sentinel to aid dealing with the beginning and the end of the
//        list (similar to how std::list is implemented in libstdc++.
//    The type of the data stored in the List is a template parameter.  This
//    file contains both the declaration as well as the implementation of the
//    class.
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
  explicit List() {
    head_sentinel_ = new Node({});
    head_sentinel_->next_ = head_sentinel_;
    head_sentinel_->prev_ = head_sentinel_;
  };
  ~List();
  List(List&& other) {
    head_sentinel_ = other.head_sentinel_;
    other.head_sentinel_ = nullptr;
  };

  List(List& other) {
    head_sentinel_ = new Node({});
    head_sentinel_->next_ = head_sentinel_;
    head_sentinel_->prev_ = head_sentinel_;

    for (auto item : other) {
      this->push_back(item);
    }
  };

  // A non-default constructor/destructor is required because this class deals
  // with raw memory. However, this triggers the generation of the following
  // special functions, which are not required. Hence they are "delete"d here.
  List operator=(List) = delete;
  List operator=(List&&) = delete;

  // A struct representing a node in the List
  struct Node {
    explicit Node(T new_val) : val_(new_val), next_(nullptr), prev_(nullptr) {}
    T val_;
    Node *next_;
    Node *prev_;
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
  class Iterator
      : public std::iterator<std::bidirectional_iterator_tag,
                             UnqualifiedType,
                             std::ptrdiff_t,
                             Type *,
                             Type &> {
    using Node = typename List<UnqualifiedType>::Node;
    Node *itr;

  public:
    explicit Iterator(Node *nd) : itr(nd) {}
    Iterator() // Default construct gives end.
        : itr(nullptr) {}

    void swap(Iterator &other) noexcept {
      using std::swap;
      swap(itr, other.itr);
    }

    void updateNode(Iterator &other) noexcept {
      itr->val_ = other.itr->val_;
      itr->next_ = other.itr->next_;
      other.itr->next_->prev_ = itr;
    }

    Node* get() { return itr;}

    Iterator &operator++() // Pre-increment
    {
      assert(itr != nullptr && "Out-of-bounds iterator increment!");
      itr = itr->next_;
      return *this;
    }

    const Iterator operator++(int) // Post-increment
    {
      assert(itr != nullptr && "Out-of-bounds iterator increment!");
      Iterator tmp(*this);
      itr = itr->next_;
      return tmp;
    }

    Iterator &operator--() // Pre-increment
    {
      assert(itr != nullptr && "Out-of-bounds iterator decrement!");
      itr = itr->prev_;
      return *this;
    }

    const Iterator operator--(int) // Post-increment
    {
      assert(itr != nullptr && "Out-of-bounds iterator decrement!");
      Iterator tmp(*this);
      itr = itr->prev_;
      return tmp;
    }

    // two-way comparison: v.begin() == v.cbegin() and vice versa
    template <class OtherType>
    bool operator==(const Iterator<OtherType> &rhs) const {
      return itr == rhs.itr;
    }

    template <class OtherType>
    bool operator!=(const Iterator<OtherType> &rhs) const {
      return itr != rhs.itr;
    }

    template <class OtherType>
    bool operator<(const Iterator<OtherType> &rhs) const {
      return itr < rhs.itr;
    }

    template <class OtherType>
    bool operator>(const Iterator<OtherType> &rhs) const {
      return itr > rhs.itr;
    }

    Type &operator*() const {
      assert(itr != nullptr && "Invalid iterator dereference!");
      return itr->val_;
    }

    Type &operator->() const {
      assert(itr != nullptr && "Invalid iterator dereference!");
      return itr->val_;
    }

    // One way conversion: iterator -> const_iterator
    operator Iterator<const Type>() const {
      return Iterator<const Type>(itr);
    }
  };

  // The following methods were implemented for compability with std::list.
  // They also make the interface much cleaner (only realised after
  // having implemented everything else).
  void push_back(const T& new_val);
  void push_front(const T& new_val);
  Node* erase(Node *node_to_delete);
  bool empty() const { return (head_sentinel_->next_ == head_sentinel_); };
  size_t size() const { return std::distance(cbegin(), cend());}
  void reverse();

  // Iterators
  using iterator = Iterator<T>;
  using const_iterator = Iterator<const T>;

  // Added as solution to Q3. Like the implementation from std::list, returns
  // an iterator pointing to the element after the deleted element. Takes an
  // iterator pointing to the element to be removed.
  iterator erase(iterator node_to_delete);

  const_iterator cbegin() const noexcept {
    return const_iterator(this->head_sentinel_->next_);
  }

  const_iterator cend() const noexcept { return const_iterator(head_sentinel_); }

  iterator begin()  noexcept {
    return iterator(this->head_sentinel_->next_);
  }

  const_iterator begin() const noexcept {
    return iterator(this->head_sentinel_->next_);
  }

  const_iterator end() const noexcept {
    return iterator(this->head_sentinel_);
  }

  iterator end() noexcept {
    return iterator(this->head_sentinel_);
  }

private:
  Node *head_sentinel_;
};

//------------------------------------------------------------------------
// CLASS: List (implementation)
//------------------------------------------------------------------------
template<typename T>
List<T>::~List() {
  // The List is already empty - nothing to do
  if (head_sentinel_->next_ == head_sentinel_) {
    return;
  }

  // If the List is not empty, use the "runner" technique to loop over all
  // nodes.
  Node *temp = head_sentinel_->next_->next_;
  Node *previous = head_sentinel_->next_;

  while (temp == head_sentinel_) {
    delete previous;
    previous = temp;
    temp = temp->next_;
  }

  // The above technique doesn't capture/delete the final node. Do it now.
  delete previous;
}

template<typename T>
void List<T>::push_back(const T& new_val) {
  // If the List is still empty then this is defining the head
  if ( head_sentinel_->next_ == head_sentinel_) {
    auto *new_node = new Node(new_val);
    new_node->prev_ = head_sentinel_;
    new_node->next_ = head_sentinel_;

    head_sentinel_->next_ = new_node;
    head_sentinel_->prev_ = new_node;
    return;
  }

  // Otherwise, find the last node, create a new node and attach it to "next_"
  // of the last node
  Node *temp = head_sentinel_->next_;
  while (temp->next_ != head_sentinel_) {
    temp = temp->next_;
  }
  auto *new_node = new Node(new_val);
  new_node->next_ = head_sentinel_;
  head_sentinel_->prev_ = new_node;
  temp->next_ = new_node;

  new_node->prev_ = temp;
}

template<typename T>
void List<T>::push_front(const T& new_val) {
  auto *new_node = new Node(new_val);
  if (empty()) {
    new_node->next_ = head_sentinel_;
    head_sentinel_->prev_ = new_node;
  } else {
    new_node->next_ = head_sentinel_->next_;
    new_node->next_->prev_ = new_node;
  }

  head_sentinel_->next_ = new_node;
  new_node->prev_ = head_sentinel_;
}

template<typename T>
typename List<T>::iterator List<T>::erase(typename List<T>::iterator node_to_delete) {
  // Check if this is the last node in the list. If that's the case do nothing.
  typename List<T>::iterator next = node_to_delete;
  next++;
  if (next == end()) {
    head_sentinel_->prev_ = node_to_delete.get()->prev_;
    node_to_delete.get()->prev_->next_ = head_sentinel_;

    if (node_to_delete == begin()) {
      head_sentinel_->next_ = head_sentinel_;
    }
    delete node_to_delete.get();
    return iterator(head_sentinel_);
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
  if (head_sentinel_->next_ == head_sentinel_) {
    return head_sentinel_->next_;
  }

  if (head_sentinel_->next_ == node_to_delete) {
    Node *temp = head_sentinel_->next_;
    head_sentinel_->next_ = head_sentinel_->next_->next_;
    delete temp;
    return head_sentinel_->next_;
  }

  // If the List is not empty, use the "runner" technique to loop over all
  // nodes and find the one that is to be deleted.
  Node *temp = head_sentinel_->next_->next_;
  Node *previous = head_sentinel_->next_;

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

template<typename T>
void List<T>::reverse() {
  auto it_start = this->begin();
  auto it_end = --this->end();

  while (it_start > it_end) {
    T tmp = *it_start;
    *it_start++ = *it_end;
    *it_end-- = tmp;
  }
}

}  // namespace cci

#endif
