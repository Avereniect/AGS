# Virtual_canvas
* a non-traditional image class breaking common assumptions about image representation
  * ill-defined boundaries
  * ill-defined resolution

## Technical Specification
### Dynamic boundaries
* the canvas is assumed to be white 
### Adaptive resolution
* the image is divided into fixed-size square tiles
  * exact size is something to optimize for performance
  * size should be a power of two for simplicity of implementation
* image resolution is dynamically increased for tiles being drawn to
  * texel density of the brushes should at least match the brush
* 