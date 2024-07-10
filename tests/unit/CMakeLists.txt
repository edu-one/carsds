# Copyright (C) Denys Valchuk - All Rights Reserved
# ZHZhbGNodWtAZ21haWwuY29tCg==

include(CMakePrintHelpers)

add_executable(carsds_test 
  carsds_test.cpp
  reduce_tests.cpp)

find_package(GTest)
target_link_libraries(carsds_test 
  PRIVATE
    carsds
    gtest::gtest)

include(GoogleTest)
gtest_discover_tests(carsds_test)
