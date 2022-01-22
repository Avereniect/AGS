cmake_minimum_required(VERSION 3.16)

add_library(AGS_core STATIC
    src/Types.cpp

    src/Core.hpp
    src/Core.cpp

    src/Vulkan_context.hpp
    src/Vulkan_context.cpp

    src/Windowing_context.hpp
    src/Windowing_context.cpp
)

target_compile_features(AGS_core PRIVATE cxx_std_17)

target_link_libraries(AGS_core AUL AVML glfw)

target_include_directories(AGS_core
    PUBLIC
    ../../external/half-2.2.0/include/
    ./include/
)
