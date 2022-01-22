cmake_minimum_required(VERSION 3.13)

add_library(AGS_ARE_GL STATIC
    ../Enums.hpp

    Kernel.hpp
    Kernel.cpp
)

target_link_libraries(AGS_ARE_GL PUBLIC gl)
set_target_properties(AGS_ARE_GL PROPERTIES LINKER_LANGUAGE CXX)
