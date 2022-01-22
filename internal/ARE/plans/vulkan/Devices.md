# Devices
## Solution
* up to three devices are chosen
* may not be unique in practice
### Graphics Device
* used for all rendering tasks
* the most powerful device found for rendering graphics

### Light Compute Device
* used for light general-purpose compute tasks
* integrated graphics card if available
  * if not, CPU device if available
  * if not, then dedicated GPU will be used 
  
If the light compute device is an integrated graphics card and the heavy 
compute device is a dedicated graphics card, then it may be faster to have 
the iGPU perform some work since it shares the memory with the CPU and 
there would be no need to wait for a transfer, or it may be much cheaper to 
copy it in the first place  

This allows the program to take advantage of integrated graphics card, and 
access a greater portion of the machine's power 

### Heavy Compute Device
* used for heavy general-purpose compute tasks
* secondary dedicated graphics card if available
  * first dedicated graphics card if available