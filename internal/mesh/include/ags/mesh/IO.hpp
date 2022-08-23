//
// Created by avereniect on 5/18/22.
//

#ifndef AGS_IO_HPP
#define AGS_IO_HPP

#include "../../../src/Dynamic_vertex_array.hpp"
#include "Vertex_array.hpp"

#include <string>

namespace ags::mesh {

    ///
    /// Vertex positions are given location 0
    /// Vertex normals are given location 1
    /// First UV map is given location 2
    ///
    /// \param path Path to file to read mesh from
    /// \return First mesh found within file as a Vertex_array object
    Vertex_array read_vertex_array(std::string_view path);

    Dynamic_vertex_array read_dynamic_vertex_array(const std::string& path);

}

#endif //AGS_IO_HPP
