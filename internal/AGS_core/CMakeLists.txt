cmake_minimum_required(VERSION 3.16)

if (${AGS_RENDER_API} STREQUAL "Vulkan10")
    set(context_source_files "src/Vulkan_context.hpp" "src/Vulkan_context.cpp")
elseif(${AGS_RENDER_API} STREQUAL "OpenGL43")
    set(context_source_files)
endif()

add_library(AGS_core STATIC
    src/Types.cpp

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
