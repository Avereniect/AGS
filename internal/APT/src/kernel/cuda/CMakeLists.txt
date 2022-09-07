cmake_minimum_required(VERSION 3.16)

add_library(APT_CUDA STATIC
    Kernel_dispatch.cu
    Kernel_dispatch.cuh
)

target_link_libraries(APT_CUDA
    PUBLIC
)
