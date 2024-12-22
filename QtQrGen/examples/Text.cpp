#include "esterv/utils/qr_image_provider.hpp"
#include <QGuiApplication>
#include <QQmlApplicationEngine>
#if defined(FORCE_STYLE)
#include <QQuickStyle>
#endif

using namespace Esterv::Utils::QrGen;

int main(int argc, char *argv[]) {
  QGuiApplication app(argc, argv);

#if defined(FORCE_STYLE)
  QQuickStyle::setStyle(FORCE_STYLE);
#endif
  QQmlApplicationEngine engine;
  engine.addImportPath("qrc:/esterVtech.com/imports");
  engine.addImageProvider(QLatin1String("qrcode"), new QRImageProvider(1));

  engine.loadFromModule("ExamplesText", "Text");
  return app.exec();
}
