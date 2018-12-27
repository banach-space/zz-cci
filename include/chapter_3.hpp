//========================================================================
//  FILE:
//      include/chapter_3.hpp
//
//  AUTHOR:
//      banach-space@github
//
//  DESCRIPTION:
//    Solutions to practice questions from Chapter 3 in [1] as well as helper
//    data structures.
//
//    "Cracking the Coding Interview", Gayle Laakmann McDowell
//
//  License: Apache License 2.0
//========================================================================
#ifndef _CHAPTER_3_
#define _CHAPTER_3_

#include <iostream>
#include <limits.h>
#include <memory>
#include <stack>
#include <vector>

//------------------------------------------------------------------------
// Solutions to Q1
//------------------------------------------------------------------------
// There are 2 solutions here:
//    * SimpleMultiStack for which each substack occupies a fixed space
//    * Stack for which each substack initilally occpies pre-defined space, but
//      this is flexible and adjusted as required at runtime
//------------------------------------------------------------------------
namespace cci {
class SimpleMultiStack {
public:
  explicit SimpleMultiStack(int size = 100, size_t num_stacks_ = 3)
      : stack_size_(size), num_substacks__(num_stacks_) {
    buffer_ = std::make_unique<int[]>(size * num_substacks__);
    stack_top_ = std::make_unique<int[]>(num_substacks__);

    for (size_t ii = 0; ii < num_substacks__; ii++) {
      stack_top_[ii] = -1;
    }
  }

  void push(size_t stack_num, int value) {
    // Check if there's space
    if (stack_top_[stack_num] + 1 >= stack_size_) {
      throw std::out_of_range("Reached the capacity of the stack");
    }

    // Increment stack pointer and the update top value
    stack_top_[stack_num]++;
    buffer_[absTopOfSimpleMultiStack(stack_num)] = value;
  }

  int pop(size_t stack_num) {
    int index = absTopOfSimpleMultiStack(stack_num);
    if (-1 == index) {
      throw std::out_of_range("Empty stack");
    }

    int value = buffer_[index];
    buffer_[index] = {};
    stack_top_[stack_num]--;
    return value;
  }

  int peek(int stack_num_) {
    int index = absTopOfSimpleMultiStack(stack_num_);
    return buffer_[index];
  }

  bool isEmpty(int stack_num) { return stack_top_[stack_num] == -1; }

private:
  int stack_size_;
  size_t num_substacks__;
  std::unique_ptr<int[]> buffer_;
  std::unique_ptr<int[]> stack_top_;

  // Returns index of top of stack "stack_num", in absolute terms
  int absTopOfSimpleMultiStack(int stack_num) {
    return stack_num * stack_size_ + stack_top_[stack_num];
  }
};

// StackData is a simple class that holds a set of data about each sub-stack. It
// does not hold the actual items in the stack.
struct StackData {
  explicit StackData(int start, int capacity)
      : start_(start), capacity_(capacity) {
    top_ = start_ - 1;
  }

  bool isWithinStack(size_t index, size_t total_size) {
    // Note: if stack wraps, the head (right side) wraps around to the lef.
    if (start_ <= index && index < start_ + capacity_) {
      // Non-wrapping, or "head" (right side) of wrapping case
      return true;
    }

    if ((start_ + capacity_ > total_size) &&
        (index < (start_ + capacity_) % total_size)) {
      // tail (left side) of wrapping case
      return true;
    }

    return false;
  }

  // The location of the beginning of the stack
  unsigned int start_;
  // The location of the top of the stack (-1 if empty)
  int top_;
  // The number of elemenents in the stack
  unsigned size_ = 0;
  unsigned capacity_;
};

//
class MultiStack {
public:
  explicit MultiStack(size_t stack_size = 0, size_t num_stacks_ = 0)
      : init_substack_size_(stack_size), num_of_substacks_(num_stacks_) {
    total_size_ = init_substack_size_ * num_of_substacks_;

    stacks_.reserve(num_of_substacks_);
    for (size_t ii = 0; ii < num_of_substacks_; ii++) {
      stacks_.emplace_back(
          StackData(ii * init_substack_size_, init_substack_size_));
    }

    buffer_.resize(total_size_);
  }

  size_t numOfElements() {
    size_t res = 0;
    for (auto stack : stacks_) {
      res += stack.size_;
    }
    return res;
  }

  size_t nextElement(int index) {
    if (static_cast<size_t>(index + 1) == total_size_) {
      return 0;
    }

    return index + 1;
  }

  int previousElement(int index) {
    if (index == 0) {
      return total_size_ - 1;
    }

    return index - 1;
  }

  void shift(size_t stackNum) {
    StackData &stack = stacks_[stackNum];

    if (stack.size_ >= stack.capacity_) {
      int nextStack = (stackNum + 1) % num_of_substacks_;
      shift(nextStack); // make some room
      stack.capacity_++;
    }

    // Shift elements in reverse order
    for (int i = (stack.start_ + stack.capacity_ - 1) % total_size_;
         stack.isWithinStack(i, total_size_); i = previousElement(i)) {
      buffer_[i] = buffer_[previousElement(i)];
    }

    buffer_[stack.start_] = 0;
    stack.start_ = nextElement(stack.start_); // move stack start
    stack.top_ = nextElement(stack.top_);     // move pointer
    stack.capacity_--;                        // return capacity to original
  }

  void expand(int stackNum) {
    shift((stackNum + 1) % num_of_substacks_);
    stacks_[stackNum].capacity_++;
  }

  void push(int stackNum, int value) {
    StackData &stack = stacks_[stackNum];
    // Check that we have space
    if (stack.size_ >= stack.capacity_) {
      if (numOfElements() >= total_size_) { // Totally full
        throw std::out_of_range("Reached the capacity of the stack");
      } else {
        // Just need to shift things around
        expand(stackNum);
      }
    }

    // Find the index of the top element in the array + 1, and increment the
    // stack pointer
    stack.size_++;
    stack.top_ = nextElement(stack.top_);
    buffer_[stack.top_] = value;
  }

  int pop(int stackNum) {
    StackData &stack = stacks_[stackNum];

    if (stack.size_ == 0) {
      throw std::out_of_range("Empty stack");
    }

    int value = buffer_[stack.top_];
    buffer_[stack.top_] = 0;
    stack.top_ = previousElement(stack.top_);
    stack.size_--;
    return value;
  }

  int peek(int stackNum) {
    StackData &stack = stacks_[stackNum];
    return buffer_[stack.top_];
  }

  bool isEmpty(int stackNum) {
    StackData &stack = stacks_[stackNum];
    return stack.size_ == 0;
  }

private:
  // The substack size at the beginning. This is only used to allocate the
  // stack buffer. At runtime each substack's size can be increased or
  // decreased.
  size_t init_substack_size_;
  size_t num_of_substacks_;
  size_t total_size_;
  std::vector<StackData> stacks_;
  std::vector<int> buffer_;
};

//------------------------------------------------------------------------
// Solutions to Q2
//------------------------------------------------------------------------
class StackWithMin {
public:
  void push(int value) {
    if (value <= min()) {
      stack_of_mins_.push(value);
    }
    main_stack_.push(value);
  }

  int pop() {
    int value = main_stack_.top();
    main_stack_.pop();
    if (value == min()) {
      stack_of_mins_.pop();
    }

    return value;
  }

  int min() {
    if (!stack_of_mins_.empty()) {
      return (stack_of_mins_.top());
    }

    return INT_MIN;
  }

private:
  std::stack<int> main_stack_;
  std::stack<int> stack_of_mins_;
};

//------------------------------------------------------------------------
// Solutions to Q3
//------------------------------------------------------------------------
// What follows is a basic solution that doesn't offer popAt.
// StackOfPlatesBasic encapsulates a stack that internally is represented as
// multiple std::stack(s). The name of the class reflects the fact that the
// original problem was introduced with the aid of "stack of plates" ...
class StackOfPlatesBasic {
public:
  explicit StackOfPlatesBasic(size_t substack_size)
      : substack_max_size_(substack_size) {
    // Init by having one std::stack
    stacks_.emplace_back();
  }

  void push(int value) {
    auto &last_stack = stacks_.back();
    // If the last stack still has space for more elements, push the value
    // there.
    if (last_stack.size() < substack_max_size_) {
      last_stack.push(value);
      return;
    }

    // The last stack is already full, so create a new substack and push the
    // value there.
    stacks_.emplace_back();
    stacks_.back().push(value);
  }

  int pop() {
    // Pop the value from the last sub-stack
    auto &last_stack = stacks_.back();
    int value = last_stack.top();
    last_stack.pop();

    // If this operation makes the last sub-stack empty then delete it.
    if (last_stack.empty()) {
      stacks_.pop_back();
    }

    return value;
  }

private:
  // Contains all the sub-stacks
  std::vector<std::stack<int>> stacks_;
  // Size limit for sub-stacks
  size_t substack_max_size_;
};

// Implements a stack that will be used in StackOfPlatesComplex. Tracks it's
// top and bottom to allow a "rollover" system.
class StackComplex {
  struct Node;

public:
  explicit StackComplex(size_t capacity)
      : size_(0), capacity_(capacity), top_(nullptr), bottom_(nullptr) {}

  StackComplex(const StackComplex &other) {
    // This is inherited from other
    capacity_ = other.capacity_;

    // These are reset to init state because *this is still empty
    size_ = 0;
    bottom_ = nullptr;
    top_ = nullptr;

    // Fill in *this with values from other
    auto *it = other.bottom_;
    while (nullptr != it) {
      push(it->value);
      it = it->above_;
    }
  }

  StackComplex &operator=(StackComplex other) {
    // This is inherited from other
    capacity_ = other.capacity_;

    // These are reset to init state because *this is still empty
    size_ = 0;
    bottom_ = nullptr;
    top_ = nullptr;

    auto *it = other.bottom_;
    while (nullptr != it) {
      push(it->value);
      it = it->above_;
    }

    return *this;
  }

  StackComplex(StackComplex &&other) noexcept {
    // Take/move all data from other
    size_ = other.size_;
    capacity_ = other.capacity_;
    bottom_ = other.bottom_;
    top_ = other.top_;

    // Set other to empty state
    other.top_ = nullptr;
    other.bottom_ = nullptr;
    other.size_ = 0;
  }

  ~StackComplex() {
    while (nullptr != top_) {
      Node *t = top_;
      top_ = top_->below_;
      delete t;
    }
  }

  int pop() {
    if (nullptr == top_) {
      throw std::out_of_range("Empty stack");
    }

    // Get the return value
    Node *t = top_;
    int ret_val = t->value;

    // Update top_
    top_ = top_->below_;
    delete t;
    size_--;

    return ret_val;
  }

  // Returns true if successful, false otherwise (which means that this stack is
  // already full)
  bool push(int val) {
    if (size_ >= capacity_) {
      return false;
    }

    Node *new_node = new Node(val);
    if (0 == size_) {
      bottom_ = new_node;
    }

    join(new_node, top_);
    top_ = new_node;

    size_++;
    return true;
  }

  // Takes two adjacent nodes and sets their above_ and below_ pointers
  // accordingly (to mark the relation)
  void join(Node *above, Node *below) {
    if (nullptr != below) {
      below->above_ = above;
    }
    if (nullptr != above) {
      above->below_ = below;
    }
  }

  bool isEmpty() { return (0 == size_); }

  // Remove the node from the bottom of the stack and update bottom_
  // accordingly. Returns the value that was stored in that node.
  int removeBottom() {
    // Get the return value
    int ret_val = bottom_->value;

    // Update bottom_
    Node *b = bottom_;
    bottom_ = bottom_->above_;
    if (nullptr != bottom_) {
      // There's nothing "below" the bottom
      bottom_->below_ = nullptr;
    } else {
      // "bottom_" is empty so this stack is empty and "top_" should also be
      // marked as empty (i.e. before this update we had top_ == bottom_)
      top_ = nullptr;
    }

    // Delete old bottom_
    delete b;
    size_--;
    return ret_val;
  }

  size_t size() { return size_; }

private:
  struct Node {
    explicit Node(int val) : value(val), above_(nullptr), below_(nullptr) {}

    int value;
    Node *above_;
    Node *below_;
  };

  size_t size_;
  size_t capacity_;
  // Top of this stack
  Node *top_;
  // Bottom of this stack
  Node *bottom_;
};

// A complex solution to Q3, provides popAt. Internally the sub-stacks are
// represented as instances of StackComplex.
class StackOfPlatesComplex {
public:
  explicit StackOfPlatesComplex(size_t substack_size)
      : substack_max_size_(substack_size) {
    // Init by creating one sub-stack
    stacks_.emplace_back(substack_max_size_);
  }

  void push(int value) {
    auto &last_stack = stacks_.back();

    // If the last sub-stack has space then push there.
    if (last_stack.size() < substack_max_size_) {
      if (!last_stack.push(value)) {
        throw std::out_of_range("Substack if full");
      }
      return;
    }

    // The last sub-stack is already full. Create a new substack and push the
    // value there.
    stacks_.emplace_back(substack_max_size_);
    if (!stacks_.back().push(value)) {
      throw std::out_of_range("Substack if full");
    }
  }

  int pop() {
    // Get the value from the last sub-stack
    auto &last_stack = stacks_.back();
    int value = last_stack.pop();

    // Check if this operation makes the last sub-stack empty. If so then
    // delete it.
    if (last_stack.isEmpty()) {
      stacks_.pop_back();
    }

    return value;
  }

  // Pop a value from a substack at "index"
  int popAt(size_t index) { return leftShift(index, true /* Pop from top */); }

  // Grabs a value (either top of bottom) from sub-stack at "index" and returns
  // it. If this makes the sub-stack at "index" not at its full capacity then
  // need to grab a value from the following sub-stack and push it here.
  int leftShift(size_t index, bool remove_top) {
    StackComplex &current_stack = stacks_.at(index);
    int removed_item{};

    if (remove_top) {
      removed_item = current_stack.pop();
    } else {
      removed_item = current_stack.removeBottom();
    }

    if (current_stack.isEmpty()) {
      stacks_.erase(stacks_.begin() + index);
    } else if (stacks_.size() > (index + 1)) {
      int v = leftShift(index + 1, false);
      current_stack.push(v);
    }

    return removed_item;
  }

private:
  std::vector<cci::StackComplex> stacks_;
  size_t substack_max_size_;
};

//------------------------------------------------------------------------
// Solution to Q4
//------------------------------------------------------------------------
class Tower {
public:
  void add(unsigned d) {
    if (!disks.empty() && disks.top() <= d) {
      throw std::out_of_range(std::string("Error placing disk ") +
                              std::to_string(d));
    } else {
      disks.push(d);
    }
  }

  void moveTopTo(Tower *t) {
    unsigned top = disks.top();
    disks.pop();
    t->add(top);
  }

  void moveDisks(size_t n, Tower *destination, Tower *buffer) {
    if (n > 0) {
      moveDisks(n - 1, buffer, destination);
      moveTopTo(destination);
      buffer->moveDisks(n - 1, destination, this);
    }
  }

  unsigned pop() {
    unsigned ret_val = disks.top();
    disks.pop();
    return ret_val;
  }

private:
  std::stack<unsigned> disks;
};

} // namespace cci

#endif
