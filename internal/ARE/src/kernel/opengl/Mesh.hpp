//
// Created by avereniect on 1/1/22.
//

#ifndef AGS_ARE_GL_MESH_HPP
#define AGS_ARE_GL_MESH_HPP

#include "Object.hpp"

#include "Enums.hpp"

#include <ags/Mesh.hpp>

#include <aul/containers/Array_map.hpp>
#include <aul/Span.hpp>

namespace ags::are::gl_kernel {

    class Mesh : public Object {
    public:

        struct Attribute {
            GLuint handle;
            ags::are::Attribute_type type;
        };

        //=================================================
        // -ctors
        //=================================================

        Mesh() = default;
        Mesh(const Mesh&) noexcept = delete;
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

        ///
        /// Loads contents of vertex array into GPU side buffer.
        ///
        /// Any existing buffer is discarded.
        ///
        /// If failure occurs for any reason, then the object's will hold no
        /// resource.
        ///
        /// \param vertex_array Vertex array to load contents of
        void load(const mesh::Vertex_array& vertex_array);

        ///
        /// Releases currently held resource if exists
        ///
        void unload();

        //=================================================
        // Accessors
        //=================================================

        ///
        ///
        /// \return Number of indices used in mesh representation
        [[nodiscard]]
        std::uint32_t index_count() const;

        ///
        ///
        /// \return Number of vertices in mesh
        [[nodiscard]]
        std::uint32_t vertex_count() const;

        ///
        /// \return Span over currently used attribute locations. Valid until
        /// attributes are modified
        [[nodiscard]]
        aul::Span<const std::uint32_t> attribute_locations() const;

        ///
        /// \param loc Attribute location to query
        /// \return Type corresponding to specified location. Returns
        /// NULL_ATTRIBUTE_TYPE if the specified location is unused or does not
        /// exist
        [[nodiscard]]
        Attribute_type attribute_type(std::uint32_t loc) const;

    private:

        //=================================================
        // Instance members
        //=================================================

        GLuint ibo_id = 0;

        std::uint32_t num_indices = 0;
        std::uint32_t num_vertices = 0;

        aul::Array_map<std::uint32_t, Attribute> attributes;

    };

}

#endif //AGS_ARE_GL_MESH_HPP
