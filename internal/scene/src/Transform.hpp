//
// Created by avereniect on 8/30/22.
//

#ifndef AGS_SCENE_TRANSFORM_HPP
#define AGS_SCENE_TRANSFORM_HPP

#include <avml/AVML.hpp>

namespace ags::scene {

    class Transform {
    public:

        //=================================================
        // -ctors
        //=================================================

        Transform() = default;
        ~Transform() = default;

        //=================================================
        // Assignment operators
        //=================================================



        //=================================================
        // Assignment operators
        //=================================================

    private:

        //=================================================
        // Instance members
        //=================================================

        avml::vec3f position{0.0f, 0.0f, 0.0f};

        avml::vec3f rotation{0.0f, 0.0f, 0.0f};

        avml::vec3f scale{1.0f, 1.0f, 1.0f};

        avml::mat4x4f matrix{1.0f};

    };



}

#endif //AGS_SCENE_TRANSFORM_HPP
