cmake_minimum_required(VERSION 3.16)

option(AGS_ARE_OPENGL_DEBUG OFF)

add_library(AGS_ARE_OPENGL STATIC
    ../Enums_common.hpp
    ../Enums_common.cpp

    ../Framebuffer_common.hpp

    Enums.hpp
    Enums.cpp

    Object.hpp
    Object.cpp

    Kernel.hpp
    Kernel.cpp

    Kernel_base.hpp
    Kernel_base.cpp

    Uniform_pack.hpp
    Uniform_pack.cpp

    Draw_call.hpp
    Draw_call.cpp

    Render_queue.hpp
    Render_queue.cpp

    Compute_queue.hpp
    Compute_queue.cpp

    Shader_kernel.hpp
    Shader_kernel.cpp

    Shader.hpp
    Shader.cpp

    Mesh.hpp
    Mesh.cpp

    Mesh_kernel.hpp
    Mesh_kernel.cpp

    Texture_kernel.cpp
    Texture_kernel.hpp

    Texture.cpp
    Texture.hpp

    Framebuffer_kernel.hpp
    Framebuffer_kernel.cpp

    Framebuffer.hpp
    Framebuffer.cpp
)

target_link_libraries(AGS_ARE_OPENGL
    PUBLIC AGS_core AGS_mesh GL
)

if (AGS_ARE_OPENGL_DEBUG)
    target_compile_definitions(AGS_ARE_OPENGL
        PRIVATE AGS_ARE_GL_DEBUG
    )
endif()

target_compile_definitions(AGS_ARE_OPENGL
    PRIVATE AGS_MODULE_NAME="AGS_ARE_GL"
)

set_target_properties(AGS_ARE_OPENGL PROPERTIES LINKER_LANGUAGE CXX)
