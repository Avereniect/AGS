//
// Created by avereniect on 1/9/22.
//

#ifndef AGS_ARE_GL_OBJECT_HPP
#define AGS_ARE_GL_OBJECT_HPP

#include <ags/Graphics_includes.hpp>

namespace ags::are::gl_kernel {

    class Object {
    protected:

        explicit Object(GLuint);

    public:

        Object() = default;
        Object(const Object&) = delete;
        Object(Object&&) noexcept;
        ~Object() = default;

        Object& operator=(const Object&) = delete;
        Object& operator=(Object&&) noexcept;

        ///
        /// \return Native OpenGL handle
        [[nodiscard]]
        GLuint native_handle() const;

        ///
        /// \return True if this object holds a resource. False otherwise
        operator bool() const {
            return (id != 0);
        }

    protected:

        //=================================================
        // Instance members
        //=================================================

        GLuint id = 0;

    };

}

#endif //AGS_ARE_GL_OBJECT_HPP
