//========================================================================
//  FILE:
//      include/Chapter_1.hpp
//
//  AUTHOR:
//      banach-space@github
//
//  DESCRIPTION:
//    Solutions to practice questions from Chapter 1 in [1] - declarations.
//
//    "Cracking the Coding Interview", Gayle Laakmann McDowell
//
//  License: Apache License 2.0
//========================================================================
//
#ifndef _CHAPTER_1_
#define _CHAPTER_1_

#include <string>
#include <string_view>
#include <vector>

namespace cci {
// Generic data (types) used across multiple solutions
enum impl_ver { ver_1 = 0, ver_2 = 1 };
const size_t k_num_ascii_chars = 256;

//-----------------------------------------------------------------------------
// Solutions to Q1
//-----------------------------------------------------------------------------
bool unique_chars(const std::string &input_str);
bool unique_chars(const char *input_str);
bool unique_chars(std::string_view input_str);

//-----------------------------------------------------------------------------
// Solution to Q2
//-----------------------------------------------------------------------------
void reverse(char *input_str);

template <impl_ver ver> void reverse(std::string &input_str);

//-----------------------------------------------------------------------------
// Solution to Q3
//-----------------------------------------------------------------------------
template <impl_ver ver>
bool permutation(const std::string &str1, const std::string &str2);

//-----------------------------------------------------------------------------
// Solution to Q4
// FYI The "code" refers to "%20" from the Question
//-----------------------------------------------------------------------------
void replace_space_with_code(std::string &input_str, size_t len);

//-----------------------------------------------------------------------------
// Solutions to Q5
//-----------------------------------------------------------------------------
std::string string_compress(const std::string &);

//-----------------------------------------------------------------------------
// Solution to Q6
//-----------------------------------------------------------------------------
using image = std::vector<std::vector<char>>;
void rotate(image &);

//-----------------------------------------------------------------------------
// Solution to Q7
//-----------------------------------------------------------------------------
using matrix = std::vector<std::vector<int>>;
void setZeros(matrix &);

//-----------------------------------------------------------------------------
// Solution to Q8
//-----------------------------------------------------------------------------
bool isRotation(const std::string &parent_string, const std::string &substring);

} // namespace cci
#endif
