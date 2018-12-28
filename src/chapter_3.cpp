//========================================================================
// FILE:
//  chapter_3.cpp
//
// AUTHOR:
//  banach-space@github
//
// DESCRIPTION:
//    Solutions to practice questions from Chapter 3 in [1] - implementation.
//
//    [1] "Cracking the Coding Interview", Gayle Laakmann McDowell
//
// License: Apache License 2.0
//========================================================================
#include <chapter_3.hpp>

namespace cci {
//------------------------------------------------------------------------
// Solution to Q6
//------------------------------------------------------------------------
std::stack<int> sort(std::stack<int> *stack_in) {
  std::stack<int> sorted;

  while (!stack_in->empty()) {
    int tmp = stack_in->top();
    stack_in->pop();

    while (!sorted.empty() && sorted.top() > tmp) {
      stack_in->push(sorted.top());
      sorted.pop();
    }
    sorted.push(tmp);
  }

  return sorted;
}
}
