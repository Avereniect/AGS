
__global__ void render_kernel() {


}


void kernel_dispatch() {
    dim3 grid_size{};
    dim3 block_size{};

    render_kernel<<<grid_size, block_size>>>();
}
