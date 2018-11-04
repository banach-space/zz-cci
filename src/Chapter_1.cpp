//========================================================================
// FILE:
//  Chapter_1.cpp
//
// AUTHOR:
//  banach-space@github
//
// DESCRIPTION:
//    Solutions to practice questions from Chapter 1 in [1] - implementation.
//
//    "Cracking the Coding Interview", Gayle Laakmann McDowell
//
// License: Apache License 2.0
//========================================================================
#include <Chapter_1.h>
#include <string>
#include <string_view>
#include <algorithm>

bool unique_chars(const std::string &input_str) {
  if (input_str.empty()) {
    return true;
  }

  uint32_t present[256] = {};

  for (auto &item : input_str) {
    present[(static_cast<uint8_t>(item))]++;
  }

  for (auto item : present) {
    if (item > 1) {
      return false;
    }
  }

  return true;
}

bool unique_chars(const std::string_view input_str) {
  if (input_str.empty()) {
    return true;
  }

  uint32_t present[256] = {};

  for (auto &item : input_str) {
    present[(static_cast<uint8_t>(item))]++;
  }

  for (auto item : present) {
    if (item > 1) {
      return false;
    }
  }

  return true;
}

bool unique_chars(const char *input_str) {
  if ('\0' == *input_str) {
    return true;
  }

  uint32_t present[256] = {};

  auto current_char = '\0';
  while ('\0' != (current_char = *input_str++)) {
    present[(static_cast<uint8_t>(current_char))]++;
  }

  for (auto item : present) {
    if (item > 1) {
      return false;
    }
  }

  return true;
}

void reverse(char *input_str) {
  if ('\0' == *input_str) {
    return;
  }

  char tmp = '\0';
  char *str_end = input_str;
  char *str_start = input_str;

  while ('\0' != *str_end) {
    str_end++;
  }
  str_end--;

  while (str_end > str_start) {
    tmp = *str_start;
    *str_start++ = *str_end;
    *str_end-- = tmp;
  }
}

static void reverse_cpp_ver_1(std::string& input_str)
{
    size_t length = input_str.length();

    // Swap character starting from two corners
    for (size_t ii = 0; ii < length / 2; ii++)
        std::swap(input_str[ii], input_str[length - ii - 1]);
}

static void reverse_cpp_ver_2(std::string& input_str)
{
    reverse(input_str.begin(), input_str.end());
}

void reverse(std::string &input_str, reverse_ver ver) {
  if (ver == ver_1) {
    return reverse_cpp_ver_1(input_str);
  } else {
    return reverse_cpp_ver_2(input_str);
  }
}

