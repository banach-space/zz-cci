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
#include <algorithm>

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

//-----------------------------------------------------------------------------
// Tests for Solution to Q3
//-----------------------------------------------------------------------------
template <typename T> class CciChapter3_Q3 : public ::testing::Test {};

using StackTypes_Q3 =
    ::testing::Types<cci::StackOfPlatesBasic, cci::StackOfPlatesComplex>;
TYPED_TEST_CASE(CciChapter3_Q3, StackTypes_Q3);

TYPED_TEST(CciChapter3_Q3, StackOfPlates) {
  size_t k_num_of_values = 10;
  size_t k_max_substack_size = 2;

  TypeParam test_stack(k_max_substack_size);

  for (size_t ii = 0; ii < k_num_of_values; ii++) {
    test_stack.push(static_cast<int>(ii));
  }

  for (size_t ii = 0; ii < k_num_of_values; ii++) {
    int value = test_stack.pop();
    EXPECT_EQ(static_cast<int>(k_num_of_values - 1 - ii), value);
  }
}

TYPED_TEST(CciChapter3_Q3, StackOfPlatesComplex) {
  size_t k_num_of_values = 10;
  size_t k_max_substack_size = 2;

  cci::StackOfPlatesComplex test_stack(k_max_substack_size);

  for (size_t ii = 0; ii < k_num_of_values; ii++) {
    test_stack.push(static_cast<int>(ii));
  }

  // These tests are a bit verbose, sorry.
  auto value = test_stack.popAt(1);
  EXPECT_EQ(3, value);

  value = test_stack.popAt(1);
  EXPECT_EQ(4, value);

  value = test_stack.popAt(2);
  EXPECT_EQ(7, value);

  value = test_stack.popAt(2);
  EXPECT_EQ(8, value);

  value = test_stack.popAt(0);
  EXPECT_EQ(1, value);
}

//-----------------------------------------------------------------------------
// Tests for Solution to Q4
//-----------------------------------------------------------------------------
TEST(CciChapter3_Q4, HanoiTower) {
  cci::Tower towers[3];
  size_t k_num_disks = 10;

  for (size_t ii = k_num_disks; ii > 0; ii--) {
    towers[0].add(ii);
  }

  towers[0].moveDisks(k_num_disks, &towers[2], &towers[1]);

  for (size_t ii = 1; ii <= k_num_disks; ii++) {
    EXPECT_EQ(ii, towers[2].pop());
  }
}

//-----------------------------------------------------------------------------
// Tests for Solution to Q5
//-----------------------------------------------------------------------------
TEST(CciChapter3_Q5, queue_implemented_with_two_stacks) {
  cci::MyQueue test_queue;
  size_t k_num_elements = 10;

  for (size_t ii = 0; ii < k_num_elements; ii++) {
    test_queue.add(ii);
  }

  // Since this is a queue, checkc that MyQueue indeed implements a FIFO
  for (size_t ii = 0; ii < k_num_elements; ii++) {
    EXPECT_EQ(static_cast<int>(ii), test_queue.remove());
  }
}

//-----------------------------------------------------------------------------
// Tests for Solution to Q6
//-----------------------------------------------------------------------------
TEST(CciChapter3_Q6, sort_stack) {
  std::vector<std::vector<int>> test_vectors = {
    {1, 2, 3, 4, 5, 6, 7, 8, 9, 10},
    {1, 1, 1, 3, 34, 543, 44, 124, 13, 17, 10000}
  };

  for (auto &test_case : test_vectors) {
    std::stack<int> test_stack;
    for (auto item : test_case) {
      test_stack.push(item);
    }

    // Sort so that the elements are in ascending order
    std::stack<int> output_stack = cci::sort(&test_stack);
    // Do the same with the test vector (making sure that the first elements is
    // the largest, and the last is the smallest, hence the reverse iterators)
    std::sort(test_case.rbegin(), test_case.rend());

    // Since this is a queue, checkc that MyQueue indeed implements a FIFO
    for (auto item : test_case) {
      EXPECT_EQ(item, output_stack.top());
      output_stack.pop();
    }
  }
}

//-----------------------------------------------------------------------------
// Tests for Solution to Q7
//-----------------------------------------------------------------------------
TEST(CciChapter3_Q7, animal_queue) {
  cci::AnimalQueue animal_shelter;

  // Animals in the order in which they are admitted to the shelter
  std::vector<std::string> animal_names_delivered = {
    "dog", "dog", "cat", "cat", "dog", "cat", "dog"
  };

  // Animals in order which they are given away
  std::vector<std::string> animal_names_given_away(animal_names_delivered.rbegin(), animal_names_delivered.rend());

  for (auto animal_name : animal_names_delivered) {
    cci::Animal a(animal_name);
    animal_shelter.enquue(a);
  }

  for (auto animal_name : animal_names_given_away) {
    cci::Animal a = animal_shelter.dequeuAny();
    EXPECT_EQ(animal_name, a.getName());
  }

}
