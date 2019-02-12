//========================================================================
// FILE:
//  chapter_5.cpp
//
// AUTHOR:
//  banach-space@github
//
// DESCRIPTION:
//    Solutions to practice questions from Chapter 5 in [1] - implementation.
//
//    [1] "Cracking the Coding Interview", Gayle Laakmann McDowell
//
// License: Apache License 2.0
//========================================================================
#include <chapter_5.hpp>

using namespace cci;
//-----------------------------------------------------------------------------
// Solution to Q1
//
// It is assumed that there is 32 bits in and int and that bits are numbered
// from right to left.
//-----------------------------------------------------------------------------
uint32_t cci::updateBits(uint32_t n, uint32_t m, std::size_t i, std::size_t j) {
  uint32_t all_ones = ~0; 

  // The mask that corresponds to the [31, j + 1]
  uint32_t left_mask = all_ones << (j + 1);
  // Edge case ... Otherwise left_mask would be 0 "[...] reduced modulo one more than
  // the maximum value representable in the result type".
  if (j == 31) {
    left_mask = 0u;
  }
  // The mask that corresponds to the [i - 1, 0]
  uint32_t right_mask = ((1 << i) - 1);
  // The mask that corresponds to the [i, j] intterval
  uint32_t mask = left_mask | right_mask;

  uint32_t n_cleared = n & mask;
  uint32_t m_shifted = m << i;


  return n_cleared | m_shifted;
}

//-----------------------------------------------------------------------------
// Solution to Q2
//-----------------------------------------------------------------------------
std::vector<int> cci::printBinary(double num) {
  std::vector<int> binary;

  while (num > 0) {
    // Set the limit on the length of the representation
    if (binary.size() >= 32) {
      return binary;
    }

    double r = num * 2;
    if (r >= 1) {
      binary.push_back(1);
      num = r - 1;
    } else {
      binary.push_back(0);
      num = r;
    }
  }

  return binary;
}
