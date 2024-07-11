# Copyright (C) Denys Valchuk - All Rights Reserved
# ZHZhbGNodWtAZ21haWwuY29tCg==

cmake_minimum_required(VERSION 3.23)

project(carsds VERSION 0.0.1 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)

option(WITH_TESTS "build tests?" ON)

add_library(carsds
  src/carsprocessor.cpp
  src/CountResult.cpp)
target_include_directories(carsds PUBLIC include)

find_package(vincentlaucsb-csv-parser)
find_package(nlohmann_json)
find_package(magic_enum)

target_link_libraries(carsds 
  PRIVATE
    vincentlaucsb-csv-parser::vincentlaucsb-csv-parser
  PUBLIC
    magic_enum::magic_enum
    nlohmann_json::nlohmann_json)

if(WITH_TESTS)
  list(APPEND CMAKE_CTEST_ARGUMENTS "--output-on-failure")
  enable_testing()
  add_subdirectory(tests)
endif()
