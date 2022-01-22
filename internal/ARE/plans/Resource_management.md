# Resource Management

## Single Render Queue
* object wrappers release resources when destroyed
* resource owned by object wrapper could be in render queue however
  * have object release resource to garbage pool managed by kernel
  * calls to glDelete* are made after the render queue has been cleared or 
    when the kernel shuts down

## Multiple Render Queues
* after destruction of object, resource could be queried in one or more queues
* resource could be kept alive by having objects release resource handles 
  into garbage pool
* no way to determine when it's safe to give the resource back to OpenGL 
  without additional information

### Possible Solutions
#### Avoid Multiple Queues
* multiple render queues could improve performance if the rendering engine 
  is used by multiple components
  * e.g. UI and 3D scene rendering would be able to fill their own render 
    queues in different threads independent of each other
#### Defer the responsibility to the user
* present a clean_up() method that will release resources in garbage pool 
  back to OpenGL
#### Make seperate sub-kernels
* resources are tied to a specific subkernel
* each subkernel features its own 
#### Use thread-local storage to create different queues?
* each thread maintains its own render queue
* resources can only be used in the thread which created them
* on destruction, resources handles are released to thread-specific 
#### Simply tell user to avoid this behavior
* resources should not be destroyed if queued up in render queue that is later 
  issued
* delaying destruction of resource could still be useful