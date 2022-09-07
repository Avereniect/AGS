cmake_minimum_required(VERSION 3.14)

add_executable(AGS_image_tests EXCLUDE_FROM_ALL
    Image_tests.cpp

    Pixel_buffer_tests.hpp
)

target_link_libraries(AGS_image_tests AGS_image)
