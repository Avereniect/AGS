cmake_minimum_required(VERSION 3.16)

add_executable(APT_TESTS
    ./APT_tests.cpp

    ./Instersection_tests.hpp
    ./LBVH8_tests.hpp
)

target_include_directories(APT_TESTS PRIVATE ../src/)

target_link_libraries(APT_TESTS PRIVATE APT gtest)
