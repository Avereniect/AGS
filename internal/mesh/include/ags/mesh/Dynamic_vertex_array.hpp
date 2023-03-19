#ifndef AGS_DYNAMIC_VERTEX_ARRAY_HPP
#define AGS_DYNAMIC_VERTEX_ARRAY_HPP

#include "ags/Types.hpp"
#include "ags/mesh/Attribute.hpp"

#include "aul/Span.hpp"
#include "aul/containers/Array_map.hpp"

#include <cstdint>

namespace ags::mesh {

    ///
    /// Class which represents a 3D mesh as a series of parallel arrays.
    ///
    /// This
    ///
    class Dynamic_vertex_array {
    public:

        //=================================================
        // -ctors
        //=================================================

        Dynamic_vertex_array() = default;
        Dynamic_vertex_array(const Dynamic_vertex_array&);
        Dynamic_vertex_array(Dynamic_vertex_array&&) noexcept;
        ~Dynamic_vertex_array();

        //=================================================
        // Assignment operators
        //=================================================

        Dynamic_vertex_array& operator=(const Dynamic_vertex_array&);
        Dynamic_vertex_array& operator=(Dynamic_vertex_array&&) noexcept;

        //=================================================
        // Mutators
        //=================================================

        ///
        /// \param index_count The number of vertex indices in the mesh
        /// \param index_ptr Pointer to array of indices to copy
        /// \param vertex_count Number vertices in the mesh
        /// \return Pointer to internal index array
        std::uint32_t* specify_indices(std::uint32_t index_count, const std::uint32_t* index_ptr, std::uint32_t vertex_count);

        ///
        /// \param index_count The number of vertex indices in the mesh
        /// \param index_ptr Pointer to array of indices to copy
        /// \return Pointer to internal index array
        std::uint32_t* specify_indices(std::uint32_t index_count, const std::uint32_t* index_ptr);

        Attribute_array_handle specify_attribute(const std::string& name, Attribute_width w, const std::uint8_t* ptr);
        Attribute_array_handle specify_attribute(const std::string& name, Attribute_width w, const std::uint16_t* ptr);
        Attribute_array_handle specify_attribute(const std::string& name, Attribute_width w, const std::uint32_t* ptr);

        Attribute_array_handle specify_attribute(const std::string& name, Attribute_width w, const half* ptr);
        Attribute_array_handle specify_attribute(const std::string& name, Attribute_width w, const float* ptr);

        ///
        /// \param name
        /// \return
        bool remove_attribute(const std::string& name);

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
        aul::Span<const std::string> attribute_names() const;

        [[nodiscard]]
        Attribute_array_handle get_attribute(const std::string& name) const;

        [[nodiscard]]
        std::uint32_t index_count() const;

        [[nodiscard]]
        std::uint32_t vertex_count() const;

        [[nodiscard]]
        aul::Span<const std::uint32_t> indices() const;

        [[nodiscard]]
        aul::Span<const Attribute_array_handle> attributes() const;

    protected:

        //=================================================
        // Instance members
        //=================================================

        std::uint32_t num_indices = 0;
        std::uint32_t* index_array = nullptr;

        std::uint32_t num_vertices = 0;
        aul::Array_map<std::string, Attribute_array_handle> attribute_map{};

        //=================================================
        // Helper functions
        //=================================================

        Attribute_array_handle specify_attribute(
            const std::string& name,
            Primitive p,
            Attribute_width w,
            const void* ptr
        );

    };

}

#endif //AGS_DYNAMIC_VERTEX_ARRAY_HPP
