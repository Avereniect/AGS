//
// Created by avereniect on 5/7/22.
//
#include "Compute_queue.hpp"

namespace ags::are::gl_kernel {

    void Compute_queue::enqueue(const Compute_shader& shader, std::uint32_t x) {
        enqueue(shader, x, 1, 1);
    }

    void Compute_queue::enqueue(const Compute_shader& shader, std::uint32_t x, std::uint32_t y) {
        enqueue(shader, x, y, 1);
    }

    void Compute_queue::enqueue(const Compute_shader& shader, std::uint32_t x, std::uint32_t y, std::uint32_t z) {
        queue.push_back(Compute_call{shader, x, y, z});
    }

}
