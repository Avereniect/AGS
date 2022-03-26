//
// Created by avereniect on 3/26/22.
//
#include "Enums.hpp"

namespace ags::are {

    Depth_stencil_format to_depth_stencil_format(Depth_format d) {
        return Depth_stencil_format{d};
    }

    Depth_stencil_format to_depth_stencil_format(Stencil_format s) {
        return Depth_stencil_format{s};
    }

    Depth_stencil_format to_depth_stencil_format(Depth_stencil_format d, Stencil_format s) {
        return Depth_stencil_format{std::uint8_t(std::uint8_t(d) | std::uint8_t(s))};
    }

    Depth_format to_depth_format(Depth_stencil_format ds) {
        return Depth_format{std::uint8_t(std::uint8_t(ds) & 0x06)};
    }

    Stencil_format to_stencil_format(Depth_stencil_format ds) {
        return Stencil_format{std::uint8_t(std::uint8_t(ds) & 0x01)};
    }

}
