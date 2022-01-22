cmake_minimum_required(VERSION 3.13)

add_library(AGS_ARE_VK STATIC
    ../Enums.hpp

    Kernel.hpp
    Kernel.cpp
    Kernel_base.cpp
    Kernel_base.hpp
    Draw_call.hpp
    Draw_call.cpp
)

target_link_libraries(AGS_ARE_VK PUBLIC vulkan)
set_target_properties(AGS_ARE_VK PROPERTIES LINKER_LANGUAGE CXX)
