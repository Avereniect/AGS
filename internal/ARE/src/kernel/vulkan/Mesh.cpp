//
// Created by avereniect on 3/12/22.
//
#include "Mesh.hpp"

namespace ags::are::vk10 {

    void Mesh::load(const ags::mesh::Fixed_vertex_array_view& mesh) {

    }

    //=====================================================
    // Accessors
    //=====================================================

    std::uint32_t Mesh::vertex_count() const {
        return vert_count;
    }

}
