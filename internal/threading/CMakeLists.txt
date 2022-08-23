cmake_minimum_required(VERSION 3.16)

option(AGS_THREADING_BUILD_TESTS OFF)

add_library(AGS_threading STATIC
    src/Work_sharing_thread_pool.hpp
    src/Work_sharing_thread_pool.cpp
)

target_compile_definitions(AGS_threading
    PRIVATE AGS_MODULE_NAME=AGS_THREADING
)

target_link_libraries(AGS_threading PRIVATE AGS_core)

target_include_directories(AGS_threading PUBLIC ./include/)

if (AGS_THREADING_BUILD_TESTS)
    add_executable(AGS_THREADING_TESTS
        tests/Threading_tests.cpp

        tests/Work_sharing_thread_pool_tests.hpp
    )

    target_compile_options(AGS_THREADING_TESTS PRIVATE) #"-fsanitize=address")
    target_link_options(AGS_THREADING_TESTS PRIVATE) #"-fsanitize=address")
    target_compile_features(AGS_THREADING_TESTS PRIVATE cxx_std_17)

    target_link_libraries(AGS_THREADING_TESTS PUBLIC AGS_threading gtest AUL)
endif()
