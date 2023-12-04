# QrDec

This repo detect and decode a Qr code in a image.
The compiled library depends on [opencv](https://opencv.org/)

To use the library on your CMake  project 
```
include(FetchContent)
FetchContent_Declare(
	qrCode
	GIT_REPOSITORY git@github.com:EddyTheCo/qrCode.git
	GIT_TAG main
	FIND_PACKAGE_ARGS 0.4 COMPONENTS QrDec CONFIG  
)
FetchContent_MakeAvailable(qrCode)

target_link_libraries(<target> <PRIVATE|PUBLIC|INTERFACE> QrCode::QrDec)
```







