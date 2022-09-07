//
// Created by avereniect on 3/12/22.
//
#include "Mesh.hpp"

namespace ags::are::vk_kernel {

    /*
    void Mesh::load(const ags::mesh::Fixed_vertex_array_view& mesh) {

    }
    */

    //=====================================================
    // -ctors
    //=====================================================

    Mesh::Mesh(Mesh&& mesh) noexcept:
        index_buffer(std::exchange(mesh.index_buffer, VK_NULL_HANDLE)),
        pos_buffer(std::exchange(mesh.pos_buffer, VK_NULL_HANDLE)),
        norm_buffer(std::exchange(mesh.norm_buffer, VK_NULL_HANDLE)),
        vert_count(std::exchange(mesh.vert_count, 0)) {}

    Mesh::~Mesh() {
        unload();
    }

    //=====================================================
    // Assignment operators
    //=====================================================

    Mesh& Mesh::operator=(Mesh&& mesh) noexcept {
        index_buffer = std::exchange(mesh.index_buffer, VK_NULL_HANDLE);
        pos_buffer = std::exchange(mesh.pos_buffer, VK_NULL_HANDLE);
        norm_buffer = std::exchange(mesh.norm_buffer, VK_NULL_HANDLE);
        vert_count = std::exchange(mesh.vert_count, 0);

        return *this;
    }

    //=====================================================
    // Buffer mutators
    //=====================================================

    void Mesh::load(mesh::Dynamic_vertex_array& mesh) {
        
    }

    void Mesh::unload() {

    }

    //=====================================================
    // Accessors
    //=====================================================

    std::uint32_t Mesh::vertex_count() const {
        return vert_count;
    }

}
