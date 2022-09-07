//
// Created by avereniect on 9/1/22.
//
#include "Uniform_block.hpp"

namespace ags::are {

    //=========================================================================
    // Uniform_block_layout
    //=========================================================================

    bool operator<(const Uniform_block_layout& lhs, const Uniform_block_layout& rhs) {

    }

    //=========================================================================
    // Uniform_block
    //=========================================================================

    void Uniform_block_layout::specify_uniforms(const std::vector<Uniform>& uniforms) {

    }

    std::size_t Uniform_block::size_bytes() const {
        //TODO: Implement
    }

    std::size_t Uniform_block::uniform_count() const {
        //TODO: Implement
    }

}