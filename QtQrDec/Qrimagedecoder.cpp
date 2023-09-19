#include "qrcodedec.hpp"
#include "Qrimagedecoder.hpp"
#include <QDebug>
#include<QImage>
#include <QQuickImageProvider>
using namespace qrcodedec;

namespace fooQtQrDec
{
QString fooPrint(void)
{
    return "https://forum.qt.io/post/762513";
}
}

#ifdef USE_EMSCRIPTEN
#include <QRandomGenerator>
#include <emscripten.h>
#include <emscripten/bind.h>
QRImageDecoder* QRImageDecoder::m_decoder=nullptr;

EMSCRIPTEN_BINDINGS(qrdecoder) {
    emscripten::class_<QRImageDecoder>("QRImageDecoder")
        .function("reload", &QRImageDecoder::reload,emscripten::allow_raw_pointers())
        .class_function("getdecoder", &QRImageDecoder::getdecoder, emscripten::allow_raw_pointers());
}

EM_JS(void, call_start, (), {

    if ('mediaDevices' in navigator && 'getUserMedia' in navigator.mediaDevices) {
        stream = navigator.mediaDevices.getUserMedia({  video: { facingMode: 'environment' }, audio: false }).then((stream) => {
                         let settings = stream.getVideoTracks()[0].getSettings();
                         let width = settings.width;
                         let height = settings.height;

                         if(document.querySelector("#qrvideo")=== null)
                         {
                             var elemDiv = document.createElement('div');
                             elemDiv.style.cssText = 'display:none; position:absolute;width:100%;height:100%;';
                             elemDiv.innerHTML += '<video controls autoplay id="qrvideo" width="'+width+'px" height="'+height+'px"></video><canvas id="qrcanvas" width="'+width+'px" height="'+height+'px" ></canvas></div>';
                             document.body.appendChild(elemDiv);
                         }
                         let video = document.querySelector("#qrvideo");
                         let canvas = document.querySelector("#qrcanvas");

                         video.srcObject = stream;
                         window.localStream = stream;
                         getimage=setInterval(function() {
                                 //You need to define qtQR module when loading the module of the qt application.
                                 canvas.getContext('2d').drawImage(video, 0, 0, canvas.width, canvas.height);
                                 let imageData = canvas.getContext('2d').getImageData(0, 0, canvas.width, canvas.height);
                                 var data=imageData.data.buffer;
                                 var uint8Arr = new Uint8Array(data);
                                 const numBytes = uint8Arr.length * uint8Arr.BYTES_PER_ELEMENT;
                                 const dataPtr = qtQR.module()._malloc(numBytes);
                                 const dataOnHeap = new Uint8Array(qtQR.module().HEAPU8.buffer, dataPtr, numBytes);
                                 dataOnHeap.set(uint8Arr);

                                 qtQR.module().QRImageDecoder.getdecoder().reload(dataOnHeap.byteOffset,video.width,video.height);
                                 qtQR.module()._free(dataPtr);
                             }, 100);

                     }).catch(alert);


    }




});

EM_JS(void, call_stop, (), {
    try {
        getimage;
        clearInterval(getimage);
        localStream.getVideoTracks()[0].stop();
    }catch(e) {
        e; // => ReferenceError
        console.log('getimage is not defined');
    }
});

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
void QRImageDecoder::decodePicture(QImage picture)
{
    picture.convertTo(QImage::Format_Grayscale8,Qt::MonoOnly);
    auto str = decode_grey(picture.bits(), picture.height(),picture.bytesPerLine());
    auto qstr=QString::fromStdString(str);
    if(qstr!="")
    {
        text=qstr;
        emit text_changed();
    }
}
#ifdef USE_EMSCRIPTEN
QImage WasmImageProvider::img=QImage();
QImage WasmImageProvider::requestImage(const QString &id, QSize *size, const QSize &requestedSize)
{
    return img;
}
void QRImageDecoder::reload(int offset,  int width, int height)
{
    auto imgarr = reinterpret_cast<uchar*>(offset);
    WasmImageProvider::img=QImage(imgarr,width,height,QImage::Format_RGBA8888);
    setid();
    decodePicture(WasmImageProvider::img);
}
void QRImageDecoder::setid()
{
    QByteArray seed;
    auto buffer=QDataStream(&seed,QIODevice::WriteOnly | QIODevice::Append);

    quint32 value = QRandomGenerator::global()->generate();
    buffer<<value;
    source=seed.toHex();
    emit source_changed();
}
#endif
