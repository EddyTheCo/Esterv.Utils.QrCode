#include<QObject>
#include<QString>
#include <QtQml/qqmlregistration.h>

class QRImageDecoder : public QObject
{
    Q_OBJECT
    Q_PROPERTY(QString text READ get_text NOTIFY text_changed)
    Q_PROPERTY(QString source READ get_source WRITE set_source NOTIFY source_changed)
    QML_ELEMENT

public:
    QRImageDecoder(){
        m_decoder=this;
    };
    QString get_text(void)
    {
        return text;
    }
    QString get_source(void)
    {
        return source;
    }
    static QRImageDecoder* getdecoder(){return m_decoder;};
    void set_source(const QString &file );
    void set_data(unsigned char* img,int rows ,int cols);
signals:
    void text_changed();
    void source_changed();
private:
    void decodePicture(QImage& picture);
    QString text,source;
    static QRImageDecoder* m_decoder;
};



