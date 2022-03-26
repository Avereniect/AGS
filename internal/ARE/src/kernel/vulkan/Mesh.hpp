//
// Created by avereniect on 3/12/22.
//

#ifndef AGS_ARE_VK10_MESH_HPP
#define AGS_ARE_VK10_MESH_HPP

#include "Includes.hpp"

#include <ags/Mesh.hpp>
#include <cstdint>

namespace ags::are::vk10 {

    class Mesh {
    public:

        //=================================================
        // -ctors
        //=================================================

        Mesh();
        Mesh(Mesh&&) noexcept;
        ~Mesh();

        //=================================================
        // Assignment operators
        //=================================================

        Mesh& operator=(Mesh&&) noexcept;

        //=================================================
        // Buffer mutators
        //=================================================

        void load(const ags::mesh::Fixed_vertex_array_view& mesh);

    private:

        //=================================================
        // Instance members
        //=================================================

        vk::Buffer index_buffer;
        vk::Buffer pos_buffer;
        vk::Buffer norm_buffer;

    };

}

#endif //AGS_ARE_VK10_MESH_HPP
