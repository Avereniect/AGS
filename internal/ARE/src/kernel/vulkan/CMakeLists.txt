cmake_minimum_required(VERSION 3.13)

add_library(AGS_ARE_VK STATIC
    ../Enums.hpp

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
)

target_link_libraries(AGS_ARE_VK
    PUBLIC AGS_mesh
    PRIVATE vulkan shaderc spirv-reflect-static
)

set_target_properties(AGS_ARE_VK
    PROPERTIES
    CXX_VISIBILITY_PRESET hidden
)

set_target_properties(AGS_ARE_VK PROPERTIES LINKER_LANGUAGE CXX)
