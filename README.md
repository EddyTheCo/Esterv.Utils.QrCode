# Esterv.Utils.QrCode 

[TOC]

This repository is intended to provide a library for working with QR codes from c++. The main purpose is to exploit modern CMake and facilitate reuse and develop.

The GUI part will be based on Qt libraries and QML. Examples of this library compiled for Web Assembly can be found on:
- [QtQrGen](https://eddytheco.github.io/qmlonline/?example_url=qt_qr_gen)
- [QtQrDec](https://eddytheco.github.io/qmlonline/?example_url=qt_qr_dec)

## Configure, build, test, package ...

The project uses [CMake presets](https://cmake.org/cmake/help/latest/manual/cmake-presets.7.html) as a way to share CMake configurations.
Refer to [cmake](https://cmake.org/cmake/help/latest/manual/cmake.1.html), [ctest](https://cmake.org/cmake/help/latest/manual/ctest.1.html) and [cpack](https://cmake.org/cmake/help/latest/manual/cpack.1.html) documentation for more information on the use of presets.


## Adding the libraries to your CMake project

```CMake
include(FetchContent)
FetchContent_Declare(
	EstervQrCode
	GIT_REPOSITORY https://github.com/EddyTheCo/Esterv.Utils.QrCode.git
	GIT_TAG vMAJOR.MINOR.PATCH 
	FIND_PACKAGE_ARGS MAJOR.MINOR COMPONENTS QrDec QrGen QtQrDec QtQrGen CONFIG
	)
FetchContent_MakeAvailable(EstervQrCode)

target_link_libraries(<target> <PRIVATE|PUBLIC|INTERFACE> Esterv::QrGen Esterv::QtQrGen Esterv::QrDec Esterv::QtQrDec)
```
For more information check

- [QrGen](QrGen/README.md)
- [QrDec](QrDec/README.md)
- [QtQrGen](QtQrGen/README.md)
- [QtQrDec](QtQrDec/README.md)

## API reference

You can read the [API reference](https://eddytheco.github.io/Esterv.Utils.QrCode/), or generate it yourself like
```
cmake --workflow --preset default-documentation
```

## Contributing

We appreciate any contribution!


You can open an issue or request a feature.
You can open a PR to the `develop` branch and the CI/CD will take care of the rest.
Make sure to acknowledge your work, and ideas when contributing.

