# qrCode

This repository is intended to provide a library for working with QR codes from c++. The main purpose is to exploit modern CMake and facilitate reuse and develop.
The GUI part will be based on Qt libraries and QML;

## Adding the libraries to your CMake project will be as easy as

```CMake
include(FetchContent)
	FetchContent_Declare(
			qrCode
			GIT_REPOSITORY git@github.com:EddyTheCo/qrCode
			GIT_TAG main
			)
FetchContent_MakeAvailable(qrCode)

target_link_libraries(<target> <PRIVATE|PUBLIC|INTERFACE> QrGen QtQrGen)
```



