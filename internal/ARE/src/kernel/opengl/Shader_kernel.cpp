//
// Created by avereniect on 4/30/22.
//
#include "Shader_kernel.hpp"

#include <thread>

namespace ags::are::gl_kernel {

    //=====================================================
    // Static members
    //=====================================================

    std::array<std::uint32_t, 3> Shader_kernel::max_workgroup_counts{0, 0, 0};
    std::array<std::uint32_t, 3> Shader_kernel::max_workgroup_sizes{0, 0, 0};
    std::uint32_t Shader_kernel::max_workgroup_invocations = 0;

    //=====================================================
    // State methods
    //=====================================================

    void Shader_kernel::init() {
        GLint work_group_count_limits[3];
        glGetIntegeri_v(GL_MAX_COMPUTE_WORK_GROUP_COUNT, 0, work_group_count_limits);
        glGetIntegeri_v(GL_MAX_COMPUTE_WORK_GROUP_COUNT, 1, work_group_count_limits);
        glGetIntegeri_v(GL_MAX_COMPUTE_WORK_GROUP_COUNT, 2, work_group_count_limits);
        max_workgroup_counts[0] = work_group_count_limits[0];
        max_workgroup_counts[1] = work_group_count_limits[1];
        max_workgroup_counts[2] = work_group_count_limits[2];

        GLint work_group_size_limits[3];
        glGetIntegeri_v(GL_MAX_COMPUTE_WORK_GROUP_SIZE, 0, work_group_count_limits);
        glGetIntegeri_v(GL_MAX_COMPUTE_WORK_GROUP_SIZE, 1, work_group_count_limits);
        glGetIntegeri_v(GL_MAX_COMPUTE_WORK_GROUP_SIZE, 2, work_group_count_limits);
        max_workgroup_sizes[0] = work_group_size_limits[0];
        max_workgroup_sizes[1] = work_group_size_limits[1];
        max_workgroup_sizes[2] = work_group_size_limits[2];

        GLint work_group_invocation_limit;
        glGetIntegerv(GL_MAX_COMPUTE_WORK_GROUP_INVOCATIONS, &work_group_invocation_limit);
        max_workgroup_invocations = work_group_invocation_limit;
    }

    void Shader_kernel::term() {

    }

    //=====================================================
    // State mutators
    //=====================================================

    GLuint Shader_kernel::acquire_vertex_shader() {
        return glCreateShader(GL_VERTEX_SHADER);
    }

    void Shader_kernel::release_vertex_shader(GLuint id) {
        glDeleteShader(id);
    }

    GLuint Shader_kernel::acquire_fragment_shader() {
        return glCreateShader(GL_FRAGMENT_SHADER);
    }

    void Shader_kernel::release_fragment_shader(GLuint id) {
        glDeleteShader(id);
    }

    GLuint Shader_kernel::acquire_shader_program() {
        return glCreateProgram();
    }

    void Shader_kernel::release_shader_program(GLuint id) {
        glDeleteProgram(id);
    }

    GLuint Shader_kernel::acquire_compute_shader() {
        return glCreateShader(GL_COMPUTE_SHADER);
    }

    void Shader_kernel::release_compute_shader(GLuint id) {
        glDeleteShader(id);
    }

}
