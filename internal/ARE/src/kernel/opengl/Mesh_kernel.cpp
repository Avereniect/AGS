//
// Created by avereniect on 1/9/22.
//
#include "Mesh_kernel.hpp"

namespace ags::are::gl43 {

    std::vector<GLuint> Mesh_kernel::mesh_garbage{};
    std::vector<GLuint> Mesh_kernel::mesh_pool{};

    void Mesh_kernel::init() {

    }

    void Mesh_kernel::term() {
        for (auto id : mesh_garbage) {

        }
    }

}
