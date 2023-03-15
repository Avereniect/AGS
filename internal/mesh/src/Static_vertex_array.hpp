#ifndef AGS_MESH_VERTEX_ARRAY_HPP
#define AGS_MESH_VERTEX_ARRAY_HPP

#include "ags/Types.hpp"

#include <cstdint>
#include <string>
#include <tuple>

namespace ags::mesh {

    template<Primitive p, const char* n>
    struct Static_attribute {
        using type = typename ags::primitive_to_type_t<p>;
        static inline const char* name = n;
    };

    ///
    /// \tparam Attributes List of ags::mesh::Static_attribute classes
    template<class...Attributes>
    class Static_vertex_array {
    public:

        //=================================================
        // -ctors
        //=================================================

        Static_vertex_array() = default;

        //=================================================
        // Assignment operators
        //=================================================

        //=================================================
        // Mutators
        //=================================================

        void load(const std::uint32_t* index_ptr, const typename Attributes::type*... attributes) {
            //TODO: Allocate indices


        }

    private:

        //=================================================
        // Instance members
        //=================================================

        std::uint32_t num_indices = 0;
        std::uint32_t* indices = nullptr;

        std::uint32_t num_vertices = 0;


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

    ///
    /// Owning
    ///
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



}

#endif //AGS_MESH_VERTEX_ARRAY_HPP
