//
// Created by avereniect on 9/1/22.
//

#ifndef AGS_ARE_UNIFORM_BLOCK_HPP
#define AGS_ARE_UNIFORM_BLOCK_HPP

#include "Enums_common.hpp"

#include <cstdint>
#include <string>

#include <aul/containers/Array_map.hpp>

#include <avml/Matrices.hpp>
#include <avml/Vectors.hpp>

namespace ags::are {

    class Uniform_block_layout {
    public:

        //=================================================
        // Helper types
        //=================================================

        struct Uniform {
            std::string name{};
            std::uint16_t location = -1;
            Uniform_type type = Uniform_type::NULL_UNIFORM_TYPE;
        };

    private:

        struct Internal_uniform {

        };

    public:

        //=================================================
        // -ctors
        //=================================================

        Uniform_block_layout();
        ~Uniform_block_layout();

        //=================================================
        // Assignment operators
        //=================================================

        Uniform_block_layout& operator=(const Uniform_block_layout&);
        Uniform_block_layout& operator=(Uniform_block_layout&&) noexcept;

        //=================================================
        // Comparisons
        //=================================================

        friend bool operator<(const Uniform_block_layout& lhs, const Uniform_block_layout& rhs);

        bool is_subset(const Uniform_block_layout& other);

        //=================================================
        // Mutators
        //=================================================

        void specify_uniforms(const std::vector<Uniform>& uniform);

        //=================================================
        // Accessors
        //=================================================

        ///
        /// \return Number of uniforms in uniform block
        [[nodiscard]]
        std::size_t size() const;

        ///
        /// \return Number of occupied locations in
        [[nodiscard]]
        std::size_t occupied_locations() const;

    private:

        //=================================================
        // Instance members
        //=================================================

        aul::Array_map<std::string, Internal_uniform> uniforms;

    };

    class Uniform_block {
    public:

        //=================================================
        // -ctors
        //=================================================

        //=================================================
        // Assignment operators
        //=================================================

        //=================================================
        // Uniform specification
        //=================================================

        void field(const std::string_view, float);
        void field(const std::string_view, avml::vec2f);
        void field(const std::string_view, avml::vec3f);
        void field(const std::string_view, avml::vec4f);

        void field(const std::string_view, avml::mat2x2f);
        void field(const std::string_view, avml::mat3x3f);
        void field(const std::string_view, avml::mat4x4f);

        void field(const std::string_view, std::int32_t);
        void field(const std::string_view, avml::vec2i);
        void field(const std::string_view, avml::vec3i);
        void field(const std::string_view, avml::vec4i);

        void field(const std::string_view, avml::mat2x2i);
        void field(const std::string_view, avml::mat3x3i);
        void field(const std::string_view, avml::mat4x4i);

        void field(const std::string_view, std::uint32_t);
        void field(const std::string_view, avml::vec2u);
        void field(const std::string_view, avml::vec3u);
        void field(const std::string_view, avml::vec4u);

        void field(const std::string_view, avml::mat2x2u);
        void field(const std::string_view, avml::mat3x3u);
        void field(const std::string_view, avml::mat4x4u);



        void field(const std::string_view, aul::Span<float>);
        void field(const std::string_view, aul::Span<avml::vec2f>);
        void field(const std::string_view, aul::Span<avml::vec3f>);
        void field(const std::string_view, aul::Span<avml::vec4f>);

        void field(const std::string_view, aul::Span<avml::mat2x2f>);
        void field(const std::string_view, aul::Span<avml::mat3x3f>);
        void field(const std::string_view, aul::Span<avml::mat4x4f>);

        void field(const std::string_view, aul::Span<std::int32_t>);
        void field(const std::string_view, aul::Span<avml::vec2i>);
        void field(const std::string_view, aul::Span<avml::vec3i>);
        void field(const std::string_view, aul::Span<avml::vec4i>);

        void field(const std::string_view, aul::Span<avml::mat2x2i>);
        void field(const std::string_view, aul::Span<avml::mat3x3i>);
        void field(const std::string_view, aul::Span<avml::mat4x4i>);

        void field(const std::string_view, aul::Span<std::uint32_t>);
        void field(const std::string_view, aul::Span<avml::vec2u>);
        void field(const std::string_view, aul::Span<avml::vec3u>);
        void field(const std::string_view, aul::Span<avml::vec4u>);

        void field(const std::string_view, aul::Span<avml::mat2x2u>);
        void field(const std::string_view, aul::Span<avml::mat3x3u>);
        void field(const std::string_view, aul::Span<avml::mat4x4u>);

        //=================================================
        // Accessors
        //=================================================

        [[nodiscard]]
        std::size_t size_bytes() const;

        [[nodiscard]]
        std::size_t uniform_count() const;

        [[nodiscard]]
        std::byte* data();

        [[nodiscard]]
        const std::byte* data() const;

    private:

        //=================================================
        // Instance members
        //=================================================

        //TODO: Some kind of reference to uniform block layout

    };

}

#endif //AGS_ARE_UNIFORM_BLOCK_HPP
