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
#include <gtest/gtest.h>

#include <cstring>
#include <iostream>
#include <string_view>
#include <vector>

#include <chapter_1.hpp>

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
    test_strings = {{{""}, {""}},
                    {{"aba"}, {"aba"}},
                    {{"abba"}, {"abba"}},
                    {{"Andrzej Warzynski"}, {"iksnyzraW jezrdnA"}},
                    {{"aaaaaaaaaaaaaaaaaaaa"}, {"aaaaaaaaaaaaaaaaaaaa"}},
                    {{"xxxxxxxxxxyyyyyyyyyy"}, {"yyyyyyyyyyxxxxxxxxxx"}}};
  }

protected:
  void SetUp() override {}
  void TearDown() override {}
};

struct CciChapter1_Q3 : public ::testing::Test {
  // A vector of test strings tuples: {original string, anagram|antigram}
  std::vector<std::tuple<std::string, std::string>> anagrams;
  std::vector<std::tuple<std::string, std::string>> antigrams;

  CciChapter1_Q3() {
    anagrams = {{{""}, {""}},
                {{"dog"}, {"god"}},
                {{"Andrzej"}, {"jezrdnA"}},
                {{"Warzynski"}, {"iksnyzraW"}},
                {{"¬!£$%^&*()_+{}:@~<>?|"}, {"|?><~@:}{+_)(*&^%$£!¬"}}};

    antigrams = {
        {{"dog"}, {"goG"}},           {{"Andrzej"}, {"Warzynski"}},
        {{"Warzynski"}, {"Andrzej"}}, {{"Andrzej"}, {"andrzej"}},
        {{"Andrzej"}, {" Andrzej"}},
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
    // (one gotcha: std::string.length() doesn't include the null character)
    auto length = std::get<1>(pair).length() + 1;
    char *current_str = nullptr;
    current_str = new char[length];
    strncpy(current_str, std::get<0>(pair).c_str(), length);

    reverse(current_str);
    ASSERT_STREQ(current_str, std::get<1>(pair).c_str());

    delete[](current_str);
  }
}

TEST_F(CciChapter1_Q2, reverse_cpp_string_ver1) {
  for (auto pair : test_strings) {
    std::string current_str(std::get<0>(pair));

    reverse<ver_1>(current_str);
    ASSERT_EQ(current_str, std::get<1>(pair).c_str());
  }
}

TEST_F(CciChapter1_Q2, reverse_cpp_string_ver2) {
  for (auto pair : test_strings) {
    std::string current_str(std::get<0>(pair));

    reverse<ver_2>(current_str);
    ASSERT_EQ(current_str, std::get<1>(pair).c_str());
  }
}

TEST_F(CciChapter1_Q3, permutation_ver1) {
  for (auto pair : anagrams) {
    ASSERT_TRUE(permutation<ver_1>(std::get<0>(pair), std::get<1>(pair)));
  }

  for (auto pair : antigrams) {
    ASSERT_FALSE(permutation<ver_1>(std::get<0>(pair), std::get<1>(pair)));
  }
}

TEST_F(CciChapter1_Q3, permutation_ver2) {
  for (auto pair : anagrams) {
    ASSERT_TRUE(permutation<ver_2>(std::get<0>(pair), std::get<1>(pair)));
  }

  for (auto pair : antigrams) {
    ASSERT_FALSE(permutation<ver_2>(std::get<0>(pair), std::get<1>(pair)));
  }
}

TEST(CciChapter1_Q4, replace_space_with_code) {
  std::vector<std::tuple<std::string, std::string, size_t>> test_strings = {
      {{"Mr John Smith    "}, {"Mr%20John%20Smith"}, 13},
      {{"Mr  John  Smith        "}, {"Mr%20%20John%20%20Smith"}, 15},
      {{"MrJohnSmith"}, {"MrJohnSmith"}, 11},
  };

  for (auto test_case : test_strings) {
    replace_space_with_code(std::get<0>(test_case), std::get<2>(test_case));

    ASSERT_EQ(std::get<0>(test_case), std::get<1>(test_case));
  }
}

TEST(CciChapter1_Q5, string_compress) {
  std::vector<std::tuple<std::string, std::string>> test_strings = {
      {{"aabcccccaaa"}, {"a2b1c5a3"}},
      {{"abcd"}, {"abcd"}},
      {{"abcdaaaaaaaaa"}, {"a1b1c1d1a9"}},
      {{"abcdaaaaaaaaa"}, {"a1b1c1d1a9"}},
      {{"abcdaaaaaaaaaaaaaaaaaaaaaaaaaaaaaa"}, {"a1b1c1d1a30"}},
  };

  for (auto test_case : test_strings) {
    std::string compressed_str = string_compress(std::get<0>(test_case));

    ASSERT_EQ(compressed_str, std::get<1>(test_case));
  }
}

TEST(CciChapter1_Q6, reverse) {
  std::vector<std::tuple<image, image>> test_images = {
      {{}, {}},
      {{{'a', 'b'}, {'c', 'd'}}, {{'c', 'a'}, {'d', 'b'}}},
      {{{'a', 'b', 'c'}, {'d', 'e', 'f'}, {'g', 'h', 'i'}},
       {{'g', 'd', 'a'}, {'h', 'e', 'b'}, {'i', 'f', 'c'}}},
      {{{'a', 'b', 'c', 'd'},
        {'e', 'f', 'g', 'h'},
        {'i', 'j', 'k', 'l'},
        {'m', 'n', 'o', 'p'}},
       {{'m', 'i', 'e', 'a'},
        {'n', 'j', 'f', 'b'},
        {'o', 'k', 'g', 'c'},
        {'p', 'l', 'h', 'd'}}}};

  for (auto test_image : test_images) {
    rotate(std::get<0>(test_image));

    ASSERT_EQ(std::get<0>(test_image), std::get<1>(test_image));
  }
}

TEST(CciChapter1_Q7, setZero) {
  std::vector<std::tuple<matrix, matrix>> test_matrices = {
      {{}, {}},
      {{{1, 1}, {0, 1}}, {{0, 1}, {0, 0}}},
      {{{1, 1, 1}, {0, 0, 1}, {1, 1, 1}}, {{0, 0, 1}, {0, 0, 0}, {0, 0, 1}}},
      {{{1, 1, 1, 1, 1},
        {1, 0, 1, 0, 1},
        {1, 0, 1, 1, 1},
        {0, 1, 1, 1, 1},
        {0, 0, 1, 1, 1}},
       {{0, 0, 1, 0, 1},
        {0, 0, 0, 0, 0},
        {0, 0, 0, 0, 0},
        {0, 0, 0, 0, 0},
        {0, 0, 0, 0, 0}}},
  };

  for (auto test_matrix : test_matrices) {
    setZeros(std::get<0>(test_matrix));

    ASSERT_EQ(std::get<0>(test_matrix), std::get<1>(test_matrix));
  }
}

TEST(CciChapter1_Q8, isRotation) {
  std::vector<std::tuple<std::string, std::string, bool>> test_strings = {
      {{}, {}, false},
      {{"Andrzej"}, {"Andrzej"}, true},
      {{"Andrzej"}, {"ejAndrz"}, true},
      {{"Andrzej"}, {"Andrzje"}, false},
  };

  for (auto &test_case : test_strings) {
    ASSERT_EQ(isRotation(std::get<0>(test_case), std::get<1>(test_case)),
              std::get<2>(test_case));
  }
}
