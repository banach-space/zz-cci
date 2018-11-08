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

// Q1
bool unique_chars(const std::string &input_str);
bool unique_chars(const char *input_str);
bool unique_chars(const std::string_view input_str);

// Q2
void reverse(char *input_str);

enum reverse_ver {
  ver_1 = 0,
  ver_2 = 1
};

template<reverse_ver ver>
void reverse(std::string& input_str);

// Q3
template<reverse_ver ver>
bool permutation(const std::string &str1, const std::string &str2);

// Q4
// FYI The code refers to %20 from the Question
void replace_space_with_code(std::string &input_str, size_t len);

// Q5
std::string string_compress(const std::string &);

#endif
