//
// Created by avereniect on 5/2/22.
//

#ifndef AGS_ARE_GL_TEXTURE_HPP
#define AGS_ARE_GL_TEXTURE_HPP

#include <ags/Graphics_includes.hpp>

#include "Enums.hpp"
#include "Object.hpp"

#include <ags/Types.hpp>

#include <cstdint>
#include <array>

namespace ags::are::gl_kernel {

    //TODO: Define move constructors and assignment operators
    //TODO: Add memory mapping functions
    //TODO: Add write back functions

    class Texture1D : public Object {
    public:

        //=================================================
        // -ctors
        //=================================================

        Texture1D() = default;

        //=================================================
        // Resource mutators
        //=================================================

        void load(std::uint32_t w, Channel_format f, std::uint8_t* ptr);
        void load(std::uint32_t w, Channel_format f, std::uint16_t* ptr);
        void load(std::uint32_t w, Channel_format f, float* ptr);

        void unload();

        //=================================================
        // Accessors
        //=================================================

        [[nodiscard]]
        GLuint width() const;

        [[nodiscard]]
        GLuint dimensions() const;

        [[nodiscard]]
        Channel_format channel_format() const;

    private:

        //=================================================
        // Instance members
        //=================================================

        GLuint dimension= 0;

        Primitive channel_type = Primitive::NULL_PRIMITIVE;
        Channel_format format = Channel_format::NULL_CHANNEL_FORMAT;

        //=================================================
        // Helper functions
        //=================================================

        void load(std::uint32_t w, Channel_format, Primitive p, void*);

    };

    class Texture2D : public Object {
    public:

        //=================================================
        // -ctors
        //=================================================

        Texture2D() = default;
        Texture2D(const Texture2D&) = delete;
        Texture2D(Texture2D&&) = delete;
        ~Texture2D();

        //=================================================
        // Assignment operators
        //=================================================

        Texture2D& operator=(const Texture2D&) = delete;
        Texture2D& operator=(Texture2D&&) = delete;

        //=================================================
        // Resource mutators
        //=================================================

        void load(std::uint32_t w, std::uint32_t h, Channel_format f, std::uint8_t* ptr);
        void load(std::uint32_t w, std::uint32_t h, Channel_format f, std::int8_t* ptr);

        void load_unnormalized(std::uint32_t w, std::uint32_t h, Channel_format f, std::uint8_t* ptr);
        void load_unnormalized(std::uint32_t w, std::uint32_t h, Channel_format f, std::int8_t* ptr);

        void load(std::uint32_t w, std::uint32_t h, Channel_format f, std::uint16_t* ptr);
        void load(std::uint32_t w, std::uint32_t h, Channel_format f, std::int16_t* ptr);

        void load_unnormalized(std::uint32_t w, std::uint32_t h, Channel_format f, std::uint16_t* ptr);
        void load_unnormalized(std::uint32_t w, std::uint32_t h, Channel_format f, std::int16_t* ptr);

        void load_unnormalized(std::uint32_t w, std::uint32_t h, Channel_format f, std::uint32_t* ptr);
        void load_unnormalized(std::uint32_t w, std::uint32_t h, Channel_format f, std::int32_t* ptr);

        void load(std::uint32_t w, std::uint32_t h, Channel_format f, half* ptr);
        void load(std::uint32_t w, std::uint32_t h, Channel_format f, float* ptr);

        void load_srgb(std::uint32_t w, std::int32_t h, Channel_format f, std::uint8_t* ptr);

        void load_compress_rgtc(std::uint32_t w, std::uint32_t h, Channel_format f, std::uint8_t* ptr);
        void load_compress_rgtc(std::uint32_t w, std::uint32_t h, Channel_format f, std::int8_t* ptr);

        void load_compress_bptc(std::uint32_t w, std::uint32_t h, Channel_format f, std::uint8_t* ptr);
        void load_compress_bptc(std::uint32_t w, std::uint32_t h, Channel_format f, float* ptr);

        void load_compress_astc(std::uint32_t w, std::uint32_t h, Channel_format f, std::uint8_t* ptr);
        void load_compress_astc(std::uint32_t w, std::uint32_t h, Channel_format f, float* ptr);

        void load_compress_s3tc(std::uint32_t w, std::uint32_t h, Channel_format f, std::uint8_t* ptr);
        void load_compress_s3tc(std::uint32_t w, std::uint32_t h, Channel_format f, std::int8_t* ptr);

        void unload();

        //=================================================
        // Accessors
        //=================================================

        [[nodiscard]]
        std::uint32_t width() const;

        [[nodiscard]]
        std::uint32_t height() const;

        [[nodiscard]]
        std::array<GLuint, 2> dimensions() const;

        [[nodiscard]]
        Channel_format channel_format() const;

    private:

        //=================================================
        // Instance members
        //=================================================

        std::array<std::uint32_t, 2> dims{};

        Primitive channel_type = Primitive::NULL_PRIMITIVE;
        Channel_format format = Channel_format::NULL_CHANNEL_FORMAT;

        //TODO: Add enum to keep track of texture compression scheme
        //TODO: Add enum to keep track of

        //=================================================
        // Helper functions
        //=================================================

        void load(std::uint32_t w, std::uint32_t h, Channel_format, Primitive p, void*);

    };

    class Texture3D : public Object {
    public:

        //=================================================
        // -ctors
        //=================================================

        Texture3D() = default;
        Texture3D(const Texture3D&) = delete;
        Texture3D(Texture3D&&) = delete;
        ~Texture3D();

        //=================================================
        // Assignment operators
        //=================================================

        Texture3D& operator=(const Texture3D&) = delete;
        Texture3D& operator=(Texture3D&&) = delete;

        //=================================================
        // Resource mutators
        //=================================================

        void load(std::uint32_t w, std::uint32_t h, std::uint32_t d, Channel_format f, std::uint8_t* ptr);
        void load(std::uint32_t w, std::uint32_t h, std::uint32_t d, Channel_format f, std::uint16_t* ptr);
        void load(std::uint32_t w, std::uint32_t h, std::uint32_t d, Channel_format f, float* ptr);

        void unload();

        //=================================================
        // Accessors
        //=================================================

        [[nodiscard]]
        GLuint width() const;

        [[nodiscard]]
        GLuint height() const;

        [[nodiscard]]
        GLuint depth() const;

        [[nodiscard]]
        std::array<GLuint, 2> dimensions() const;

        [[nodiscard]]
        Channel_format channel_format() const;



    private:

        //=================================================
        // Instance members
        //=================================================

        std::array<std::uint32_t, 3> dims{};

        Primitive channel_type = Primitive::NULL_PRIMITIVE;
        Channel_format format = Channel_format::NULL_CHANNEL_FORMAT;

        //=================================================
        // Helper functions
        //=================================================

        void load(std::uint32_t w, std::uint32_t h, std::uint32_t d, Channel_format, Primitive p, void*);


    };

}


#endif //AGS_ARE_GL_TEXTURE_HPP
