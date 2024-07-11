# Copyright (C) Denys Valchuk - All Rights Reserved
# ZHZhbGNodWtAZ21haWwuY29tCg==

include(CMakePrintHelpers)

add_executable(carsds_test 
  process_tests.cpp
  reduce_tests.cpp)

find_package(GTest)
target_link_libraries(carsds_test 
  PRIVATE
    carsds
    gtest::gtest)

target_compile_definitions(carsds_test PRIVATE DV_RESOURCES_DIR="${PROJECT_SOURCE_DIR}/resources")

include(GoogleTest)
gtest_discover_tests(carsds_test)
