#ifndef AGS_ARE_VK_MESH_HPP
#define AGS_ARE_VK_MESH_HPP

#include <ags/Graphics_includes.hpp>

#include "Enums.hpp"

#include <ags/Mesh.hpp>
#include <cstdint>

namespace ags::are::vk_kernel {

    class Mesh {
    public:

        struct Attribute {
            //TODO: Replace type with allocation handle
            int handle;
            Attribute_type type;
        };

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

        //TODO: Add load overload that take non-owning mesh type

        void load(const mesh::Vertex_array& mesh);

        void unload();

        //=================================================
        // Accessors
        //=================================================

        [[nodiscard]]
        std::uint32_t index_count() const;

        [[nodiscard]]
        std::uint32_t vertex_count() const;

        [[nodiscard]]
        aul::Span<const std::uint32_t> attribute_locations() const;

        [[nodiscard]]
        Attribute_type attribute_type(std::uint32_t loc) const;

    private:

        //=================================================
        // Instance members
        //=================================================

        vk::Buffer index_buffer;

        std::uint32_t num_indices = 0;
        std::uint32_t num_vertices = 0;

        aul::Array_map<std::uint32_t, Attribute> attributes;

        //=================================================
        // Helper functions
        //=================================================

        std::vector<vk::VertexInputAttributeDescription>
        create_attribute_descriptions(const mesh::Vertex_array& mesh);

    };

}

#endif //AGS_ARE_VK_MESH_HPP
