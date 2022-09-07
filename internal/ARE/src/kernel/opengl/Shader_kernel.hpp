//
// Created by avereniect on 4/30/22.
//

#ifndef AGS_ARE_GL_SHADER_KERNEL_HPP
#define AGS_ARE_GL_SHADER_KERNEL_HPP

#include <ags/Graphics_includes.hpp>

#include "Kernel_base.hpp"

#include <array>

namespace ags::are::gl_kernel {

    class Shader_kernel : public Kernel_base {
    public:

        //=================================================
        // State methods
        //=================================================

        static void init();
        static void term();

        //=================================================
        // State mutators
        //=================================================

        static GLuint acquire_vertex_shader();
        static void release_vertex_shader(GLuint);

        static GLuint acquire_fragment_shader();
        static void release_fragment_shader(GLuint);

        static GLuint acquire_shader_program();
        static void release_shader_program(GLuint);

        static GLuint acquire_compute_shader();
        static void release_compute_shader(GLuint);

        //=================================================
        // Accessors
        //=================================================

        //[[nodiscard]]
        //static std::array<std::uint32_t, 3> max_workgroup_dims();

    private:

        //=================================================
        // Static members
        //=================================================

        static std::array<std::uint32_t, 3> max_workgroup_counts;
        static std::array<std::uint32_t, 3> max_workgroup_sizes;
        static std::uint32_t max_workgroup_invocations;

    };

}

#endif //AGS_ARE_GL_SHADER_KERNEL_HPP
