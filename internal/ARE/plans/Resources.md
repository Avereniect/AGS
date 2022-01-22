# Resource classes
* wrap API specific resources (e.g. textures, meshes, shaders, framebuffers)
* each kernel provides its own resource classes
* explicit use of underlying API is avoided through the use of the Kernel 
  classes
* 

## Problem: polymorphism should be avoided
* OpenGL resource handles are 32-bit integers
* Vulkan handles are pointers or 64-bit integers (up to configuration)
* 