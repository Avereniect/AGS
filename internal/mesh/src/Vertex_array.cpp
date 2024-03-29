#include "ags/mesh/Vertex_array.hpp"

namespace ags::mesh {

    //=====================================================
    // -ctors
    //=====================================================

    Vertex_array::Vertex_array(const Vertex_array& src):
        num_indices(src.num_indices),
        index_array(reinterpret_cast<std::uint32_t*>(malloc(sizeof(std::uint32_t) * src.num_indices))),
        num_vertices(src.num_vertices),
        attribute_map(src.attribute_map) {

        //TODO: Error handling
        for (auto& attrib : attribute_map.values()) {
            auto* orig = attrib.ptr;

            auto allocation_size =
                size_of_primitive(attrib.type()) *
                static_cast<std::uint8_t>(attrib.width()) *
                num_vertices;
            attrib.ptr = malloc(allocation_size);

            std::memcpy(attrib.ptr, orig, allocation_size);
        }
    }

    Vertex_array::Vertex_array(Vertex_array&& rhs) noexcept:
        num_indices(std::exchange(rhs.num_indices, 0)),
        index_array(std::exchange(rhs.index_array, nullptr)),
        num_vertices(std::exchange(rhs.num_vertices, 0)),
        attribute_map(std::exchange(rhs.attribute_map, {})) {}

    Vertex_array::~Vertex_array() {
        clear();
    }

    //=====================================================
    // Assignment operators
    //=====================================================

    Vertex_array& Vertex_array::operator=(const Vertex_array& rhs) {
        if (this == &rhs) {
            return *this;
        }

        //TODO: Error handling
        num_indices = rhs.num_indices;
        index_array = reinterpret_cast<std::uint32_t*>(malloc(num_indices * sizeof(std::uint32_t)));

        num_vertices = rhs.num_vertices;

        attribute_map = rhs.attribute_map;
        for (auto& attrib : attribute_map.values()) {
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

    Vertex_array& Vertex_array::operator=(Vertex_array&& rhs) noexcept {
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

    std::uint32_t* Vertex_array::specify_indices(std::uint32_t index_count, const std::uint32_t* index_ptr, std::uint32_t vertex_count) {
        if (index_count == 0) {
            return nullptr;
        }

        num_indices = index_count;
        num_vertices = vertex_count;

        index_array = reinterpret_cast<std::uint32_t*>(malloc(index_count * sizeof(std::uint32_t)));
        std::copy_n(index_ptr, index_count, index_array);

        return index_array;
    }

    std::uint32_t* Vertex_array::specify_indices(std::uint32_t index_count, const std::uint32_t* index_ptr) {
        if (index_count == 0) {
            return nullptr;
        }

        std::uint32_t max = *std::max_element(index_ptr, index_ptr + index_count);
        return specify_indices(index_count, index_ptr, max + 1);
    }

    Attribute_handle Vertex_array::specify_attribute(std::uint32_t location, Attribute_width w, const std::uint8_t* ptr) {
        return specify_attribute(location, Primitive::UINT8, w, ptr);
    }

    Attribute_handle Vertex_array::specify_attribute(std::uint32_t location, Attribute_width w, const std::uint16_t* ptr) {
        return specify_attribute(location, Primitive::UINT16, w, ptr);
    }

    Attribute_handle Vertex_array::specify_attribute(std::uint32_t location, Attribute_width w, const std::uint32_t* ptr) {
        return specify_attribute(location, Primitive::UINT32, w, ptr);
    }

    Attribute_handle Vertex_array::specify_attribute(std::uint32_t location, Attribute_width w, const half* ptr) {
        return specify_attribute(location, Primitive::FLOAT16, w, ptr);
    }

    Attribute_handle Vertex_array::specify_attribute(std::uint32_t location, Attribute_width w, const float* ptr) {
        return specify_attribute(location, Primitive::FLOAT32, w, ptr);
    }

    bool Vertex_array::remove_attribute(std::uint32_t name) {
        auto it = attribute_map.find(name);
        free(aul::get<1>(it));

        bool ret = it != attribute_map.end();
        attribute_map.erase(it);
        return ret;
    }

    void Vertex_array::clear() {
        free(index_array);
        num_indices = 0;

        for (auto& attrib : attribute_map.values()) {
            free(attrib.ptr);
        }

        attribute_map.clear();
        num_vertices = 0;
    }

    //=====================================================
    // Accessors
    //=====================================================

    aul::Span<const std::uint32_t> Vertex_array::attribute_locations() const {
        return attribute_map.keys();
    }

    const Attribute_handle Vertex_array::get_attribute(std::uint32_t location) const {
        auto it = attribute_map.find(location);
        if (it == attribute_map.end()) {
            return {};
        }

        return std::get<1>(*it);
    }

    std::uint32_t Vertex_array::index_count() const {
        return num_indices;
    }

    std::uint32_t Vertex_array::vertex_count() const {
        return num_vertices;
    }

    aul::Span<const std::uint32_t> Vertex_array::indices() const {
        return {index_array, num_vertices};
    }

    aul::Span<Attribute_handle> Vertex_array::attributes() {
        return attribute_map.values();
    }

    aul::Span<const Attribute_handle> Vertex_array::attributes() const {
        return attribute_map.values();
    }

    //=====================================================
    // Helper functions
    //=====================================================

    Attribute_handle Vertex_array::specify_attribute(
        std::uint32_t location,
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
        auto [it, succ] = attribute_map.emplace_or_assign(location, p, w, allocation);
        return std::get<1>(*it);
    }

}