//
// Created by avereniect on 5/9/22.
//

#ifndef AGS_DYNAMIC_VERTEX_ARRAY_HPP
#define AGS_DYNAMIC_VERTEX_ARRAY_HPP

#include "ags/Types.hpp"
#include "ags/mesh/Attribute.hpp"

#include <aul/Span.hpp>
#include <aul/containers/Array_map.hpp>

#include <cstdint>

namespace ags::mesh {

    ///
    /// Class representing
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

        std::uint32_t* specify_indices(std::uint32_t index_count, const std::uint32_t* index_ptr, std::uint32_t vertex_count);

        std::uint32_t* specify_indices(std::uint32_t index_count, const std::uint32_t* index_ptr);

        Attribute_handle specify_attribute(const std::string& name, Attribute_width w, const std::uint8_t* ptr);
        Attribute_handle specify_attribute(const std::string& name, Attribute_width w, const std::uint16_t* ptr);
        Attribute_handle specify_attribute(const std::string& name, Attribute_width w, const std::uint32_t* ptr);

        Attribute_handle specify_attribute(const std::string& name, Attribute_width w, const half* ptr);
        Attribute_handle specify_attribute(const std::string& name, Attribute_width w, const float* ptr);

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
        Attribute_handle get_attribute(const std::string& name) const;

        [[nodiscard]]
        std::uint32_t index_count() const;

        [[nodiscard]]
        std::uint32_t vertex_count() const;

        [[nodiscard]]
        aul::Span<const std::uint32_t> indices() const;

        [[nodiscard]]
        aul::Span<const Attribute_handle> attributes() const;

    protected:

        //=================================================
        // Instance members
        //=================================================

        std::uint32_t num_indices = 0;
        std::uint32_t* index_array = nullptr;

        std::uint32_t num_vertices = 0;
        aul::Array_map<std::string, Attribute_handle> attribute_map{};

        //=================================================
        // Helper functions
        //=================================================

        Attribute_handle specify_attribute(
            const std::string& name,
            Primitive p,
            Attribute_width w,
            const void* ptr
        );

    };

}

#endif //AGS_DYNAMIC_VERTEX_ARRAY_HPP
