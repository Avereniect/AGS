//
// Created by avereniect on 1/1/22.
//

#ifndef AGS_GL33_MESH_HPP
#define AGS_GL33_MESH_HPP

#include "Object.hpp"

#include <ags/Mesh.hpp>

namespace ags::are::gl33 {

    class Mesh : public Object {
    public:

        //=================================================
        // -ctors
        //=================================================

        Mesh() = default;
        Mesh(const Mesh&) = default;
        Mesh(Mesh&&) = delete;
        ~Mesh();

        //=================================================
        // Assignment operators
        //=================================================

        Mesh& operator=(const Mesh&) = delete;
        Mesh& operator=(Mesh&&) = default;

        //=================================================
        // Buffer mutators
        //=================================================

        void load(mesh::Fixed_vertex_array_view view);

        ///
        /// Releases currently held resource if exists
        ///
        void unload();

        //=================================================
        // Accessors
        //=================================================



    private:

        //=================================================
        // Instance members
        //=================================================

        GLuint position_buffer = 0;
        GLuint normal_buffer = 0;
        GLuint tangent_buffer = 0;
        GLuint uv0_buffer = 0;

    };

}

#endif //AGS_GL33_MESH_HPP
