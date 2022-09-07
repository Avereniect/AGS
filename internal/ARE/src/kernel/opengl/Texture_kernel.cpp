//
// Created by avereniect on 5/1/22.
//
#include "Texture_kernel.hpp"

#include <algorithm>

namespace ags::are::gl_kernel {

    //=================================================
    // Static members
    //=================================================

    std::vector<GLuint> Texture_kernel::bound_textures;

    std::vector<GLuint> Texture_kernel::texture_pool{};
    std::vector<GLuint> Texture_kernel::texture_garbage{};

    GLint Texture_kernel::max_1d_texture_dim = 0;
    GLint Texture_kernel::max_2d_texture_dim = 0;
    GLint Texture_kernel::max_3d_texture_dim = 0;

    GLuint Texture_kernel::active_texture_slot = 0;

    //=================================================
    // State functions
    //=================================================

    void Texture_kernel::init() {
        GLint max_frag_textures;
        GLint max_vert_textures;
        GLint max_combined_textures;

        glGetIntegerv(GL_MAX_TEXTURE_IMAGE_UNITS, &max_frag_textures);
        glGetIntegerv(GL_MAX_VERTEX_TEXTURE_IMAGE_UNITS, &max_vert_textures);
        glGetIntegerv(GL_MAX_COMBINED_TEXTURE_IMAGE_UNITS, &max_combined_textures);

        GLint max_textures = std::min(max_frag_textures, std::min(max_vert_textures, max_combined_textures));
        bound_textures.resize(max_textures);

        glGetIntegerv(GL_MAX_3D_TEXTURE_SIZE, &max_3d_texture_dim);
        glGetIntegerv(GL_MAX_TEXTURE_SIZE, &max_2d_texture_dim);
        glGetIntegerv(GL_MAX_TEXTURE_SIZE, &max_1d_texture_dim);
    }

    void Texture_kernel::term() {
        clean_up();

        glDeleteTextures(texture_pool.size(), texture_pool.data());
    }

    void Texture_kernel::clean_up() {
        glDeleteBuffers(texture_garbage.size(), texture_garbage.data());
        texture_garbage.clear();
    }

    //=================================================
    // Mutators
    //=================================================

    //=====================================================
    // Resource functions
    //=====================================================

    GLuint Texture_kernel::acquire_texture() {
        if (texture_pool.empty()) {
            texture_pool.resize(texture_pool_reservation_size);
            glGenTextures(texture_pool_reservation_size, texture_pool.data());
        }

        auto ret = texture_pool.back();
        texture_pool.pop_back();
        return ret;
    }

    void Texture_kernel::release_texture(GLuint id) {
        texture_garbage.push_back(id);
        if (texture_garbage.size() == texture_garbage_reservation_size) {
            clean_up();
        }
    }

}
