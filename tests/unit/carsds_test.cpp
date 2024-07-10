/* Copyright (C) Denys Valchuk - All Rights Reserved
 * ZHZhbGNodWtAZ21haWwuY29tCg==
 */

#include <carsds.h>
#include <gtest/gtest.h>

TEST(FactorialTest, Zero) {
  EXPECT_EQ(1, dv::carsds::factorial(0));
}

TEST(FactorialTest, Positive) {
  EXPECT_EQ(1, dv::carsds::factorial(1));
  EXPECT_EQ(2, dv::carsds::factorial(2));
  EXPECT_EQ(6, dv::carsds::factorial(3));
  EXPECT_EQ(40320, dv::carsds::factorial(8));
}

TEST(FactorialTest, Negative) {
  EXPECT_THROW(dv::carsds::factorial(-1), std::invalid_argument);
}
