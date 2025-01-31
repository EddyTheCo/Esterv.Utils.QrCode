# Esterv.CustomControls.QrDec

[TOC] 

This repo produce a QML Module with custom types that can detect and decode QRCODEs.

The types should be style independent, but the colors used relies on the [EstervDesigns](https://github.com/EddyTheCo/Esterv.Designs)
Simple style. 
If you want to change the colors in your top qml file one can do
```
import Esterv.Styles.Simple
...

Component.onCompleted:
{
Style.frontColor1= (Style.theme)?LightThemeColor:DarkThemeColor //Like control.palette.text

Style.frontColor2= ...
Style.frontColor3= ...

Style.backColor1= ...
Style.backColor2= ...
Style.backColor3= ...
}

``` 
The detection and decoding is performed by [OpenCV](https://opencv.org/) libraries.
In case OpenCV is not found on your system CMake will download pre compiled libraries from [my action releases](https://github.com/EddyTheCo/install-OpenCV-action).

The library use [QtMultimedia](https://doc.qt.io/qt-6/qtmultimedia-index.html) if not compiling for wasm.
If compiling for wasm the library creates a custom ImageProvider that communicates with the browser.

You can play with the decoder on [this page](https://eddytheco.github.io/qmlonline/?example_url=qt_qr_dec)
 

## Adding the module to your CMake project

```
include(FetchContent)
FetchContent_Declare(
	EstervQrCode
	GIT_REPOSITORY https://github.com/EddyTheCo/Esterv.Utils.QrCode.git
	GIT_TAG vMAJOR.MINOR.PATCH
	FIND_PACKAGE_ARGS MAJOR.MINOR COMPONENTS QtQrDec CONFIG
)
FetchContent_MakeAvailable(EstervQrCode)

target_link_libraries(<target> <PRIVATE|PUBLIC|INTERFACE> Esterv::QtQrDec)
target_link_libraries(<target> <PRIVATE|PUBLIC|INTERFACE> $<$<STREQUAL:$<TARGET_PROPERTY:Esterv::QtQrDec,TYPE>,STATIC_LIBRARY>:Esterv::QtQrDecplugin>)
```


## Examples

The [examples](examples) folder shows the use of the different custom types provided by the QML module.



## Contributing

We appreciate any contribution!


You can open an issue or request a feature also.
You can open a PR to the `develop` branch and the CI/CD will take care of the rest.
Make sure to acknowledge your work, ideas when contributing.

