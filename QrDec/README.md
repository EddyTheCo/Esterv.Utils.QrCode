# QrGen

This repo detect and decode a Qr code in a image.
The compiled library depend on [opencv](https://opencv.org/)
 
CMake produce the target 'QrDec' so one can link to this library like
```
target_link_libraries(<target> <PRIVATE|PUBLIC|INTERFACE> QrDec)
```







