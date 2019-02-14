//========================================================================
//  FILE:
//      include/chapter_5.hpp
//
//  AUTHOR:
//      banach-space@github
//
//  DESCRIPTION:
//    Solutions to practice questions from Chapter 5 in [1] - declarations.
//
//    "Cracking the Coding Interview", Gayle Laakmann McDowell
//
//  License: Apache License 2.0
//========================================================================
#ifndef _CHAPTER_5_
#define _CHAPTER_5_

#include <cstdint>
#include <vector>

namespace cci {
//-----------------------------------------------------------------------------
// Solution to Q1
//
// Fit `m` inside `n` between the bit positions i and j (j > i). Assume that
// there's no more than (j - i + 1) non-zero bits in `m`.
//-----------------------------------------------------------------------------
uint32_t updateBits(uint32_t n, uint32_t m, std::size_t i, std::size_t j);

//-----------------------------------------------------------------------------
// Solution to Q2
//
// Returns the binary representation of the input double (or an empty vector if
// requires more than 32 binary digits). The input number lies between 0 and 1.
//-----------------------------------------------------------------------------
std::vector<int> printBinary(double num);

//-----------------------------------------------------------------------------
// Solutions to Q3
//-----------------------------------------------------------------------------
// Returns the smallest number that is larger than n (n > 0) and has the same
// number of 0s and 1s. Returns 0 on failure.
//-----------------------------------------------------------------------------
uint32_t getNext(uint32_t n);

//-----------------------------------------------------------------------------
// Returns the largest number that is smaller than n (n > 0) and has the same
// number of 0s and 1s. Returns 0 on failure.
//-----------------------------------------------------------------------------
uint32_t getPrev(uint32_t n);

//-----------------------------------------------------------------------------
// Solution to Q4
//-----------------------------------------------------------------------------
// Check if n is a power of two
//-----------------------------------------------------------------------------
bool isPowerOfTwo(uint32_t n);

//-----------------------------------------------------------------------------
// Solution to Q5
//-----------------------------------------------------------------------------
// Returns the number of bits that need to be flipped in order to convert a to
// b (or vice versa)
//-----------------------------------------------------------------------------
size_t numOfBitsToConvert(uint32_t a, uint32_t b);

//-----------------------------------------------------------------------------
// Solution to Q6
//-----------------------------------------------------------------------------
// Swap odd and even bits in n
//-----------------------------------------------------------------------------
uint32_t swapOddAndEvenBits(uint32_t n);

//-----------------------------------------------------------------------------
// Solution to Q7
//-----------------------------------------------------------------------------
// Find missing number in the input array. The input array contains numbers
// from 0 through n, except for one number which is missing. Only binary
// operations are allowed.
//-----------------------------------------------------------------------------
uint32_t findMissing(const std::vector<uint32_t> &array);

//-----------------------------------------------------------------------------
// Solution to Q8
//
// TODO
//-----------------------------------------------------------------------------

} // namespace cci

# endif
