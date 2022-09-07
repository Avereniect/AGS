//
// Created by avereniect on 5/7/22.
//

#ifndef AGS_ARE_GL_COMPUTE_QUEUE_HPP
#define AGS_ARE_GL_COMPUTE_QUEUE_HPP

#include <ags/Graphics_includes.hpp>
#include "Shader.hpp"

#include <cstdint>
#include <vector>

namespace ags::are::gl_kernel {

    struct Compute_call {
        GLuint shader_id = 0;
        std::uint32_t x = 1;
        std::uint32_t y = 1;
        std::uint32_t z = 1;
    };

    class Compute_queue {
    public:

        //=================================================
        // -ctors
        //=================================================

        Compute_queue() = default;
        ~Compute_queue() = default;

        //=================================================
        // Assignment operators
        //=================================================

        Compute_queue& operator=(const Compute_queue&) = delete;

        //=================================================
        // Element mutators
        //=================================================

        void enqueue(const Compute_shader& shader, std::uint32_t x);

        void enqueue(const Compute_shader& shader, std::uint32_t x, std::uint32_t y);

        void enqueue(const Compute_shader& shader, std::uint32_t x, std::uint32_t y, std::uint32_t z);

    private:

        //=================================================
        // Instance members
        //=================================================

        std::vector<Compute_call> queue;

    };

}

#endif //AGS_ARE_GL_COMPUTE_QUEUE_HPP
