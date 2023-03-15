#include "Texture.hpp"

namespace ags::are::vk_kernel {

    //=========================================================================
    // Texture1D
    //=========================================================================

    //=========================================================================
    // Texture2D
    //=========================================================================

    //=====================================================
    // Resource mutators
    //=====================================================

    void Texture2D::load(std::uint32_t w, std::uint32_t h, Channel_format f, std::uint8_t*) {

    }

    //=====================================================
    // Accessors
    //=====================================================

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

    Primitive Texture2D::channel_type() const {
        return type;
    }

    //=========================================================================
    // Texture3D
    //=========================================================================

}
