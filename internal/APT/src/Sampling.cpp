//
// Created by avereniect on 6/18/22.
//
#include "Sampling.hpp"

namespace ags::apt {

    using size_type = Jittered_sampling_tree::size_type;

    vec2r Jittered_sampling_tree::generate_sample_location() {
        if (root == nullptr) {
            root = new Node{};
            root->count = 1;
            root->location = {generator.get_float(), generator.get_float()};
        }


    }

}
