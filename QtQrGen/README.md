#QtQrGen

This code produce a library with a custom ImageProvider of Qt. The image provider print a QRCODE from a string.
CMake produce the target 'QtQrGen' so one can link to this library like
```
target_link_libraries(<target> <PRIVATE|PUBLIC|INTERFACE> QtQrGen)
```


## Showing the QRCODE on QML aplications will be simple as 

```
Image {
        sourceSize.width: 300
        source: "image://qrcode/https://eddytheco.github.io/"
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
    engine.addImageProvider(QLatin1String("qrCode"), new QRImageProvider("blue",1));
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


