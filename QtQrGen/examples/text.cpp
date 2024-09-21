#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include "esterv/utils/qr_image_provider.hpp"
#if defined(FORCE_STYLE)
#include <QQuickStyle>
#endif

using namespace Esterv::Utils::QrGen;

int main(int argc, char *argv[])
{
	QGuiApplication app(argc, argv);

#if defined(FORCE_STYLE)
	QQuickStyle::setStyle(FORCE_STYLE);
#endif
	QQmlApplicationEngine engine;
	engine.addImportPath("qrc:/esterVtech.com/imports");
    engine.addImageProvider(QLatin1String("qrcode"), new QRImageProvider(1));
    const QUrl url=QUrl("qrc:/esterVtech.com/imports/Etext/qml/text.qml");

	engine.load(url);

	return app.exec();
}

