//========================================================================
// FILE:
//  test/tests-ch3.cpp
//
// AUTHOR:
//  banach-space@github
//
// DESCRIPTION:
//    Unit tests for solutions to practice questions from Chapter 3 in [1]
//
//    [1] "Cracking the Coding Interview", Gayle Laakmann McDowell
//
// License: Apache License 2.0
//========================================================================
#include <gtest/gtest.h>

#include <numeric>
#include <vector>

#include <chapter_3.hpp>

//-----------------------------------------------------------------------------
// Tests for Solutions to Q1
//-----------------------------------------------------------------------------
template <typename T> class CciChapter3_Q1 : public ::testing::Test {};

using StackTypes_Q1 = ::testing::Types<cci::SimpleMultiStack, cci::MultiStack>;
TYPED_TEST_CASE(CciChapter3_Q1, StackTypes_Q1);

TYPED_TEST(CciChapter3_Q1, push_and_pop) {
  // These are arbitrary
  const size_t k_num_substacks = 7;
  const size_t k_substack_size = 7;

  // The values for each substack
  std::vector<int> stack_vals(k_substack_size);
  std::iota(stack_vals.begin(), stack_vals.end(), 0);

  TypeParam test_stack(k_substack_size, k_num_substacks);

  for (size_t ii = 0u; ii < k_num_substacks; ii++) {
    for (auto item : stack_vals) {
      test_stack.push(ii, item);
    }
  }

  for (size_t ii = 0u; ii < k_num_substacks; ii++) {
    std::vector<int> current_stack_vector{};

    while (!test_stack.isEmpty(ii)) {
      current_stack_vector.insert(current_stack_vector.begin(),
                                  test_stack.pop(ii));
    }
    EXPECT_EQ(current_stack_vector, stack_vals);
  }
}

TYPED_TEST(CciChapter3_Q1, push_and_peek) {
  const size_t k_num_substacks = 7;
  const size_t k_substack_size = 7;

  // The values for each substack
  std::vector<int> stack_vals(k_substack_size);
  std::iota(stack_vals.begin(), stack_vals.end(), 0);

  TypeParam test_stack(k_substack_size, k_num_substacks);

  for (size_t ii = 0u; ii < k_num_substacks; ii++) {
    for (auto item : stack_vals) {
      test_stack.push(ii, item);
    }
  }

  for (size_t ii = 0u; ii < k_num_substacks; ii++) {
    // "peek" doesn't change the state of the stack, so doing it twice should
    // give identical result
    EXPECT_EQ(*(--stack_vals.end()), test_stack.peek(ii));
    EXPECT_EQ(*(--stack_vals.end()), test_stack.peek(ii));
  }
}

TYPED_TEST(CciChapter3_Q1, push_out_of_range) {
  const size_t k_stack_val = 1;
  const size_t k_num_substacks = 1;
  const size_t k_substack_size = 1;

  TypeParam test_stack(k_substack_size, k_num_substacks);

  test_stack.push(0, k_stack_val);

  try {
    test_stack.push(0, k_stack_val);
  } catch (std::out_of_range const &err) {
    EXPECT_EQ(err.what(), std::string("Reached the capacity of the stack"));
  } catch (...) {
    FAIL() << "Expected std::out_of_range";
  }
}

TEST(CciChapter3_Q1, SimpleMultiStack_push_out_of_range) {
  const size_t k_stack_val = 1;
  const size_t k_num_substacks = 2;
  const size_t k_substack_size = 1;

  cci::MultiStack test_stack(k_substack_size, k_num_substacks);

  test_stack.push(0, k_stack_val);

  try {
    test_stack.push(0, k_stack_val);
  } catch (std::out_of_range const &err) {
    EXPECT_EQ(err.what(), std::string("Reached the capacity of the stack"));
  } catch (...) {
    FAIL() << "Expected std::out_of_range";
  }
}

TEST(CciChapter3_Q1, MultiStack_push_out_of_range) {
  const size_t k_stack_val = 1;
  const size_t k_num_substacks = 2;
  const size_t k_substack_size = 1;

  cci::MultiStack test_stack(k_substack_size, k_num_substacks);

  test_stack.push(0, k_stack_val);
  test_stack.push(0, k_stack_val);

  try {
    test_stack.push(0, k_stack_val);
  } catch (std::out_of_range const &err) {
    EXPECT_EQ(err.what(), std::string("Reached the capacity of the stack"));
  } catch (...) {
    FAIL() << "Expected std::out_of_range";
  }
}

TYPED_TEST(CciChapter3_Q1, empty) {
  const size_t k_num_substacks = 100;
  const size_t k_substack_size = 1;

  TypeParam test_stack(k_substack_size, k_num_substacks);

  for (size_t ii = 0u; ii < k_num_substacks; ii++) {
    EXPECT_TRUE(test_stack.isEmpty(ii));
  }
}

TYPED_TEST(CciChapter3_Q1, pop_out_of_range) {
  const size_t k_num_substacks = 1;
  const size_t k_substack_size = 1;

  TypeParam test_stack(k_substack_size, k_num_substacks);

  try {
    test_stack.pop(0);
  } catch (std::out_of_range const &err) {
    EXPECT_EQ(err.what(), std::string("Empty stack"));
    return;
  } catch (...) {
    FAIL() << "Expected std::out_of_range";
  }

  FAIL() << "Expected an exception";
}

//-----------------------------------------------------------------------------
// Tests for Solution to Q2
//-----------------------------------------------------------------------------
TEST(CciChapter3_Q2, StackWithMin) {
  const int k_stack_min = 7;
  const size_t k_num_elements = 20;

  cci::StackWithMin test_stack;

  test_stack.push(k_stack_min);

  // Populate the stack with values greater than k_stack_min
  for (size_t ii = 0; ii < k_num_elements; ii++) {
    test_stack.push(ii + k_stack_min);
  }

  // Remove all elements from the stack and at every step verify that min
  // remains min
  for (size_t ii = 0; ii << k_num_elements; ii++) {
    EXPECT_EQ(test_stack.min(), k_stack_min);
    test_stack.pop();
  }

}
