//
// Created by avereniect on 8/27/22.
//

#ifndef AGS_IMAGE_PIXEL_BUFFER_TESTS_HPP
#define AGS_IMAGE_PIXEL_BUFFER_TESTS_HPP

#include <cstdlib>

#include <memory>

#include <ags/image/Pixel_buffer.hpp>

using ags::image::Image;
using ags::image::Pixel_buffer;
using ags::image::Pixel_buffer_common;

int main() {
    std::unique_ptr<Pixel_buffer_common<std::uint8_t, 3>> image = std::make_unique<Pixel_buffer<std::uint8_t, 3>>(512, 512);


    return EXIT_SUCCESS;
}

#endif //AGS_IMAGE_PIXEL_BUFFER_TESTS_HPP
