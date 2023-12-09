#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include "Qrimagedecoder.hpp"

#if defined(FORCE_STYLE)
#include <QQuickStyle>
#endif
int main(int argc, char *argv[])
{
	QGuiApplication app(argc, argv);

#if defined(FORCE_STYLE)
	QQuickStyle::setStyle(FORCE_STYLE);
#endif
	QQmlApplicationEngine engine;
	engine.addImageProvider(QLatin1String("wasm"), new WasmImageProvider());
	engine.addImportPath("qrc:/esterVtech.com/imports");
	const QUrl url=QUrl("qrc:/esterVtech.com/imports/Eqrcam/qml/qrcam.qml");

	engine.load(url);

	return app.exec();
}

