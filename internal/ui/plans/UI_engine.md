# UI Engine

## Functional Specification
* responsible for initialization, termination, and general management of GLFW library state
* must be initialized prior to modules which require rendering context (e.g. ARE)
* must offer GPU accelerate UI rendering capabilities

## Technical Specification
### Context Management
* each window has its own rendering context associated with it by design of the GLFW library
* ARE will manage GLFW contexts that are used for rendering
  * these contexts will be hidden windows
* contents of framebuffers 
### 
* 