# QrGen

The code is based on [QR Code generator library](https://github.com/nayuki/QR-Code-generator) and produce a library for the generation of a QR code of certain data.

To use the library on your CMake  project 
```
include(FetchContent)
FetchContent_Declare(
	qrCode
	GIT_REPOSITORY git@github.com:EddyTheCo/qrCode.git
	GIT_TAG main
	FIND_PACKAGE_ARGS 0.4 COMPONENTS QrGen CONFIG  
)
FetchContent_MakeAvailable(qrCode)

target_link_libraries(<target> <PRIVATE|PUBLIC|INTERFACE> QrCode::QrGen)
```







