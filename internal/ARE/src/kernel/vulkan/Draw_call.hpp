//
// Created by avereniect on 1/13/22.
//

#ifndef AGS_ARE_VK_DRAW_CALL_HPP
#define AGS_ARE_VK_DRAW_CALL_HPP

#include <ags/Graphics_includes.hpp>

#include "Mesh.hpp"
#include "Shader.hpp"
#include "Framebuffer.hpp"

namespace ags::are::vk_kernel {

    struct Draw_call {

        //=================================================
        // -ctors
        //=================================================

        //=================================================
        // Assignment operators
        //=================================================

        //=================================================
        // Comparison operators
        //=================================================

        //=================================================
        // Instance members
        //=================================================

        VkBuffer mesh_buffer;
        std::uint32_t mesh_offset;

        VkPipeline pipeline;

    };

}

#endif //AGS_ARE_VK_DRAW_CALL_HPP
