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

template<>
void reverse<ver_1>(std::string& input_str)
{
    size_t length = input_str.length();

    // Swap character starting from two corners
    for (size_t ii = 0; ii < length / 2; ii++) {
        std::swap(input_str[ii], input_str[length - ii - 1]);
    }
}

template<>
void reverse<ver_2>(std::string& input_str)
{
    reverse(input_str.begin(), input_str.end());
}

template<>
bool permutation<ver_1>(const std::string &str1, const std::string &str2) {
  if (str1.length() != str2.length()) {
    return false;
  }

  std::string str1_sorted = str1;
  sort(str1_sorted.begin(), str1_sorted.end());

  std::string str2_sorted = str2;
  sort(str2_sorted.begin(), str2_sorted.end());

  return (str1_sorted == str2_sorted);
}

template<>
bool permutation<ver_2>(const std::string &str1, const std::string &str2) {
  if (str1.length() != str2.length()) {
    return false;
  }

  char chars_in_string1[256] = {};
  char chars_in_string2[256] = {};

  for (auto current_char : str1) {
    chars_in_string1[(static_cast<uint8_t>(current_char))]++;
  }

  for (auto current_char : str2) {
    chars_in_string2[(static_cast<uint8_t>(current_char))]++;
  }

  for (size_t ii = 0; ii < 256; ii++) {
    if (chars_in_string1[ii] != chars_in_string2[ii]) {
      return false;
    }
  }

  return true;
}
