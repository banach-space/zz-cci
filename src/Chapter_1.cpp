//========================================================================
// FILE:
//  Chapter_1.cpp
//
// AUTHOR:
//  banach-space@github
//
// DESCRIPTION:
//    Solutions to practice questions from Chapter 1, "Cracking the Coding
//    Interview", Gayle Laakmann McDowell
//
// License: Apache License 2.0
//========================================================================
#include <string>
#include <string_view>

bool unique_chars(const std::string &input_str) {
  if (input_str.empty()) { return true;}

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
  if (input_str.empty()) { return true;}

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
  if ('\0' == *input_str) { return true;}

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
