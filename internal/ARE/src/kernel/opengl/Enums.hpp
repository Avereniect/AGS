//
// Created by avereniect on 5/3/22.
//

#ifndef AGS_ARE_GL_ENUMS_HPP
#define AGS_ARE_GL_ENUMS_HPP

#include <ags/Graphics_includes.hpp>

#include "../Enums_common.hpp"

namespace ags::are::gl_kernel {

    GLenum to_native_enum(Channel_format format);

    GLenum to_native_enum(Primitive primitive);

    GLint to_native_enum(Channel_format format, Primitive primitive);

    GLenum to_native_enum(Depth_format format);

    GLenum to_native_enum(Stencil_format);

    GLenum to_native_enum(Depth_stencil_format format);

    GLint to_native_enum(Texture_wrap wrap);

    GLint to_native_enum(Texture_filter tex_filter);

    GLint to_native_enum(Texture_filter tex_filter, Mipmap_filter mip_filter);

    Primitive to_primitive(GLenum type);

    Attribute_type to_attribute_type(GLenum attribute_type);

    Uniform_type to_uniform_type(GLenum uniform_type);

}

#endif //AGS_ARE_GL_ENUMS_HPP
