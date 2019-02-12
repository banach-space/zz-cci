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
}

# endif
