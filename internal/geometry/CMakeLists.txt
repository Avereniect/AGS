cmake_minimum_required(3.16)

add_library(AGS_GEOMETRY STATIC
    include/ags/geometry/Ray.hpp
)

target_link_libraries(AGS_GEOMETRY PRIVATE avml)
target_include_directories(AGS_GEOMETRy PUBLIC include)