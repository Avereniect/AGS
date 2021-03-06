//
// Created by avereniect on 1/9/22.
//

#ifndef AGS_GL43_MESH_KERNEL_HPP
#define AGS_GL43_MESH_KERNEL_HPP

#include <glad/glad.h>

#include <vector>

namespace ags::are::gl43 {

    class Mesh_kernel {
    public:

        static void init();
        static void term();

    private:

        static std::vector<GLuint> mesh_garbage;
        static std::vector<GLuint> mesh_pool;

    };

}

#endif //AGS_GL43_MESH_KERNEL_HPP
