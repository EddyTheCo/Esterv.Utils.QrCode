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
#include <qrcodedec.hpp>

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
    enum State {
        Decoding = 0,
        Ready
    };
    Q_INVOKABLE void start();
    Q_INVOKABLE void stop();

    QString get_text(void)const{return text;}
    QString get_source(void)const{return source;}

#ifdef USE_EMSCRIPTEN
    static QRImageDecoder* getdecoder(){return m_decoder;};
#endif
     void reload(int offset, int width, int height);
signals:
    void text_changed();
    void source_changed();
private:
    State m_state;
#ifdef USE_EMSCRIPTEN
    static QRImageDecoder* m_decoder;
#else
    QCamera* m_camera;
    QMediaCaptureSession* captureSession;
    QVideoSink* videoSink;
    void getCamera(void);
#endif
    void setid();
    void decodePicture(QImage picture);
    QString text,source;
    QRDecoder detector;
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

