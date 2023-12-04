# QtQrGen

This code produce a QML module with custom types and a custom ImageProvider of Qt.
The custom types are related to the generation and showing of QRCODEs.

You can play with the  ImageProvider on [this page](https://eddytheco.github.io/qmlonline/?example_url=qt_qr_gen).


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
