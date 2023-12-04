# QtQrDec

This repo produce a QML Module with custom types that can detect and decode QRCODEs.
The detection and decoding is performed by [OpenCV](https://opencv.org/) libraries.
In case OpenCV is not found on your system CMake will download pre compiled libraries from [my action releases](https://github.com/EddyTheCo/install-OpenCV-action).

The library use [QtMultimedia](https://doc.qt.io/qt-6/qtmultimedia-index.html) if not compiling for wasm.
If compiling for wasm the library creates a custom ImageProvider that communicates with the browser.

You can play with the decoder on [this page](https://eddytheco.github.io/qmlonline/?example_url=qt_qr_dec)
 

To use the library on your CMake  project 
```
include(FetchContent)
FetchContent_Declare(
	qrCode
	GIT_REPOSITORY git@github.com:EddyTheCo/qrCode.git
	GIT_TAG main
	FIND_PACKAGE_ARGS 0.4 COMPONENTS QtQrDec CONFIG  
)
FetchContent_MakeAvailable(qrCode)

target_link_libraries(<target> <PRIVATE|PUBLIC|INTERFACE> QrCode::QtQrDec)
```


