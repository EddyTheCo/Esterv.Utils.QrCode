#include<QObject>
#include<QString>
#include <QtQml/qqmlregistration.h>

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
    };
#ifdef USE_EMSCRIPTEN
    Q_INVOKABLE void start()const;
    Q_INVOKABLE void stop()const;
#endif
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
    void set_source(const QString &file );
    void set_data(unsigned char* img,int rows ,int cols);
signals:
    void text_changed();
    void source_changed();

private:
#ifdef USE_EMSCRIPTEN
    static QRImageDecoder* m_decoder;
#endif
    void decodePicture(QImage& picture);
    QString text,source;

};



