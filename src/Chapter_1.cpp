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
#include <algorithm>
#include <string>
#include <string_view>

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

template <> void reverse<ver_1>(std::string &input_str) {
  size_t length = input_str.length();

  // Swap character starting from two corners
  for (size_t ii = 0; ii < length / 2; ii++) {
    std::swap(input_str[ii], input_str[length - ii - 1]);
  }
}

template <> void reverse<ver_2>(std::string &input_str) {
  reverse(input_str.begin(), input_str.end());
}

template <>
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

template <>
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

void replace_space_with_code(std::string &input_str, size_t length) {
  // Count the number of whitespaces.
  size_t space_count = 0;
  for (size_t ii = 0; ii < length; ii++) {
    if (' ' == input_str[ii]) {
      space_count++;
    }
  }

  // Replaces the whitespaces with %20 (as per the question). Start from the
  // back (that's easier).
  size_t new_length = length + space_count * 2;
  size_t input_idx = new_length - 1;
  for (int ii = length - 1; ii >= 0; ii--) {
    if (' ' == input_str[ii]) {
      input_str[input_idx] = '0';
      input_str[input_idx - 1] = '2';
      input_str[input_idx - 2] = '%';
      input_idx -= 3;
    } else {
      input_str[input_idx] = input_str[ii];
      input_idx--;
    }
  }
}

std::string string_compress(const std::string &input_str) {
  size_t compressed_string_length = 0;
  size_t current_char_count = 1;

  // Step 1 - calculate the length of the compressed string
  // Assume that null character is never a valid char so that it can be used in
  // the initialisation below.
  char prev_char = '\0';
  for (auto current_char : input_str) {
    if (current_char == prev_char) { 
      current_char_count++; 
    } else {
      compressed_string_length++;
      compressed_string_length += std::to_string(current_char_count).length();

      prev_char = current_char;
      current_char_count = 1;
    }
  }

  // Step 2 - if the compressed string is longer than the original one, then
  // return the original string.
  if (compressed_string_length >= input_str.length()) {
    std::string compressed_string = input_str;
    return compressed_string;
  }

  // Step 3 - compress the string and return the compressed version
  std::string compressed_string;
  // This vvvv is important, otherwise concatention could be very expensive.
  compressed_string.reserve(compressed_string_length);
  prev_char = input_str[0];
  current_char_count = 1;

  for (size_t ii= 1; ii < input_str.length(); ii++) {
    if (input_str[ii] == prev_char) { 
      current_char_count++; 
    } else {
      // Add the last char and it's count
      compressed_string += prev_char;
      compressed_string += std::to_string(current_char_count);

      // Reset the current char count, prev_char and add the current character
      current_char_count = 1;
      prev_char = input_str[ii];
    }
  }
  // Append the final character and the corresponding character count
  compressed_string += prev_char;
  compressed_string += std::to_string(current_char_count);

  return compressed_string;
}
