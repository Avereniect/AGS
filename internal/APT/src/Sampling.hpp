//
// Created by avereniect on 6/18/22.
//

#ifndef AGS_APT_SAMPLING_HPP
#define AGS_APT_SAMPLING_HPP

#include "Common.hpp"
#include "Random.hpp"

namespace ags::apt {

    // Progressive Jittered Sampling
    //

    class Jittered_sampling_tree {
    public:

        //=================================================
        // Helper structs
        //=================================================

        struct Node {
            vec2r location;
            uint32 count = 0;

            Node* children[4];
        };

        //=================================================
        // Type Aliases
        //=================================================

        using size_type = std::size_t;

        //=================================================
        // -ctors
        //=================================================



        //=================================================
        // Assignment Operators
        //=================================================



        //=================================================
        // Accessors
        //=================================================



        //=================================================
        // Mutators
        //=================================================

        vec2r generate_sample_location();

    private:

        //=================================================
        // Instance Members
        //=================================================

        Node* root = nullptr;

        Rand24 generator{};

    };

}

#endif //AGS_APT_SAMPLING_HPP
