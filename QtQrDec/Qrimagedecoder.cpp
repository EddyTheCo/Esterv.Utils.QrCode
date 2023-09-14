#include "qrcodedec.hpp"
#include "Qrimagedecoder.hpp"
#include <QQuickImageProvider>
#include <QDebug>
#include<QImage>

using namespace qrcodedec;


namespace fooQtQrDec
{
QString fooPrint(void)
{
    return "fooPrint";
}
}
#ifdef USE_EMSCRIPTEN
#include <emscripten.h>
#include <emscripten/bind.h>
QRImageDecoder* QRImageDecoder::m_decoder=nullptr;

EM_JS(void, call_start, (), {
    let video = document.querySelector("#qrvideo");
    let stream = await navigator.mediaDevices.getUserMedia({ video: true, audio: false });
    video.srcObject = stream;
    let canvas = document.querySelector("#qrcanvas");
    getimage=setInterval(function() {
            let imageData = canvas.getContext('2d').getImageData(0, 0, video.width, video.height);
            var data=imageData.data.buffer;
            var uint8Arr = new Uint8Array(data);
            if (qtLoader.module()) {
                qtLoader.module().QRImageDecoder.getdecoder().set_data(uint8Arr,video.width,video.height);
            }
        }, 500);
    $("#qrDecoder").toggle();
});
EM_JS(void, call_stop, (), {
      clearInterval(getimage);
    $("#qrDecoder").toggle();
});
EMSCRIPTEN_BINDINGS(qrdecoder) {
    emscripten::class_<QRImageDecoder>("QRImageDecoder")
        .function("set_data", &QRImageDecoder::set_data)
    .class_function("get_editor", &QRImageDecoder::getdecoder, emscripten::allow_raw_pointers());

}
void QRImageDecoder::start()const
{
    call_start();
}
void QRImageDecoder::stop()const
{
    call_stop();
}
#endif

void QRImageDecoder::set_source(const QString & path )
{
    if(path=="") return;
    QImage picture;
    auto myQmlEngine = qmlEngine(this);
    if(myQmlEngine==nullptr)
        return;

    QUrl imageUrl(path);
    auto provider = reinterpret_cast<QQuickImageProvider*>( myQmlEngine->imageProvider(imageUrl.host()));

    if (provider->imageType()==QQuickImageProvider::Image){
        picture = provider->requestImage(imageUrl.path().remove(0,1),nullptr,QSize());

    }
    if(!picture.isNull())decodePicture(picture);

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
