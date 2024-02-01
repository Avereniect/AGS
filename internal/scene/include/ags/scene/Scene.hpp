#ifndef AGS_SCENE_SCENE_HPP
#define AGS_SCENE_SCENE_HPP

#include <aul/containers/Slot_map.hpp>
#include <aul/Span.hpp>

#include "Camera.hpp"
#include "Mesh.hpp"
#include "Shader.hpp"
#include "Transform.hpp"
#include "Object.hpp"

#include "Scene_fwd.hpp"

namespace ags::scene {

    class Scene {
    public:

        //=================================================
        // -ctors
        //=================================================

        Scene() = default;
        Scene(const Scene&) = delete;
        Scene(Scene&&) = delete;
        ~Scene() = default;

        //=================================================
        // Assignment operators
        //=================================================

        Scene& operator=(const Scene&) = delete;
        Scene& operator=(Scene&&) noexcept = default;

        //=================================================
        // Accessors
        //=================================================



        //=================================================
        // Mutators
        //=================================================

    private:

        //=================================================
        // Instance members
        //=================================================

        aul::Slot_map<Object> objects;

        aul::Slot_map<Material> materials;

    };

}

#endif //AGS_SCENE_SCENE_HPP
