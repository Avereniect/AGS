cmake_minimum_required(VERSION 3.13)

option(AGS_ARE_VULKAN_DEBUG OFF)

add_library(AGS_ARE_VULKAN STATIC
    ../Enums_common.hpp
    ../Enums_common.cpp

    ../Framebuffer_common.hpp

    Kernel.hpp
    Kernel.cpp

    Kernel_base.hpp
    Kernel_base.cpp

    Device.hpp
    Device.cpp

    Device_kernel.hpp
    Device_kernel.cpp

    Draw_call.hpp
    Draw_call.cpp

    Shader_kernel.hpp
    Shader_kernel.cpp

    Shader.hpp
    Shader.cpp

    Mesh_kernel.hpp
    Mesh_kernel.cpp

    Mesh.hpp
    Mesh.cpp

    Texture.hpp
    Texture.cpp

    Texture_kernel.hpp
    Texture_kernel.cpp
)

target_link_libraries(AGS_ARE_VULKAN
    PUBLIC AGS_mesh
    PRIVATE vulkan shaderc spirv-reflect-static
)

if (AGS_ARE_VULKAN_DEBUG)
    target_compile_definitions(AGS_ARE_VULKAN
        PRIVATE AGS_ARE_VULKAN_DEBUG
    )
endif()

target_compile_definitions(AGS_ARE_VULKAN
    PRIVATE AGS_MODULE_NAME="AGS_ARE_VULKAN"
)

set_target_properties(AGS_ARE_VULKAN PROPERTIES LINKER_LANGUAGE CXX)
