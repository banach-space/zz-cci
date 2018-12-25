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

#include <memory>
#include <vector>

//------------------------------------------------------------------------
// Solutions to Q1
//------------------------------------------------------------------------
// There are 2 solutions here:
//    * SimpleMultiStack for which each substack occupies a fixed space
//    * Stack for which each substack initilally occpies pre-defined space, but
//    this is flexible and adjusted as required at runtime
namespace cci {
class SimpleMultiStack {
  public:
  explicit SimpleMultiStack(int size = 100, size_t num_stacks_ = 3) :
                       stack_size_(size), num_substacks__(num_stacks_) {
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
    int value = buffer_[absTopOfSimpleMultiStack(stack_num)];
    buffer_[absTopOfSimpleMultiStack(stack_num)] = {};
    stack_top_[stack_num]--;
    return value;
  }

  int peek(int stack_num_) {
    int index = absTopOfSimpleMultiStack(stack_num_);
    return buffer_[index];
  }

  bool isEmpty(int stack_num) {
    return stack_top_[stack_num] == -1;
  }

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
    explicit StackData(int start, int capacity) : start_(start), capacity_(capacity) {
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
  explicit MultiStack(size_t stack_size = 0, size_t num_stacks_ = 0) : init_substack_size_(stack_size), num_of_substacks_(num_stacks_) {
    total_size_ = init_substack_size_ * num_of_substacks_;

    stacks_.reserve(num_of_substacks_);
    for (size_t ii = 0; ii < num_of_substacks_; ii++) {
      stacks_.emplace_back(StackData(ii * init_substack_size_, init_substack_size_));
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
    if (index + 1 == total_size_) {
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
         stack.isWithinStack(i, total_size_);
         i = previousElement(i)) {
         buffer_[i] = buffer_[previousElement(i)];
    }

    buffer_[stack.start_] = 0;
    stack.start_ = nextElement(stack.start_); // move stack start
    stack.top_ = nextElement(stack.top_); //move pointer
    stack.capacity_--; // return capacity to original
  }

  void expand(int stackNum) {
    shift((stackNum + 1) % num_of_substacks_);
    stacks_[stackNum].capacity_++;
  }

  void push(int stackNum, int value) {
    StackData &stack = stacks_[stackNum];
    // Check that we have space
    if (stack.size_ >= stack.capacity_) {
      if (numOfElements() >= total_size_) {// Totally full
        throw std::out_of_range("Reached the capacity of the stack");
      }
      else {
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
} // namespace cci

//------------------------------------------------------------------------
// Solution to Q1
//------------------------------------------------------------------------


#endif

