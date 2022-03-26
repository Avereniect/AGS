cmake_minimum_required(VERSION 3.13)

add_library(AGS_ARE_GL STATIC
    ../Enums.hpp

    Kernel.hpp
    Kernel.cpp

    Shader.hpp
    Shader.cpp

    Object.hpp
    Object.cpp

    Draw_call.hpp
    Draw_call.cpp

    Mesh.hpp
    Mesh.cpp

    Mesh_kernel.hpp
    Mesh_kernel.cpp

    Render_queue.hpp
    Render_queue.cpp

    Uniform_pack.hpp
    Uniform_pack.cpp
)

target_link_libraries(AGS_ARE_GL
    PUBLIC AGS_mesh glad
    PRIVATE GL
)

set_target_properties(AGS_ARE_GL PROPERTIES LINKER_LANGUAGE CXX)
