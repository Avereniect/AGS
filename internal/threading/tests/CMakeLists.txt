cmake_minimum_required(VERSION 3.16)

add_executable(AGS_threading_tests
    Threading_tests.cpp
    Work_sharing_thread_pool_tests.hpp

    containers/Locked_queue_tests.hpp
)

target_compile_options(AGS_threading_tests PRIVATE "-fsanitize=address")
target_link_options(AGS_threading_tests PRIVATE "-fsanitize=address")
target_compile_features(AGS_threading_tests PRIVATE cxx_std_17)

target_link_libraries(AGS_threading_tests PUBLIC AGS_threading gtest)
