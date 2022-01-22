//
// Created by avereniect on 1/9/22.
//

#ifndef AGS_GL33_OBJECT_HPP
#define AGS_GL33_OBJECT_HPP

#include <glad/glad.h>

namespace ags::are::gl33 {

    class Object {
    public:

        Object() = default;
        Object(const Object&) = delete;
        Object(Object&&) noexcept;
        ~Object() = default;

        Object& operator=(const Object&) = delete;
        Object& operator=(Object&&) noexcept;

        [[nodiscard]]
        GLuint get_id() const;

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

#endif //AGS_GL33_OBJECT_HPP
