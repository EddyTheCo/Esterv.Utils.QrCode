#include <QBuffer>
#include <QImage>
#include <QObject>
#include <QString>
#include <QtQml/qqmlregistration.h>
#include <qquickimageprovider.h>

#ifndef USE_EMSCRIPTEN
#include <QCamera>
#include <QCameraDevice>
#include <QMediaCaptureSession>
#include <QMediaDevices>
#include <QVideoSink>
#endif

#include <esterv/utils/qrcode_dec.hpp>

#if defined(QTQRDEC_SHARED)
#include <QtCore/QtGlobal>
#ifdef WINDOWS_EXPORT
#define DEC_EXPORT Q_DECL_EXPORT
#else
#define DEC_EXPORT Q_DECL_IMPORT
#endif
#else
#define DEC_EXPORT
#endif

namespace Esterv::Utils::QrDec {
class DEC_EXPORT QRImageDecoder : public QObject {
  Q_OBJECT
  Q_PROPERTY(QString source READ get_source NOTIFY sourceChanged)
  Q_PROPERTY(bool useTorch MEMBER m_useTorch NOTIFY useTorchChanged)
  Q_PROPERTY(bool hasTorch MEMBER m_hasTorch NOTIFY hasTorchChanged)
  QML_ELEMENT
  QML_SINGLETON

  QRImageDecoder(QObject *parent = nullptr);

public:
  static QRImageDecoder *instance();
  static QRImageDecoder *create(QQmlEngine *qmlEngine, QJSEngine *jsEngine) {
    return instance();
  }
  enum State { Decoding = 0, Ready };
  Q_INVOKABLE void start();
  Q_INVOKABLE void stop();
  Q_INVOKABLE void clear();
  QString get_source(void) const { return m_source; }

  void reload(int offset, int width, int height);
signals:
  void decodedQR(QString);
  void sourceChanged();
  void hasTorchChanged();
  void useTorchChanged();

private:
  State m_state;
#ifndef USE_EMSCRIPTEN
  QCamera *m_camera;
  QMediaCaptureSession *captureSession;
  QVideoSink *videoSink;
  void getCamera(void);
#endif
  void setid();
  void decodePicture(QImage picture);
  QString m_source;
  QRDecoder detector;
  bool m_useTorch, m_hasTorch;
  static QRImageDecoder *m_instance;
};

class DEC_EXPORT WasmImageProvider : public QQuickImageProvider {
public:
  WasmImageProvider() : QQuickImageProvider(QQuickImageProvider::Image) {
    restart();
  }
  QImage requestImage(const QString &id, QSize *size,
                      const QSize &requestedSize) override;
  static void restart(void);
  static QImage img;
};
} // namespace Esterv::Utils::QrDec
