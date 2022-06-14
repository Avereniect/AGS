//
// Created by avereniect on 12/22/21.
//

#ifndef AGS_ARE_SCENE_HPP
#define AGS_ARE_SCENE_HPP

#include "../Common.hpp"
#include "../Camera.hpp"

namespace ags::apt {

    struct Object {
        int32 mesh_index;
        int32 material_index;
    };

    struct Material {

    };

    struct Mesh {
        int32 indices;
        int32 coordinates;
        int32 normals;
        int32 uvs;
    };

    struct Scene {
        Camera camera;

        std::vector<int32> indices;

        std::vector<real> coordinates;
        std::vector<real> normals;
        std::vector<real> uvs;
    };

}

#endif //AGS_ARE_SCENE_HPP
