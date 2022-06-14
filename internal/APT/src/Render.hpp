//
// Created by avereniect on 12/22/21.
//

#ifndef AGS_ARE_RENDER_HPP
#define AGS_ARE_RENDER_HPP

#include "Common.hpp"
#include "Render_settings.hpp"
#include "Camera.hpp"
#include "scene/Scene.hpp"

namespace ags::apt {

    ///
    /// \param settings Settings to be used for rendering
    /// \param scene Description of scene to be rendered
    /// \return Rendered image of scene following the specified settings
    Image render_scene(
        const Render_settings& settings,
        const Scene& scene
    );

}

#endif //AGS_ARE_RENDER_HPP
