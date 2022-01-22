//
// Created by avereniect on 1/1/22.
//

#ifndef AGS_MESH_VERTEX_ARRAY_HPP
#define AGS_MESH_VERTEX_ARRAY_HPP

#include "ags/Types.hpp"

#include <aul/containers/Array_map.hpp>

#include <cstdint>
#include <string>

namespace ags::mesh {

    struct Attribute {
        Primitive type = Primitive::NULL_PRIMITIVE;
        std::uint8_t components = 0;
        void* ptr = nullptr;
    };

    class Fixed_vertex_array_base {
    protected:

        std::uint32_t index_count = 0;
        std::uint32_t* indices = nullptr;

        std::uint32_t attribute_count = 0;
        float* position = nullptr;
        float* normals = nullptr;
        float* tangents = nullptr;
        float* uv0 = nullptr;
    };

    class Fixed_vertex_array : Fixed_vertex_array_base {
    public:

        Fixed_vertex_array():
            Fixed_vertex_array_base() {}

        ~Fixed_vertex_array() {
            delete[] indices;
            delete[] position;
            delete[] normals;
            delete[] tangents;
            delete[] uv0;
        }

        void load_indices(std::uint32_t*) {

        }

    };

    class Fixed_vertex_array_view {
    public:

        //=================================================
        // -ctors
        //=================================================

        Fixed_vertex_array_view() = default;
        Fixed_vertex_array_view(const Fixed_vertex_array_view& view) = default;
        Fixed_vertex_array_view(Fixed_vertex_array_view&& view) = default;
        ~Fixed_vertex_array_view() = default;

        //=================================================
        // Assignment Operators
        //=================================================

        Fixed_vertex_array_view& operator=(const Fixed_vertex_array_view&) = default;
        Fixed_vertex_array_view& operator=(Fixed_vertex_array_view&&) = default;

        //=================================================
        // Loading
        //=================================================

        void load_indices();



    private:

        std::uint32_t num_indices = 0;
        const std::uint32_t index_ptr;

        std::uint32_t num_vertices = 0;
        const float* position_ptr = nullptr;
        const float* normal_ptr = nullptr;
        const float* tangent_ptr = nullptr;
        const float* uv0_ptr = nullptr;

    };


    class Dynamic_vertex_array_base {
    public:

        Dynamic_vertex_array_base() = default;
        ~Dynamic_vertex_array_base() = default;

        //=================================================
        // Mutators
        //=================================================

        void add_attribute(const void*);

    protected:

        //=================================================
        // Instance members
        //=================================================

        std::uint32_t* indices;
        std::uint32_t index_count;

        std::uint32_t vertex_count;
        aul::Array_map<std::string, Attribute> attributes{};

    };

    ///
    /// Class representing
    ///
    class Dynamic_vertex_array : public Dynamic_vertex_array_base {
    public:

        //=================================================
        // -ctors
        //=================================================

        Dynamic_vertex_array() = default;
        Dynamic_vertex_array(const Dynamic_vertex_array&) = delete;
        Dynamic_vertex_array(Dynamic_vertex_array&&) = delete;
        ~Dynamic_vertex_array() {
            clear();
        }

        //=================================================
        // Assignment operators
        //=================================================

        Dynamic_vertex_array& operator=(const Dynamic_vertex_array&) = delete;
        Dynamic_vertex_array& operator=(Dynamic_vertex_array&&) = delete;

        //=================================================
        // Mutators
        //=================================================

        void clear() {
            free(indices);
            indices = nullptr;
            index_count = 0;
            vertex_count = 0;

            attributes.clear();
        }

    private:

        //=================================================
        // Instance members
        //=================================================

        std::uint32_t* indices = nullptr;
        std::uint32_t index_count = 0;

        std::uint32_t vertex_count = 0;
        aul::Array_map<std::string, Attribute> attributes{};
    };

    class Dynamic_vertex_array_view {
    public:

        Dynamic_vertex_array_view() = default;
        ~Dynamic_vertex_array_view() = default;

    private:


    };

}

#endif //AGS_MESH_VERTEX_ARRAY_HPP
