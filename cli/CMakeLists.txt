# Copyright (C) Denys Valchuk - All Rights Reserved
# ZHZhbGNodWtAZ21haWwuY29tCg==

add_executable(carsds_cli
  main.cpp)

target_link_libraries(carsds_cli PRIVATE carsds)
