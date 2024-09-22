#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include "esterv/utils/qr_image_decoder.hpp"

#if defined(FORCE_STYLE)
#include <QQuickStyle>
#endif

using namespace Esterv::Utils::QrDec;

int main(int argc, char *argv[])
{
	QGuiApplication app(argc, argv);

#if defined(FORCE_STYLE)
	QQuickStyle::setStyle(FORCE_STYLE);
#endif
	QQmlApplicationEngine engine;
	engine.addImageProvider(QLatin1String("wasm"), new WasmImageProvider());
	engine.addImportPath("qrc:/esterVtech.com/imports");
    const QUrl url=QUrl("qrc:/esterVtech.com/imports/Eqrtext/qml/qrtext.qml");

	engine.load(url);

	return app.exec();
}

