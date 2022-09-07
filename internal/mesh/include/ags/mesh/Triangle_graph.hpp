//
// Created by avereniect on 5/9/22.
//

#ifndef AGS_TRIANGLE_GRAPH_HPP
#define AGS_TRIANGLE_GRAPH_HPP

#include "ags/mesh/Attribute.hpp"

#include "avml/AVML.hpp"

#include "aul/containers/Array_map.hpp"
#include "aul/Span.hpp"

#include <cstdint>

namespace ags::mesh {

    ///
    ///
    ///
    class Triangle_graph {
    public:

        //=================================================
        // Type Aliases
        //=================================================

        using index_type = std::uint32_t;

        using location_type = std::uint16_t;

        using size_type = std::uint32_t;
        using difference_type = std::int32_t;

        using index_set_type = std::array<index_type, 3>;
        using neighbor_type = std::array<index_type, 3>;

        //=================================================
        // -ctors
        //=================================================

        Triangle_graph() = default;
        Triangle_graph(const Triangle_graph&);
        Triangle_graph(Triangle_graph&&) noexcept;
        ~Triangle_graph();

        //=================================================
        // Assignment operators
        //=================================================

        Triangle_graph& operator=(const Triangle_graph&);

        Triangle_graph& operator=(Triangle_graph&&) noexcept;

        //=================================================
        // Mutators
        //=================================================

        void reserve_indices() const;

        void reserve_vertices() const;

        void reserve_edges() const;

        void reserve_faces() const;

        //=================================================
        // Accessors
        //=================================================

        [[nodiscard]]
        size_type index_count() const;

        [[nodiscard]]
        size_type vertex_count() const;

        [[nodiscard]]
        size_type edge_count() const;

        [[nodiscard]]
        size_type face_count() const;


        [[nodiscard]]
        aul::Span<const index_set_type> indices() const;

        [[nodiscard]]
        aul::Span<const neighbor_type> neighbors() const;


        [[nodiscard]]
        const Attribute_handle& vertex_attribute(location_type location);

        [[nodiscard]]
        const Attribute_handle& edge_attribute(location_type location);

        [[nodiscard]]
        const Attribute_handle& face_attribute(location_type location);


        [[nodiscard]]
        aul::Span<const location_type> vertex_attribute_locations() const;

        [[nodiscard]]
        aul::Span<const location_type> edge_attribute_locations() const;

        [[nodiscard]]
        aul::Span<const location_type> face_attribute_locations() const;


        [[nodiscard]]
        aul::Span<const Attribute_handle> vertex_attributes() const;

        [[nodiscard]]
        aul::Span<const Attribute_handle> edge_attributes() const;

        [[nodiscard]]
        aul::Span<const Attribute_handle> face_attributes() const;

    private:

        //=================================================
        // Instance members
        //=================================================

        index_set_type* index_array = nullptr;

        size_type num_indices = 0;

        size_type num_vertices = 0;

        size_type num_edges = 0;

        size_type num_faces = 0;


        size_type cap_indices = 0;

        size_type cap_vertices = 0;

        size_type cap_edges = 0;

        size_type cap_faces = 0;


        aul::Array_map<location_type, Attribute_handle> vertex_attribute_map{};

        aul::Array_map<location_type, Attribute_handle> edge_attribute_map{};

        aul::Array_map<location_type, Attribute_handle> face_attribute_map{};

        neighbor_type* neighbor_array = nullptr;

    };

}

#endif //AGS_TRIANGLE_GRAPH_HPP
