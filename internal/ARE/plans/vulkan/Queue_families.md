# Queue Families

## Solution
* each device
### Graphics Device
* two queues
  * rendering queue
    * used for issuing rendering commands
  * compute queue
    * used for issuing general-purpose compute tasks meant to support the 
      rendering process
  * transfer queue
    * used to perform asynchronous transfers of data
### Light Compute Device
* two queues
  * compute queue
    * used for light-weight general-purpose computer tasks
  * transfer queue
### Heavy Compute Device
* two queues
  * compute queue
  * transfer queue

## Considerations
### Nvidia
* typically offers three queue families
  * one that can do anything
  * one that can anything but present
  * one that can only be used for transfering
### AMD
* typically offers three queue families
  * one that can do anything
  * one that that can do anything but graphics
  * one that do anything but graphics and compute
### Intel
* usually offers a single queue family
  * used for everything