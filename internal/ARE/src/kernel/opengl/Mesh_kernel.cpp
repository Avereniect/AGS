//
// Created by avereniect on 1/9/22.
//
#include "Mesh_kernel.hpp"

namespace ags::are::gl_kernel {

    //=====================================================
    // Static members
    //=====================================================

    std::vector<GLuint> Mesh_kernel::vao_garbage{};
    std::vector<GLuint> Mesh_kernel::vao_pool{};

    std::vector<GLuint> Mesh_kernel::vbo_garbage{};
    std::vector<GLuint> Mesh_kernel::vbo_pool{};

    //=====================================================
    // State functions
    //=====================================================

    void Mesh_kernel::init() {
        //Reserve space for pools and garbage
        vao_pool.reserve(vao_pool_size);
        vao_garbage.reserve(vao_garbage_size);

        vbo_pool.reserve(vbo_pool_size);
        vbo_garbage.reserve(vbo_garbage_size);
    }

    void Mesh_kernel::term() {
        //TODO: Clear out pools and garbage
    }

    //=====================================================
    // Resource allocation
    //=====================================================

    GLuint Mesh_kernel::acquire_vao() {
        if (vao_pool.empty()) {
            vao_pool.resize(vao_pool_size);
            glGenVertexArrays(vao_pool_size, vao_pool.data());
        }

        GLuint ret = vao_pool.back();
        vao_pool.pop_back();
        return ret;
    }

    void Mesh_kernel::release_vao(GLuint id) {
        vao_garbage.emplace_back(id);

        if (vao_garbage.size() == vao_garbage_size) {
            vao_garbage.resize(0);
            glDeleteVertexArrays(vao_garbage_size, vao_pool.data());
        }
    }

    GLuint Mesh_kernel::acquire_vbo() {
        if (vbo_pool.empty()) {
            vbo_pool.resize(vbo_pool_size);
            glGenBuffers(vbo_pool_size, vbo_pool.data());
        }

        GLuint ret = vbo_pool.back();
        vbo_pool.pop_back();
        return ret;
    }

    void Mesh_kernel::release_vbo(GLuint id) {
        vbo_garbage.emplace_back(id);

        if (vbo_garbage.size() == vbo_garbage_size) {
            vbo_garbage.resize(0);
            glDeleteBuffers(vbo_garbage_size, vbo_garbage.data());
        }
    }

    //=====================================================
    // Accessors
    //=====================================================

    std::uint32_t Mesh_kernel::max_vertex_attribute_count() {
        GLint ret;
        glGetIntegerv(GL_MAX_VERTEX_ATTRIBS, &ret);
        return static_cast<std::uint32_t>(ret);
    }


}
