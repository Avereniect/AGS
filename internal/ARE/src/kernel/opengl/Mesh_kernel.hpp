//
// Created by avereniect on 1/9/22.
//

#ifndef AGS_ARE_GL_MESH_KERNEL_HPP
#define AGS_ARE_GL_MESH_KERNEL_HPP

#include <ags/Graphics_includes.hpp>

#include <cstdint>
#include <vector>

namespace ags::are::gl_kernel {

    class Mesh_kernel {
    public:

        //=================================================
        // State functions
        //=================================================

        static void init();
        static void term();

        //=================================================
        // Resource allocation
        //=================================================

        static GLuint acquire_vbo();

        static void release_vbo(GLuint id);

        static GLuint acquire_vao();

        static void release_vao(GLuint id);

        //=================================================
        // Accessors
        //=================================================

        static std::uint32_t max_vertex_attribute_count();

    private:

        //=================================================
        // Static constants
        //=================================================

        static constexpr std::uint32_t vao_garbage_size = 32;
        static constexpr std::uint32_t vao_pool_size = 32;

        static constexpr std::uint32_t vbo_garbage_size = 256;
        static constexpr std::uint32_t vbo_pool_size = 256;

        //=================================================
        // Static members
        //=================================================

        static std::vector<GLuint> vao_garbage;
        static std::vector<GLuint> vao_pool;

        static std::vector<GLuint> vbo_garbage;
        static std::vector<GLuint> vbo_pool;

    };

}

#endif //AGS_ARE_GL_MESH_KERNEL_HPP
