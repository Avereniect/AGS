//
// Created by avereniect on 5/2/22.
//
#include "Texture.hpp"
#include "Texture_kernel.hpp"

namespace ags::are::gl_kernel {

    Texture2D::~Texture2D() {
        unload();
    }

    void Texture2D::load(std::uint32_t w, std::uint32_t h, Channel_format f, std::uint8_t* ptr) {
        load(w, h, f, Primitive::UINT8, ptr);
    }

    void Texture2D::load(std::uint32_t w, std::uint32_t h, Channel_format f, std::uint16_t* ptr) {
        load(w, h, f, Primitive::UINT16, ptr);
    }

    void Texture2D::load(std::uint32_t w, std::uint32_t h, Channel_format f, float* ptr) {
        load(w, h, f, Primitive::FLOAT32, ptr);
    }

    void Texture2D::unload() {
        if (id == 0) {
            return;
        }

        Texture_kernel::release_texture(id);
        id = 0;
        dims = {0, 0};
        channel_type = Primitive::NULL_PRIMITIVE;
        format = Channel_format::NULL_CHANNEL_FORMAT;
    }

    std::uint32_t Texture2D::width() const {
        return dims[0];
    }

    std::uint32_t Texture2D::height() const {
        return dims[1];
    }

    std::array<std::uint32_t, 2> Texture2D::dimensions() const {
        return dims;
    }

    Channel_format Texture2D::channel_format() const {
        return format;
    }

    void Texture2D::load(std::uint32_t w, std::uint32_t h, Channel_format f, Primitive p, void* ptr) {
        if (id == 0) {
            id = Texture_kernel::acquire_texture();
        }

        dims = {w, h};
        channel_type = p;
        format = f;

        glBindTexture(GL_TEXTURE_2D, id);

        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

        auto internal_format = to_native_enum(f, p);
        auto color_format = to_native_enum(f);
        auto primitive = to_native_enum(p);

        glTexImage2D(
            GL_TEXTURE_2D,
            0, //Mip-map level
            internal_format,
            GLsizei(w), GLsizei(h),
            0, //Border. Required to be 0
            color_format,
            primitive,
            ptr
        );
    }

}
