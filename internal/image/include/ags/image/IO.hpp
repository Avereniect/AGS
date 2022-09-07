//
// Created by avereniect on 5/27/22.
//

#ifndef AGS_IMAGE_IO_HPP
#define AGS_IMAGE_IO_HPP

#include "Pixel_buffer.hpp"

#include <memory>
#include <string_view>

namespace ags::image {

    ///
    /// Reads and returns a PNG image.
    ///
    /// Returned image is empty upon failure.
    ///
    /// Color space of returned image is canonically sRGB.
    ///
    /// Canonically, the channels contains the following information.
    /// 1 channel  - color value
    /// 2 channels - color value, alpha
    /// 3 channels - red, green, blue
    /// 4 channels - red, green, blue, alpha
    ///
    /// \param path PNG file path
    /// \return Pixel_buffer containing image.
    std::unique_ptr<Image> read_png(std::string_view path);

    void write_png(const Pixel_buffer<std::uint8_t, 1>&, std::string_view path);
    void write_png(const Pixel_buffer<std::uint8_t, 2>&, std::string_view path);
    void write_png(const Pixel_buffer<std::uint8_t, 3>&, std::string_view path);
    void write_png(const Pixel_buffer<std::uint8_t, 4>&, std::string_view path);

    void write_png(const Pixel_buffer<std::uint16_t, 1>&, std::string_view path);
    void write_png(const Pixel_buffer<std::uint16_t, 2>&, std::string_view path);
    void write_png(const Pixel_buffer<std::uint16_t, 3>&, std::string_view path);
    void write_png(const Pixel_buffer<std::uint16_t, 4>&, std::string_view path);

}

#endif //AGS_IMAGE_IO_HPP
