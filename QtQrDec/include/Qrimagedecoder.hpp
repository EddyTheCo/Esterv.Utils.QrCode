#include<QObject>
#include<QString>
#include <QtQml/qqmlregistration.h>
#include<QImage>
#include<QBuffer>
#include <qquickimageprovider.h>
#include <QMediaDevices>
#include <QCameraDevice>
#include <QCamera>
#include <QMediaCaptureSession>
#include <QVideoSink>
//foo namespace to force the linker to link the backing library composed only of qml files
namespace fooQtQrDec
{
QString fooPrint(void);
};

class QRImageDecoder : public QObject
{
    Q_OBJECT
    Q_PROPERTY(QString text READ get_text NOTIFY text_changed)
    Q_PROPERTY(QString source READ get_source NOTIFY source_changed)
    QML_ELEMENT
    QML_SINGLETON
public:
    QRImageDecoder(QObject *parent = nullptr);

#ifdef USE_EMSCRIPTEN
    Q_INVOKABLE void start()const;
    Q_INVOKABLE void stop()const;
#endif
    Q_INVOKABLE void start();
    Q_INVOKABLE void stop(){};

    QString get_text(void)
    {
        return text;
    }
    QString get_source(void)
    {
        return source;
    }

#ifdef USE_EMSCRIPTEN
    static QRImageDecoder* getdecoder(){return m_decoder;};

#endif
     void reload(int offset, int width, int height);
signals:
    void text_changed();
    void source_changed();
private:
#ifdef USE_EMSCRIPTEN
    static QRImageDecoder* m_decoder;
#endif
    void setid();
    void getCamera(void);
    void decodePicture(QImage picture);
    QString text,source;
    QCamera* m_camera;
    QMediaCaptureSession* captureSession;
    QVideoSink* videoSink;
};


class WasmImageProvider : public QQuickImageProvider
{
public:
    WasmImageProvider():QQuickImageProvider(QQuickImageProvider::Image)
    {

    }
    QImage requestImage(const QString &id, QSize *size, const QSize &requestedSize) override;
    static QImage img;
};

