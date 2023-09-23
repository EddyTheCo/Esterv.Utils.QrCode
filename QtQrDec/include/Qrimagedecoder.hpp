#include<QObject>
#include<QString>
#include <QtQml/qqmlregistration.h>
#include<QImage>
#include<QBuffer>
#ifdef USE_EMSCRIPTEN
#include <qquickimageprovider.h>
#endif
//foo namespace to force the linker to link the backing library composed only of qml files
namespace fooQtQrDec
{
QString fooPrint(void);
};

class QRImageDecoder : public QObject
{
    Q_OBJECT
    Q_PROPERTY(QString text READ get_text NOTIFY text_changed)
    Q_PROPERTY(QString source READ get_source WRITE set_source NOTIFY source_changed)

    QML_ELEMENT
    QML_SINGLETON

public:
    QRImageDecoder()
    {
#ifdef USE_EMSCRIPTEN
        m_decoder=this;
#endif
    };

#ifdef USE_EMSCRIPTEN
    Q_INVOKABLE void start()const;
    Q_INVOKABLE void stop()const;
#endif
    Q_INVOKABLE void requestPermision();
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
    void reload(int offset, int width, int height);
#endif
    void set_source(const QString &file );
signals:
    void text_changed();
    void source_changed();
    void permissionRequested(bool);

private:
#ifdef USE_EMSCRIPTEN
    static QRImageDecoder* m_decoder;
    void setid();
#endif
    void decodePicture(QImage picture);
    QString text,source;
};

#ifdef USE_EMSCRIPTEN
class WasmImageProvider : public QQuickImageProvider
{
public:
    WasmImageProvider():QQuickImageProvider(QQuickImageProvider::Image)
    {

    }
    QImage requestImage(const QString &id, QSize *size, const QSize &requestedSize) override;
    static QImage img;
};

#endif
