cmake_minimum_required(VERSION 3.16)

add_library(AGS_mesh STATIC
    include/ags/mesh/Attribute.hpp
    src/Attribute.cpp

    src/Dynamic_vertex_array.cpp
    src/Dynamic_vertex_array.hpp

    src/IO.cpp
    include/ags/mesh/IO.hpp

    src/Vertex_array.cpp
    include/ags/mesh/Vertex_array.hpp

    include/ags/mesh/Triangle_graph.hpp
)

target_compile_features(AGS_mesh PUBLIC cxx_std_17)

target_link_libraries(AGS_mesh
    PUBLIC AGS_core AUL
    PRIVATE assimp
)

target_include_directories(AGS_mesh
    PUBLIC ./include/
)
