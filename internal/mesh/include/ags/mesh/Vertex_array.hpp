//
// Created by avereniect on 6/30/22.
//

#ifndef AGS_MESH_VERTEX_ARRAY_HPP
#define AGS_MESH_VERTEX_ARRAY_HPP

#include "Attribute.hpp"

#include "aul/Span.hpp"
#include "aul/containers/Array_map.hpp"

#include "ags/Types.hpp"

namespace ags::mesh {

    class Vertex_array {
    public:

        //=================================================
        // -ctors
        //=================================================

        Vertex_array() = default;
        Vertex_array(const Vertex_array&);
        Vertex_array(Vertex_array&&) noexcept;
        ~Vertex_array();

        //=================================================
        // Assignment operators
        //=================================================

        Vertex_array& operator=(const Vertex_array&);
        Vertex_array& operator=(Vertex_array&&) noexcept;

        //=================================================
        // Mutators
        //=================================================

        ///
        /// \param index_count Number of indices in mesh
        /// \param index_ptr Pointer to array of indices
        /// \param vertex_count Number of vertices in mesh
        /// \return Pointer to internal index array
        std::uint32_t* specify_indices(std::uint32_t index_count, const std::uint32_t* index_ptr, std::uint32_t vertex_count);

        std::uint32_t* specify_indices(std::uint32_t index_count, const std::uint32_t* index_ptr);

        Attribute_handle specify_attribute(std::uint32_t location, Attribute_width w, const std::uint8_t* ptr);
        Attribute_handle specify_attribute(std::uint32_t location, Attribute_width w, const std::uint16_t* ptr);
        Attribute_handle specify_attribute(std::uint32_t location, Attribute_width w, const std::uint32_t* ptr);

        Attribute_handle specify_attribute(std::uint32_t location, Attribute_width w, const half* ptr);
        Attribute_handle specify_attribute(std::uint32_t location, Attribute_width w, const float* ptr);

        bool remove_attribute(std::uint32_t location);

        ///
        /// Empties the contents of the vertex array and release any held
        /// allocations
        ///
        void clear();

        //=================================================
        // Accessors
        //=================================================

        ///
        /// \return A span over the names of attributes. The span is valid so
        ///     long as attribute have been neither removed or added
        [[nodiscard]]
        aul::Span<const std::uint32_t> attribute_locations() const;

        ///
        /// \param location Location of attribute to retrieve
        /// \return Const handle over attribute
        [[nodiscard]]
        const Attribute_handle get_attribute(std::uint32_t location) const;

        ///
        /// \return Number of element indices used
        [[nodiscard]]
        std::uint32_t index_count() const;

        ///
        /// \return Number of vertices in mesh
        [[nodiscard]]
        std::uint32_t vertex_count() const;

        ///
        /// \return Span over element indices. Valid until indices are specified
        /// again.
        [[nodiscard]]
        aul::Span<const std::uint32_t> indices() const;

        ///
        /// \return Span ove rlist of Attributes. Valid until number of
        /// attributes is modified.
        [[nodiscard]]
        aul::Span<Attribute_handle> attributes();

        ///
        /// \return Span over list of attributes. Valid until number of
        /// attributes is modified.
        [[nodiscard]]
        aul::Span<const Attribute_handle> attributes() const;

    private:

        //=================================================
        // Instance members
        //=================================================

        std::uint32_t num_indices = 0;
        std::uint32_t* index_array = nullptr;

        std::uint32_t num_vertices = 0;
        aul::Array_map<std::uint32_t, Attribute_handle> attribute_map{};

        //=================================================
        // Helper functions
        //=================================================

        Attribute_handle specify_attribute(
            std::uint32_t location,
            Primitive p,
            Attribute_width w,
            const void* ptr
        );

    };

}

#endif //AGS_MESH_VERTEX_ARRAY_HPP
