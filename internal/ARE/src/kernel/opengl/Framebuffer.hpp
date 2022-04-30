//
// Created by avereniect on 4/30/22.
//

#ifndef AGS_FRAMEBUFFER_HPP
#define AGS_FRAMEBUFFER_HPP

#include "Object.hpp"
#include "../Framebuffer.hpp"

#include <cstdint>
#include <array>

namespace ags::are::gl43 {

    class Framebuffer : public Object {
    public:

        static constexpr std::uint32_t max_color_attachments = 16;

        //=================================================
        // -ctors
        //=================================================

        Framebuffer() = default;
        Framebuffer(const Framebuffer&) = delete;
        ~Framebuffer();

        //=================================================
        // Assignment operators
        //=================================================

        Framebuffer& operator=(const Framebuffer&) = delete;

        //=================================================
        // Mutators
        //=================================================

        void create_buffer(
            std::uint32_t w, std::uint32_t h,
            std::initializer_list<Color_attachment> color_attachments
        );

        void create_buffer(
            std::uint32_t w, std::uint32_t h,
            std::initializer_list<Color_attachment> color_attachments,
            Depth_format format
        );

        void create_buffer(
            std::uint32_t w, std::uint32_t h,
            std::initializer_list<Color_attachment> color_attachments,
            Stencil_format format
        );

        void create_buffer(
            std::uint32_t w, std::uint32_t h,
            std::initializer_list<Color_attachment> color_attachments,
            Depth_stencil_format format
        );

        void unload();

        //=================================================
        // Accessors
        //=================================================

        [[nodiscard]]
        std::array<std::uint32_t, 2> dimensions() const;

        [[nodiscard]]
        std::uint32_t width() const;

        [[nodiscard]]
        std::uint32_t height() const;

    private:

        //=================================================
        // Instance members
        //=================================================

        std::array<std::uint32_t, 2> dims{0, 0};

        std::array<Color_attachment, max_color_attachments> color_attachment;

        //=================================================
        // Helper functions
        //=================================================

        void verify() const;

    };

}

#endif //AGS_FRAMEBUFFER_HPP
