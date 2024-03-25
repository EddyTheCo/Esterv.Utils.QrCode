# QrDec

This repo detect and decode a Qr code in a image.
The detection and decoding is performed by [OpenCV](https://opencv.org/) libraries.
In case OpenCV is not found on your system CMake will download pre compiled libraries from [my action releases](https://github.com/EddyTheCo/install-OpenCV-action).

## Adding the libraries to your CMake project 
```
include(FetchContent)
FetchContent_Declare(
	qrCode
	GIT_REPOSITORY https://github.com/EddyTheCo/qrCode.git
	GIT_TAG vMAJOR.MINOR.PATCH 
	FIND_PACKAGE_ARGS MAJOR.MINOR COMPONENTS QrDec CONFIG  
)
FetchContent_MakeAvailable(qrCode)

target_link_libraries(<target> <PRIVATE|PUBLIC|INTERFACE> qrCode::QrDec)
```







