#include "esterv/utils/qr_image_decoder.hpp"
#include <QGuiApplication>
#include <QQmlApplicationEngine>

#if defined(FORCE_STYLE)
#include <QQuickStyle>
#endif

using namespace Esterv::Utils::QrDec;

int main(int argc, char *argv[]) {
  QGuiApplication app(argc, argv);

#if defined(FORCE_STYLE)
  QQuickStyle::setStyle(FORCE_STYLE);
#endif
  QQmlApplicationEngine engine;
  engine.addImageProvider(QLatin1String("wasm"), new WasmImageProvider());
  engine.addImportPath("qrc:/esterVtech.com/imports");
  engine.loadFromModule("ExamplesQrcam", "Qrcam");

  return app.exec();
}
