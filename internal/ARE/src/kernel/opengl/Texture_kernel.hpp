//
// Created by avereniect on 4/30/22.
//

#ifndef AGS_ARE_GL_TEXTURE_KERNEL_HPP
#define AGS_ARE_GL_TEXTURE_KERNEL_HPP

#include <ags/Graphics_includes.hpp>

#include "Kernel_base.hpp"

#include <vector>

namespace ags::are::gl_kernel {

    class Texture_kernel : public Kernel_base {
    public:

        //=================================================
        // State functions
        //=================================================

        static void init();
        static void term();

        //=================================================
        // Mutators
        //=================================================

        static void clean_up();

        //=================================================
        // Accessors
        //=================================================

        [[nodiscard]]
        static std::uint32_t max_3d_image_size();

        [[nodiscard]]
        static std::uint32_t max_2d_image_size();

        [[nodiscard]]
        static std::uint32_t max_1d_image_size();

        //=================================================
        // Resource functions
        //=================================================

        static GLuint acquire_texture();

        static void release_texture(GLuint);

    private:

        //=================================================
        // Static members
        //=================================================

        static constexpr std::uint32_t texture_pool_reservation_size = 32;
        static constexpr std::uint32_t texture_garbage_reservation_size = 32;

        static std::vector<GLuint> bound_textures;

        static std::vector<GLuint> texture_pool;
        static std::vector<GLuint> texture_garbage;

        static GLint max_1d_texture_dim;
        static GLint max_2d_texture_dim;
        static GLint max_3d_texture_dim;

        static GLuint active_texture_slot;

    };

}

#endif //AGS_ARE_GL_TEXTURE_KERNEL_HPP
