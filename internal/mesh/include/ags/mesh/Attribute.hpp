//
// Created by avereniect on 6/30/22.
//

#ifndef AGS_MESH_ATTRIBUTE_HPP
#define AGS_MESH_ATTRIBUTE_HPP

#include "ags/Types.hpp"

namespace ags::mesh {

    enum class Attribute_width : std::uint8_t {
        NULL_ATTRIBUTE_WIDTH = 0,
        ONE = 1,
        TWO = 2,
        THREE = 3,
        FOUR = 4
    };

    /*
    struct Attribute {
        Primitive type = Primitive::NULL_PRIMITIVE;
        Attribute_width width = Attribute_width::NULL_ATTRIBUTE_WIDTH;
    };
    */

    ///
    /// Struct containing information about mesh attributes
    ///
    struct Attribute_handle {

        //=================================================
        // -ctors
        //=================================================

        ///
        /// \param p
        /// \param w
        /// \param ptr
        Attribute_handle(Primitive p, Attribute_width w, void* ptr);

        Attribute_handle() = default;
        Attribute_handle(const Attribute_handle&) = default;
        Attribute_handle(Attribute_handle&&) = default;
        ~Attribute_handle() = default;

        //=================================================
        // Assignment operators
        //=================================================

        Attribute_handle& operator=(const Attribute_handle&) = default;
        Attribute_handle& operator=(Attribute_handle&&) = default;

        //=================================================
        // Accessors
        //=================================================

        [[nodiscard]]
        Primitive type() const;

        [[nodiscard]]
        Attribute_width width() const;

        [[nodiscard]]
        void* handle();

        [[nodiscard]]
        const void* handle() const;

        //=================================================
        // Mutators
        //=================================================

        void set_handle(void* ptr);

        //=================================================
        // Instance members
        //=================================================

        Primitive primitive = Primitive::NULL_PRIMITIVE;
        Attribute_width components = Attribute_width::NULL_ATTRIBUTE_WIDTH;
        void* ptr = nullptr;

    };

}

#endif //AGS_MESH_ATTRIBUTE_HPP
