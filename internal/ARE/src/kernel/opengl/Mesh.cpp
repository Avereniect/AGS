//
// Created by avereniect on 1/9/22.
//
#include "Mesh.hpp"
#include <glad/glad.h>

namespace ags::are::gl43 {

    Mesh::~Mesh() {
        unload();
    }

    void load(mesh::Fixed_vertex_array_view view) {

    }

    void Mesh::unload() {
        auto tmp = get_id();
        glDeleteBuffers(1, &tmp);
    }

}
