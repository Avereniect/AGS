//
// Created by avereniect on 5/9/22.
//
#include "Dynamic_vertex_array.hpp"

#include <algorithm>

namespace ags::mesh {

    //=====================================================
    // -ctors
    //=====================================================

    Dynamic_vertex_array::Dynamic_vertex_array(const Dynamic_vertex_array& src):
        num_indices(src.num_indices),
        index_array(reinterpret_cast<std::uint32_t*>(malloc(sizeof(std::uint32_t) * src.num_indices))),
        num_vertices(src.num_vertices),
        attribute_map(src.attribute_map) {

        //TODO: Error handling
        for (auto& attrib : attribute_map) {
            auto* orig = attrib.ptr;

            auto allocation_size =
                size_of_primitive(attrib.type()) *
                static_cast<std::uint8_t>(attrib.width()) *
                num_vertices;
            attrib.ptr = malloc(allocation_size);

            std::memcpy(attrib.ptr, orig, allocation_size);
        }
    }

    Dynamic_vertex_array::Dynamic_vertex_array(Dynamic_vertex_array&& rhs) noexcept:
        num_indices(std::exchange(rhs.num_indices, 0)),
        index_array(std::exchange(rhs.index_array, nullptr)),
        num_vertices(std::exchange(rhs.num_vertices, 0)),
        attribute_map(std::exchange(attribute_map, {})) {}

    Dynamic_vertex_array::~Dynamic_vertex_array() {
        clear();
    }

    //=====================================================
    // Assignment operators
    //=====================================================

    Dynamic_vertex_array& Dynamic_vertex_array::operator=(const Dynamic_vertex_array& rhs) {
        if (this == &rhs) {
            return *this;
        }

        //TODO: Error handling
        num_indices = rhs.num_indices;
        index_array = reinterpret_cast<std::uint32_t*>(malloc(num_indices * sizeof(std::uint32_t)));

        num_vertices = rhs.num_vertices;

        attribute_map = rhs.attribute_map;
        for (auto& attrib : attribute_map) {
            auto* orig = attrib.ptr;

            auto allocation_size =
                size_of_primitive(attrib.type()) *
                static_cast<std::uint8_t>(attrib.width()) *
                num_vertices;
            attrib.ptr = malloc(allocation_size);

            std::memcpy(attrib.ptr, orig, allocation_size);
        }

        return *this;
    }

    Dynamic_vertex_array& Dynamic_vertex_array::operator=(Dynamic_vertex_array&& rhs) noexcept {
        if (this == &rhs) {
            return *this;
        }
        num_indices = std::exchange(rhs.num_indices, 0);
        index_array = std::exchange(rhs.index_array, nullptr);

        num_vertices = std::exchange(rhs.num_vertices, 0);
        attribute_map = std::exchange(rhs.attribute_map, {});

        return *this;
    }

    //=====================================================
    // Mutators
    //=====================================================

    std::uint32_t* Dynamic_vertex_array::specify_indices(std::uint32_t index_count, const std::uint32_t* index_ptr, std::uint32_t vertex_count) {
        if (index_count == 0) {
            return nullptr;
        }

        num_indices = index_count;
        num_vertices = vertex_count;

        index_array = reinterpret_cast<std::uint32_t*>(malloc(index_count * sizeof(std::uint32_t)));
        std::copy_n(index_ptr, index_count, index_array);

        return index_array;
    }

    std::uint32_t* Dynamic_vertex_array::specify_indices(std::uint32_t index_count, const std::uint32_t* index_ptr) {
        if (index_count == 0) {
            return nullptr;
        }

        std::uint32_t max = *std::max_element(index_ptr, index_ptr + index_count);
        return specify_indices(index_count, index_ptr, max + 1);
    }

    Attribute_handle Dynamic_vertex_array::specify_attribute(const std::string& name, Attribute_width w, const std::uint8_t* ptr) {
        return specify_attribute(name, Primitive::UINT8, w, ptr);
    }

    Attribute_handle Dynamic_vertex_array::specify_attribute(const std::string& name, Attribute_width w, const std::uint16_t* ptr) {
        return specify_attribute(name, Primitive::UINT16, w, ptr);
    }

    Attribute_handle Dynamic_vertex_array::specify_attribute(const std::string& name, Attribute_width w, const std::uint32_t* ptr) {
        return specify_attribute(name, Primitive::UINT32, w, ptr);
    }

    Attribute_handle Dynamic_vertex_array::specify_attribute(const std::string& name, Attribute_width w, const half* ptr) {
        return specify_attribute(name, Primitive::FLOAT16, w, ptr);
    }

    Attribute_handle Dynamic_vertex_array::specify_attribute(const std::string& name, Attribute_width w, const float* ptr) {
        return specify_attribute(name, Primitive::FLOAT32, w, ptr);
    }

    //=====================================================
    // Accessors
    //=====================================================

    aul::Span<const std::string> Dynamic_vertex_array::attribute_names() const {
        return attribute_map.keys();
    }

    Attribute_handle Dynamic_vertex_array::get_attribute(const std::string& name) const {
        auto it = attribute_map.find(name);
        if (it == attribute_map.end()) {
            return {};
        }
        return *it;
    }

    bool Dynamic_vertex_array::remove_attribute(const std::string& name) {
        auto it = attribute_map.find(name);
        free(it->ptr);

        bool ret = it != attribute_map.end();
        attribute_map.erase(it);
        return ret;
    }

    void Dynamic_vertex_array::clear() {
        free(index_array);
        num_indices = 0;

        for (auto& attrib : attribute_map) {
            free(attrib.ptr);
        }
        num_vertices = 0;
    }

    std::uint32_t Dynamic_vertex_array::index_count() const {
        return num_indices;
    }

    std::uint32_t Dynamic_vertex_array::vertex_count() const {
        return num_vertices;
    }

    aul::Span<const std::uint32_t> Dynamic_vertex_array::indices() const {
        return {index_array, index_array + num_vertices};
    }

    aul::Span<const Attribute_handle> Dynamic_vertex_array::attributes() const {
        return attribute_map.values();
    }

    //=====================================================
    // Helper functions
    //=====================================================

    Attribute_handle Dynamic_vertex_array::specify_attribute(
        const std::string& name,
        Primitive p,
        Attribute_width w,
        const void* ptr
    ) {
        if (ptr == nullptr) {
            return {};
        }

        std::size_t allocation_size = size_of_primitive(p) * num_vertices * static_cast<std::uint8_t>(w);
        void* allocation = malloc(allocation_size);
        std::memcpy(allocation, ptr, allocation_size);
        auto [it, succ] = attribute_map.emplace_or_assign(name, p, w, allocation);
        return *it;
    }

}
