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
enum reverse_ver {
  ver_1 = 0,
  ver_2 = 1
};

void reverse(char *input_str);
void reverse(std::string& input_str, reverse_ver ver);

#endif
