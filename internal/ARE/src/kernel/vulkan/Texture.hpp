#ifndef AGS_ARE_VK_TEXTURE_HPP
#define AGS_ARE_VK_TEXTURE_HPP

#include <ags/Graphics_includes.hpp>
#include <ags/Types.hpp>

#include "Enums.hpp"

namespace ags::are::vk_kernel {

    class Texture1D {
    public:

    private:

    };

    class Texture2D {
    public:

        //=================================================
        // -ctors
        //=================================================

        Texture2D() = default;
        ~Texture2D() = default; //TODO: Provide proper implementation

        //=================================================
        // Assignment Operators
        //=================================================

        //=================================================
        // Resource mutators
        //=================================================

        void load(std::uint32_t w, std::uint32_t h, Channel_format f, std::uint8_t*);
        void load(std::uint32_t w, std::uint32_t h, Channel_format f, std::uint16_t*);
        void load(std::uint32_t w, std::uint32_t h, Channel_format f, float*);

        //=================================================
        // Accessors
        //=================================================

        [[nodiscard]]
        std::uint32_t width() const;

        [[nodiscard]]
        std::uint32_t height() const;

        [[nodiscard]]
        std::array<std::uint32_t, 2> dimensions() const;

        [[nodiscard]]
        Channel_format channel_format() const;

        [[nodiscard]]
        Primitive channel_type() const;

    private:

        //=================================================
        // Instance members
        //=================================================

        vk::Image handle{};

        std::array<std::uint32_t, 2> dims{};

        Primitive type = Primitive::NULL_PRIMITIVE;
        Channel_format format = Channel_format::NULL_CHANNEL_FORMAT;

    };

    class Texture3D {
    public:

    private:

    };

}

#endif //AGS_ARE_VK_TEXTURE_HPP
