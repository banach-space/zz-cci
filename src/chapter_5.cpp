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
  // Edge case ... Otherwise left_mask would be 0 "[...] reduced modulo one more
  // than the maximum value representable in the result type".
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

//-----------------------------------------------------------------------------
// Solutions to Q3
//-----------------------------------------------------------------------------
uint32_t cci::getNext(uint32_t n) {
  uint32_t c = n;
  // Number of trailing 0s
  uint32_t c0 = 0;
  // The size of block of 1s immediately to the left of the trailing 0s
  uint32_t c1 = 0;

  // Get the number of trailing 0s
  if (c != 0) {
    while ((c & 1u) == 0) {
      c0++;
      c >>= 1u;
    }
  }

  // Get the number of 1s before the next 0. Note that at this point all
  // trailing 0s have already been shifted away.
  while ((c & 1u) == 1) {
    c1++;
    c >>= 1u;
  }

  // Error: if n == 11...1100...00 or n == 0, then there is no bigger number
  // with the same number of 1s
  if (c0 + c1 == 31 || c0 + c1 == 0) {
    return 0;
  }

  // Position of the rightmost non-trailing zero
  uint32_t p = c0 + c1;

  // Flip the righmost non-trailing zero
  n |= (1u << p);
  // Clear all bits to the right of p
  n &= ~((1u << p) - 1);
  // Insert (c1 - 1) 1s on the right
  n |= (1u << (c1 - 1)) - 1;

  return n;
}

uint32_t cci::getPrev(uint32_t n) {
  uint32_t temp = n;
  // the number of trailing 1s
  uint32_t c1 = 0;
  // the size of the block of 0s immediately to the left of the trailing 1s
  uint32_t c0 = 0;

  while (1u == (temp & 1u)) {
    c1++;
    temp >>= 1;
  }

  // Error: n == 0...0111, there is no smaller number than n with the same
  // number of 1s
  if (0 == temp)
    return 0;

  while (((temp & 1u) == 0) && (temp != 0)) {
    c0++;
    temp >>= 1;
  }

  // Position of the righmost non-trailing 1
  uint32_t p = c0 + c1;
  // Clears from bit p onwards
  n &= ((~0u) << (p + 1));
  // Sequence of (c1 + 1) ones
  uint32_t mask = (1u << (c1 + 1)) - 1;
  n |= mask << (c0 - 1);

  return n;
}

//-----------------------------------------------------------------------------
// Solutions to Q4
//-----------------------------------------------------------------------------
bool cci::isPowerOfTwo(uint32_t n) { return ((n & (n - 1)) == 0); }

//-----------------------------------------------------------------------------
// Solutions to Q5
//-----------------------------------------------------------------------------
size_t cci::numOfBitsToConvert(uint32_t a, uint32_t b) {
  size_t count = 0;

  for (uint32_t c = a ^ b; c != 0; c = c & (c - 1)) {
    count++;
  }

  return count;
}

//-----------------------------------------------------------------------------
// Solutions to Q6
//-----------------------------------------------------------------------------
uint32_t cci::swapOddAndEvenBits(uint32_t n) {
  return (((n & 0xaaaaaaaau) >> 1u) | ((n & 0x55555555u) << 1u));
}
