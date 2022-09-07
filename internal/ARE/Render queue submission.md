# Render Queue Submission

## Requirements:
### Functional requirements
* need a convenient way to enqueue draw calls, mesh, shader, and framebuffer
* it should be possible to reuse a render queue once drawn once
* should be possible to check compatability between mesh, shader, and 
  framebuffer 
* ability to specify viewport location and dimensions

### Technical requirements

## Potential Solutions:
### Solution 0
* mesh, shader, and framebuffer are all submitted to an `enqueue()` function 
  simultaneously
* queue may simply be submitted multiple times
* compatability check occurs when submitting queue
* viewport dimensions and location are submitted when submitting the render 
  queue
### Solution 1
* queue using framebuffer as parameter to constructor
* `enqueue()` calls only take mesh and shader
* compatability check occurs when submitting queue
* viewport dimensions and location are submitted when submitting the render 
  queue
### Solution 2
* `enqueue()` calls take mesh, shader
* `draw()` takes framebuffer as parameter

