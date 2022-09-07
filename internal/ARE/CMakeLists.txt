cmake_minimum_required(VERSION 3.13)

option(AGS_ARE_DEBUG OFF)

add_library(AGS_ARE STATIC
    src/ARE.hpp
    src/ARE.cpp
)

if(AGS_USE_OPENGL)
    set(ARE_RENDER_LIBRARY "AGS_ARE_OPENGL")
    add_subdirectory(src/kernel/opengl/)
    target_compile_definitions(AGS_ARE PRIVATE AGS_ARE_OPENGL)
endif()

if (AGS_USE_VULKAN)
    set(ARE_RENDER_LIBRARY "AGS_ARE_VULKAN")
    add_subdirectory(src/kernel/vulkan/)
    target_compile_definitions(AGS_ARE PRIVATE AGS_ARE_VULKAN)
endif()



if (AGS_ARE_DEBUG)
    target_compile_definitions(AGS_ARE PRIVATE AGS_ARE_DEBUG)

    if(AGS_USE_OPENGL)
        set(AGS_ARE_OPENGL_DEBUG ON)
    endif()

    if (AGS_USE_VULKAN)
        set(AGS_ARE_VULKAN_DEBUG ON)
    endif()
endif()



target_link_libraries(AGS_ARE
    PUBLIC ${ARE_RENDER_LIBRARY} AGS_mesh
)

target_compile_definitions(AGS_ARE
    PRIVATE AGS_MODULE_NAME="AGS_ARE"
)

target_include_directories(AGS_ARE PUBLIC ./include/ ../../external/)
