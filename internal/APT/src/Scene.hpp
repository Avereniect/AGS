//
// Created by avereniect on 12/22/21.
//

#ifndef AGS_SCENE_HPP
#define AGS_SCENE_HPP

#include "Common.hpp"
#include "Camera.hpp"

namespace ags::apt {

    struct Object {
        whole mesh_index;
        whole material_index;
    };

    struct Material {

    };

    struct Mesh {
        whole indices;
        whole coordinates;
        whole normals;
        whole uvs;
    };

    struct Scene {
        Camera camera;

        std::vector<whole> indices;

        std::vector<real> coordinates;
        std::vector<real> normals;
        std::vector<real> uvs;
    };

}

#endif //AGS_SCENE_HPP
