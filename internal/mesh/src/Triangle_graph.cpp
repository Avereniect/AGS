//
// Created by avereniect on 8/19/22.
//
#include "ags/mesh/Triangle_graph.hpp"

namespace ags::mesh {

    using size_type = Triangle_graph::size_type;

    using index_type = Triangle_graph::index_type;

    using location_type = Triangle_graph::location_type;

    using index_set_type = Triangle_graph::index_set_type;
    using neighbor_type = Triangle_graph::neighbor_type;

    //=====================================================
    // -ctors
    //=====================================================

    Triangle_graph::Triangle_graph(Triangle_graph&& triangle_graph) noexcept:
        index_array(),
        vertex_attribute_map(),
        edge_attribute_map(),
        face_attribute_map(),
        neighbor_array() {}

    //=====================================================
    // Assignment operators
    //=====================================================

    Triangle_graph& Triangle_graph::operator=(Triangle_graph&& rhs) noexcept {
        index_array = std::exchange(rhs.index_array, nullptr);
        vertex_attribute_map = std::exchange(rhs.vertex_attribute_map, {});
        edge_attribute_map = std::exchange(rhs.edge_attribute_map, {});
        face_attribute_map = std::exchange(rhs.face_attribute_map, {});
        neighbor_array = std::exchange(rhs.neighbor_array, nullptr);

        return *this;
    }

    //=====================================================
    // Mutators
    //=====================================================

    

    //=====================================================
    // Accessors
    //=====================================================

    size_type Triangle_graph::index_count() const {
        return num_indices;
    }

    size_type Triangle_graph::vertex_count() const {
        return num_vertices;
    }

    size_type Triangle_graph::edge_count() const {
        return num_edges;
    }

    size_type Triangle_graph::face_count() const {
        return num_faces;
    }


    aul::Span<const index_set_type> Triangle_graph::indices() const {
        return {index_array, num_indices};
    }

    aul::Span<const neighbor_type> Triangle_graph::neighbors() const {
        return {neighbor_array, num_faces};
    }


    const Attribute_handle& Triangle_graph::vertex_attribute(location_type location) {
        return vertex_attribute_map[location];
    }

    const Attribute_handle& Triangle_graph::edge_attribute(location_type location) {
        return edge_attribute_map[location];
    }

    const Attribute_handle& Triangle_graph::face_attribute(location_type location) {
        return face_attribute_map[location];
    }


    aul::Span<const location_type> Triangle_graph::vertex_attribute_locations() const {
        return vertex_attribute_map.keys();
    }

    aul::Span<const location_type> Triangle_graph::edge_attribute_locations() const {
        return edge_attribute_map.keys();
    }

    aul::Span<const location_type> Triangle_graph::face_attribute_locations() const {
        return face_attribute_map.keys();
    }


    aul::Span<const Attribute_handle> Triangle_graph::vertex_attributes() const {
        return vertex_attribute_map.values();
    }

    aul::Span<const Attribute_handle> Triangle_graph::edge_attributes() const {
        return edge_attribute_map.values();

    }

    aul::Span<const Attribute_handle> Triangle_graph::face_attributes() const {
        return face_attribute_map.values();
    }

}
