//========================================================================
// FILE:
//  test/tests-ch5.cpp
//
// AUTHOR:
//  banach-space@github
//
// DESCRIPTION:
//    Unit tests for solutions to practice questions from Chapter 5 in [1]
//
//    [1] "Cracking the Coding Interview", Gayle Laakmann McDowell
//
// License: Apache License 2.0
//========================================================================
#include <gtest/gtest.h>

#include <vector>

#include <chapter_5.hpp>

//-----------------------------------------------------------------------------
// Tests for Solution to Q1
//-----------------------------------------------------------------------------
TEST(CciChapter5_Q1, test_with_shift_all_zeros) {
  // Loop over all possible positions in a 32 bit integer
  for (size_t ii = 0; ii < 32; ii++) {
    uint32_t n = 0x0;
    uint32_t m = 0x1;
    size_t i = ii;
    size_t j = ii;
    uint32_t expected_output = m << ii;

    uint32_t result = cci::updateBits(n, m, i, j);
    EXPECT_EQ(result, expected_output);
  }
}

TEST(CciChapter5_Q1, test_with_shift_all_ones) {
  // Loop over all possible positions in a 32 bit integer
  for (size_t ii = 31; ii < 32; ii++) {
    uint32_t n = ~0u;
    uint32_t m = 0u;
    size_t i = ii;
    size_t j = ii;
    uint32_t expected_output = ~(1u << ii);

    unsigned result = cci::updateBits(n, m, i, j);
    EXPECT_EQ(result, expected_output) << result;
  }
}

TEST(CciChapter5_Q1, basic_test) {
  // n, m, i, j, expected output
  std::vector<std::tuple<uint32_t, uint32_t, size_t, size_t, uint32_t>>
      test_cases = {
          {0xdeadbeef, 0x0, 0, 0, 0xdeadbeee},
          {0xdeadbeef, 0x1, 4, 4, 0xdeadbeff},
      };

  for (auto &test_case : test_cases) {
    uint32_t result =
        cci::updateBits(std::get<0>(test_case), std::get<1>(test_case),
                        std::get<2>(test_case), std::get<3>(test_case));
    EXPECT_EQ(result, std::get<4>(test_case));
  }
}

//-----------------------------------------------------------------------------
// Tests for Solution to Q2
//-----------------------------------------------------------------------------
TEST(CciChapter5_Q2, basic_test){
    // number, binary representation
    std::vector<std::tuple<double, std::vector<int>>> test_cases =
        {{0.625, {1, 0, 1}},
         {0.5, {1}},
         {0.25, {0, 1}},
         // The following ones were calculated in python
         {0.9999847412109375,
         {1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1}},
         {0.9999999997671694,
         {1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1,
          1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1}},
};

for (auto &test_case : test_cases) {
  auto result = cci::printBinary(std::get<0>(test_case));
  EXPECT_EQ(result, std::get<1>(test_case));
  }
}
