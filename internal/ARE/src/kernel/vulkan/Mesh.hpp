//
// Created by avereniect on 3/12/22.
//

#ifndef AGS_ARE_VK_MESH_HPP
#define AGS_ARE_VK_MESH_HPP

#include <ags/Graphics_includes.hpp>

#include <ags/Mesh.hpp>
#include <cstdint>

namespace ags::are::vk_kernel {

    class Mesh {
    public:

        //=================================================
        // -ctors
        //=================================================

        Mesh() = default;
        Mesh(const Mesh&) = delete;
        Mesh(Mesh&&) noexcept;
        ~Mesh();

        //=================================================
        // Assignment operators
        //=================================================

        Mesh& operator=(const Mesh&) = delete;
        Mesh& operator=(Mesh&&) noexcept;

        //=================================================
        // Buffer mutators
        //=================================================

        void load(const mesh::Dynamic_vertex_array& mesh);

        void unload();

        //=================================================
        // Accessors
        //=================================================

        std::uint32_t vertex_count() const;

    private:

        //=================================================
        // Instance members
        //=================================================

        vk::Buffer index_buffer;
        vk::Buffer pos_buffer;
        vk::Buffer norm_buffer;

        std::uint32_t vert_count{};

    };

}

#endif //AGS_ARE_VK_MESH_HPP
