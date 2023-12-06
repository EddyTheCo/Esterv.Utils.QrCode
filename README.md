# qrCode

This repository is intended to provide a library for working with QR codes from c++. The main purpose is to exploit modern CMake and facilitate reuse and develop.
The GUI part will be based on Qt libraries and QML. Examples of this library compiled for WebAssembly can be found on:
- [QtQrGen](https://eddytheco.github.io/qmlonline/?example_url=qt_qr_gen)
- [QtQrDec](https://eddytheco.github.io/qmlonline/?example_url=qt_qr_dec)

## Adding the libraries to your CMake project will be as easy as

```CMake
include(FetchContent)
	FetchContent_Declare(
			qrCode
			GIT_REPOSITORY git@github.com:EddyTheCo/qrCode.git
			GIT_TAG v0.1.2 
			FIND_PACKAGE_ARGS 0.1 CONFIG  
 			)
FetchContent_MakeAvailable(qrCode)

target_link_libraries(<target> <PRIVATE|PUBLIC|INTERFACE> qrCode::QrGen qrCode::QtQrGen qrCode::QrDec qrCode::QtQrDec)
```
For more information check

- [QrGen] (QrGen/README.md)
- [QrDec] (QrDec/README.md)
- [QtQrGen](QtQrGen/README.md)
- [QtQrDec](QtQrDec/README.md)
