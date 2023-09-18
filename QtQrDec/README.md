# QtQrDec

This repo produce a library that can detect and decode QRCODEs.
The detection and decoding is performed by [OpenCV](https://opencv.org/) libraries.
In case OpenCV is not found on your system CMake will download precompiled libraries from [my action releases](https://github.com/EddyTheCo/install-OpenCV-action).

The library use [QtMultimedia](https://doc.qt.io/qt-6/qtmultimedia-index.html) if not compiling for wasm.
If compiling for wasm the library creates a custom ImageProvider that communicates with the browser.

You can play with the decoder on [this page](https://eddytheco.github.io/qmlonline/?example_url=qt_qr_dec)
 
An example on how to add the decoder to your project can be found on [this repository](https://github.com/EddyTheCo/qmlonline) (Only the parts enclosed in the USE_QtQr macros). 

In general CMake produce the target 'QtQrDec' so one can link to this library like
```
target_link_libraries(<target> <PRIVATE|PUBLIC|INTERFACE> QtQrDec)
```


## Using the decoder  on QML aplications will be as simple as
```
            QrTextArea
            {
                id:popup_
                width:300
                height:425
                anchors.centerIn: Overlay.overlay

                description: "Get data from QRCODE"
            }
```

For this to work one has to add the custom ImageProvider to the QML engine like in the following main.cpp
```
#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include "Qrimageprovider.hpp"

int main(int argc, char *argv[])
{
	QGuiApplication app(argc, argv);

	QQmlApplicationEngine engine;
#ifdef USE_EMSCRIPTEN
    engine.addImageProvider(QLatin1String("wasm"), new WasmImageProvider());
#endif
	const QUrl url(u"qrc:/app/main.qml"_qs);
	QObject::connect(&engine, &QQmlApplicationEngine::objectCreated,
			&app, [url](QObject *obj, const QUrl &objUrl) {
			if (!obj && url == objUrl)
			QCoreApplication::exit(-1);
			}, Qt::QueuedConnection);
	engine.load(url);

	return app.exec();
}
```






