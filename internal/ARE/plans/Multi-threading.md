# Multithreading considerations
TODO: 
* Work on Vulkan kernel and look into its multi-threading capabilities
* model multithreading integration on what Vulkan makes the natural solution

## Considerations
* an OpenGL context can only be active in one thread at a time
* different contexts can be active in different thread at the same time
* constructing a resource means acquiring a resource handle, which requires 
  that the context be active in the current thread
* manipulating OpenGL objects requires an active rendering context
* 

## Solution
### Single context on a single thread
* building of render queue can still be done on one thread

### Multiple threads, each with their own context
* each thread that will interact with ARE needs to have its own OpenGL context
* 