//
// Created by avereniect on 12/22/21.
//

#include "Common.hpp"
#include "Render.hpp"

namespace ags::apt {

    colorv trace_background(uvec3rv dir) {
        ;
    }

    colorv trace_ray(vec3r origin, uvec3rv dir) {
        return trace_background(dir);
    }

    Image render_scene(
        const Render_settings& settings,
        const Scene& scene
    ) {
        //TODO: Set up camera rays

    }

}
