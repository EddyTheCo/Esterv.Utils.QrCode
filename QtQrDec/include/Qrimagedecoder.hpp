#include<QObject>
#include<QString>
#include <QtQml/qqmlregistration.h>
#include<QImage>
#include<QBuffer>
#include <qquickimageprovider.h>

#ifndef USE_EMSCRIPTEN
#include <QMediaDevices>
#include <QCameraDevice>
#include <QCamera>
#include <QMediaCaptureSession>
#include <QVideoSink>
#include <thread>
#endif

#include <qrcodedec.hpp>


class QRImageDecoder : public QObject
{
    Q_OBJECT
    Q_PROPERTY(QString source READ get_source NOTIFY sourceChanged)
    Q_PROPERTY(bool useTorch MEMBER m_useTorch NOTIFY useTorchChanged)
    Q_PROPERTY(bool hasTorch MEMBER m_hasTorch NOTIFY hasTorchChanged)
    QML_ELEMENT
    QML_SINGLETON

    QRImageDecoder(QObject *parent = nullptr);
public:
    static QRImageDecoder* instance();
    static QRImageDecoder *create(QQmlEngine *qmlEngine, QJSEngine *jsEngine)
    {
        return instance();
    }
    enum State {
        Decoding = 0,
        Ready
    };
    Q_INVOKABLE void start();
    Q_INVOKABLE void stop();
    Q_INVOKABLE void clear();
    QString get_source(void)const{return m_source;}


     void reload(int offset, int width, int height);
signals:
     void decodedQR(QString);
    void sourceChanged();
    void hasTorchChanged();
    void useTorchChanged();
private:
    State m_state;
#ifndef USE_EMSCRIPTEN
    QCamera* m_camera;
    QMediaCaptureSession* captureSession;
    QVideoSink* videoSink;
    void getCamera(void);
#endif
    void setid();
    void decodePicture(QImage picture);
    QString m_source;
    QRDecoder detector;
    bool m_useTorch,m_hasTorch;
    static QRImageDecoder* m_instance;
};


class WasmImageProvider : public QQuickImageProvider
{
public:
    WasmImageProvider():QQuickImageProvider(QQuickImageProvider::Image)
    {
        restart();
    }
    QImage requestImage(const QString &id, QSize *size, const QSize &requestedSize) override;
    static void restart(void);
    static QImage img;
};

