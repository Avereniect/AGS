//
// Created by avereniect on 11/27/21.
//

#include <ags/image/Image.hpp>

namespace ags::image {

    Image::~Image() {}

    std::uint32_t Image::width() const {
        return w;
    }

    std::uint32_t Image::height() const {
        return h;
    }

    std::array<std::uint32_t, 2> Image::dimensions() const {
        return {w, h};
    }

    std::uint32_t Image::size() const {
        return w * h;
    }

    std::uint32_t Image::max_size() const {
        return std::numeric_limits<size_type>::max();
    }

    bool Image::empty() const {
        return (w == 0) || (h == 0);
    }

}
