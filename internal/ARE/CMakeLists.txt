cmake_minimum_required(VERSION 3.13)

add_subdirectory(src/kernel/vulkan)

add_library(AGS_ARE STATIC
    src/ARE.hpp
    src/ARE.cpp
)

if (${AGS_RENDER_API} STREQUAL "Vulkan10")
    set(ARE_RENDER_LIBRARY "AGS_ARE_VK")
else()
    message(FATAL_ERROR "No rendering API selected")
endif()

target_link_libraries(AGS_ARE PRIVATE glad AGS_mesh ${ARE_RENDER_LIBRARY})

target_include_directories(AGS_ARE PUBLIC ./include/ ../../external/)
