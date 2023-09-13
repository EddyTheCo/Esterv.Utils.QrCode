#include "qrcodedec.hpp"
#include "Qrimagedecoder.hpp"
#include <QQuickImageProvider>
#include <QDebug>
#include<QImage>
#ifdef USE_EMSCRIPTEN
#include <emscripten/bind.h>
#endif
using namespace qrcodedec;

QRImageDecoder* QRImageDecoder::m_decoder=nullptr;
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
    decodePicture(picture);


}
void QRImageDecoder::decodePicture(QImage& picture)
{
    picture.convertTo(QImage::Format_Grayscale8);
    auto str = decode_grey(picture.bits(), picture.height(),picture.bytesPerLine());
    auto qstr=QString::fromStdString(str);
    if(qstr!="")
    {
        text=qstr;
        emit text_changed();
    }
}
void QRImageDecoder::set_data(unsigned char* img,int rows ,int cols)
{
    QImage picture(img,cols,rows,QImage::Format_RGBA8888);
    decodePicture(picture);
}
#ifdef USE_EMSCRIPTEN
EMSCRIPTEN_BINDINGS(qrdecoder) {
    emscripten::class_<QRImageDecoder>("QRImageDecoder")
        .function("set_data", &QRImageDecoder::set_data);
}
#endif
