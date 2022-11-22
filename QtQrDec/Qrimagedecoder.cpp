#include "qrcodedec.hpp"
#include "Qrimagedecoder.hpp"
#include <QQuickImageProvider>
#include <QDebug>
#include<QImage>
using namespace qrcodedec;


void QRImageDecoder::set_source(const QString & path )
{
    if(path=="") return;
    QImage picture;
    auto myQmlEngine = qmlEngine(this);
        if(myQmlEngine==nullptr)
            return;

        QUrl imageUrl(path);
        qDebug()<<imageUrl;
        auto provider = reinterpret_cast<QQuickImageProvider*>( myQmlEngine->imageProvider(imageUrl.host()));

        if (provider->imageType()==QQuickImageProvider::Image){
            picture = provider->requestImage(imageUrl.path().remove(0,1),nullptr,QSize());

        }

        picture.convertTo(QImage::Format_Grayscale8);
        auto str = decode_grey(picture.bits(), picture.height(),picture.bytesPerLine());  // Check why the +2
        auto qstr=QString::fromStdString(str);
        qDebug()<<qstr;
        if(qstr!="")
        {
            text=qstr;
            emit text_changed();
        }


}
