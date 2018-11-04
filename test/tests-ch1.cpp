//========================================================================
// FILE:
//  test/tests-ch1.cpp
//
// AUTHOR:
//  banach-space@github
//
// DESCRIPTION:
//    Unit tests for solutions to practice questions from Chapter 1 in [1]
//
//    [1] "Cracking the Coding Interview", Gayle Laakmann McDowell
//
// License: Apache License 2.0
//========================================================================
#include <Chapter_1.h>
#include <gtest/gtest.h>
#include <string_view>
#include <vector>
#include <string.h>
#include <iostream>

//========================================================================
// Test Fixtures
//========================================================================
struct CciChapter1_Q1 : public ::testing::Test {

  // A vector of test strings and bools. For each string the corresponding bool
  // identifies whether the characters in the string are unique.
  std::vector<std::tuple<std::string, bool>> test_strings;

  CciChapter1_Q1() {
    // Construct a string containing all (extended) ASCII characters. Make sure
    // that the NULL character is at the end (so that it's a valid C string).
    std::string ascii_alphabet;
    constexpr uint16_t k_num_ascii_chars = 256;
    for (uint16_t ii = 0; ii < k_num_ascii_chars; ii++) {
      ascii_alphabet.push_back(static_cast<char>(ii));
    }

    ascii_alphabet[static_cast<uint8_t>('\0')] = static_cast<char>(255);
    ascii_alphabet[255] = '\0';

    // Derive a string from ascii_alphabet that contains at least one character
    // twice.
    std::string almost_ascii_alphabet(ascii_alphabet);
    almost_ascii_alphabet.at(5) = 'a';

    // Finally, populate test_strings
    test_strings = {{"", true},
                    {"aa", false},
                    {std::string(256, 'a'), false},
                    {ascii_alphabet, true},
                    {almost_ascii_alphabet, false}};
  }

protected:
  void SetUp() override {}
  void TearDown() override {}
};

struct CciChapter1_Q2 : public ::testing::Test {

  // A vector of test strings tuples: {original string, reversed string}
  std::vector<std::tuple<std::string, std::string>> test_strings;

  CciChapter1_Q2() {
    test_strings = {
    {{""}, {""}},
    {{"aba"}, {"aba"}},
    {{"abba"}, {"abba"}},
    {{"Andrzej Warzynski"}, {"iksnyzraW jezrdnA"}},
    {{"aaaaaaaaaaaaaaaaaaaa"}, {"aaaaaaaaaaaaaaaaaaaa"}},
    {{"xxxxxxxxxxyyyyyyyyyy"}, {"yyyyyyyyyyxxxxxxxxxx"}}
  };

  }

protected:
  void SetUp() override {}
  void TearDown() override {}
};

//========================================================================
// Tests
//========================================================================
TEST_F(CciChapter1_Q1, unique_chars_cpp_string) {
  bool ret_val = false;

  for (auto pair : test_strings) {
    ret_val = unique_chars(std::get<0>(pair));
    EXPECT_EQ(std::get<1>(pair), ret_val);
  }
}

TEST_F(CciChapter1_Q1, unique_chars_c_string) {
  bool ret_val = false;

  for (auto pair : test_strings) {
    ret_val = unique_chars(std::get<0>(pair).c_str());
    EXPECT_EQ(std::get<1>(pair), ret_val);
  }
}

TEST_F(CciChapter1_Q1, unique_chars_string_view) {
  bool ret_val = false;

  for (auto pair : test_strings) {
    ret_val = unique_chars(std::string_view(std::get<0>(pair)));
    EXPECT_EQ(std::get<1>(pair), ret_val);
  }
}

TEST_F(CciChapter1_Q2, reverse_c_string) {
  for (auto pair : test_strings) {
    // The original question requires a modifiable C-string to be passed. What
    // follows is a bit nasty way of generating a modifiable C-string (i.e.
    // char*) from a CPP string (i.e. resorting to raw painters and dynamic
    // memory allocation).
    // (one gotcha: std::string.length() won't include the null character)
    auto length = std::get<1>(pair).length();
    char *current_str = nullptr;
    if (length > 0) {
      current_str = new char[length];
      strncpy(current_str, std::get<0>(pair).c_str(), length+1);
    } else {
      current_str = new char[1];
      *current_str = '\0';
    }

    reverse(current_str);
    ASSERT_STREQ(current_str, std::get<1>(pair).c_str());

    delete[](current_str);
  }
}

TEST_F(CciChapter1_Q2, reverse_cpp_string) {
  for (auto pair : test_strings) {
    std::string current_str(std::get<0>(pair));

    reverse(current_str, ver_2);
    ASSERT_EQ(current_str, std::get<1>(pair).c_str());
  }
}

TEST_F(CciChapter1_Q2, reverse_cpp_string_ver2) {
  for (auto pair : test_strings) {
    std::string current_str(std::get<0>(pair));

    reverse(current_str, ver_1);
    ASSERT_EQ(current_str, std::get<1>(pair).c_str());
  }
}
