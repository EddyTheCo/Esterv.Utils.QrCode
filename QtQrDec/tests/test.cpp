#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include "Qrimagedecoder.hpp"
#include<iostream>



int main(int argc, char *argv[])
{
    qmlRegisterSingletonType<QRImageDecoder>("Qrdecoder", 1, 0, "CodeDec",
            [](QQmlEngine *engine, QJSEngine *scriptEngine) -> QObject * {
            Q_UNUSED(engine)
            Q_UNUSED(scriptEngine)
            return new QRImageDecoder();
            });
	QGuiApplication app(argc, argv);

	QQmlApplicationEngine engine;
    const QUrl url(u"qrc:/appqml/main.qml"_qs);
	QObject::connect(&engine, &QQmlApplicationEngine::objectCreated,
			&app, [url](QObject *obj, const QUrl &objUrl) {
			if (!obj && url == objUrl)
			QCoreApplication::exit(-1);
			}, Qt::QueuedConnection);
	engine.load(url);

	return app.exec();
}
