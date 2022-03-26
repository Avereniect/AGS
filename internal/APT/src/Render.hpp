//
// Created by avereniect on 12/22/21.
//

#ifndef AGS_RENDER_HPP
#define AGS_RENDER_HPP

#include "Common.hpp"
#include "Render_settings.hpp"
#include "Camera.hpp"
#include "Scene.hpp"

namespace ags::apt {

    Image render_scene(
        const Render_settings& settings,
        const Scene& scene
    );

}

#endif //AGS_RENDER_HPP
