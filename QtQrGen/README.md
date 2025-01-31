# Esterv.CustomControls.QrGen

[TOC]

This code produce a QML module with custom types and a custom ImageProvider of Qt.
The custom types are related to the generation and showing of QRCODEs.


The types should be style independent, but the colors used relies on the [EstervDesigns](https://github.com/EddyTheCo/MyDesigns)
Simple style.
If you want to change the colors in your top qml file one can do

```
import Esterv.Styles.Simple
...

Component.onCompleted:
{
Style.frontColor1= (Style.theme)?LightThemeColor:DarkThemeColor//Like control.palette.text

Style.frontColor2= ...
Style.frontColor3= ...

Style.backColor1= ...
Style.backColor2= ...
Style.backColor3= ...
}

``` 

You can play with the  ImageProvider on [this page](https://eddytheco.github.io/qmlonline/?example_url=qt_qr_gen).


## Adding the module to your CMake project

```
include(FetchContent)
FetchContent_Declare(
	EstervQrCode
	GIT_REPOSITORY https://github.com/EddyTheCo/Esterv.Utils.QrCode.git
	GIT_TAG vMAJOR.MINOR.PATCH 
	FIND_PACKAGE_ARGS MAJOR.MINOR COMPONENTS QtQrGen CONFIG
)
FetchContent_MakeAvailable(EstervQrCode)

target_link_libraries(<target> <PRIVATE|PUBLIC|INTERFACE> Esterv::QtQrGen)
target_link_libraries(<target> <PRIVATE|PUBLIC|INTERFACE> $<$<STREQUAL:$<TARGET_PROPERTY:Esterv::QtQrGen,TYPE>,STATIC_LIBRARY>:Esterv::QtQrGenplugin>)
```

## Examples

The [examples](examples) folder shows the use of the different custom types provided by the QML module.

## Contributing

We appreciate any contribution!


You can open an issue or request a feature also.
You can open a PR to the `develop` branch and the CI/CD will take care of the rest.
Make sure to acknowledge your work, ideas when contributing.

