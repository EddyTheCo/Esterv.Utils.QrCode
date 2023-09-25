#include "Qrimagedecoder.hpp"
#include <QDebug>
#include<QImage>
#include <QQuickImageProvider>
#if QT_CONFIG(permissions)
#include <QPermission>
#endif
#include <QGuiApplication>
#include <QRandomGenerator>


namespace fooQtQrDec
{
QString fooPrint(void)
{
    return "https://forum.qt.io/post/762513";
}
}

#ifdef USE_EMSCRIPTEN

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
void QRImageDecoder::getCamera(void)
{
    const QList<QCameraDevice> cameras = QMediaDevices::videoInputs();
    if(cameras.size())
    {
        QCameraDevice best=cameras.front();
        for (const QCameraDevice &cameraDevice : cameras) {

            if (cameraDevice.position() == QCameraDevice::BackFace)
            {
                best=cameraDevice;
            }
        }
        m_camera=new QCamera(best,this);
        auto bvF=best.videoFormats().at(0);
        for (const QCameraFormat &format : best.videoFormats())
        {
            if(abs(format.resolution().width()*1.0-format.resolution().height())<abs(bvF.resolution().width()*1.0-bvF.resolution().height()))
            {
                bvF=format;
            }
        }
        m_camera->setCameraFormat(bvF);

    }

}
QRImageDecoder::QRImageDecoder(QObject *parent):QObject(parent),m_camera(nullptr),captureSession(new QMediaCaptureSession(this)),videoSink(new QVideoSink(this)),
    detector(new MyQRCodeDetector())
{
#ifdef USE_EMSCRIPTEN
    m_decoder=this;
#endif
    captureSession->setVideoOutput(videoSink);
    QObject::connect(videoSink,&QVideoSink::videoFrameChanged,this,[=](const QVideoFrame & Vframe)
                     {
        static size_t index=0;
        if(index>4)
            {
                         qDebug()<<"MCAMERA:videoFrameChanged";
                         auto picture=Vframe.toImage();
                         qDebug()<<"picture"<<picture;

                         WasmImageProvider::img=picture;
                         setid();
                         decodePicture(WasmImageProvider::img);
                         index=0;
        }
                         index++;
                     });
};
void QRImageDecoder::start()
{
#if QT_CONFIG(permissions)
    QCameraPermission cPermission;
    switch (qApp->checkPermission(cPermission)) {
    case Qt::PermissionStatus::Undetermined:
        qApp->requestPermission(cPermission, this,
                                &QRImageDecoder::start);
        return;
    case Qt::PermissionStatus::Denied:
        return;
    case Qt::PermissionStatus::Granted:
        qDebug()<<"PermissionStatus::Granted";
        if(!m_camera)
        {
            getCamera();
            if(m_camera)
            {
                captureSession->setCamera(m_camera);
            }

        }
        if(m_camera)
        {

            m_camera->start();

        }

        return;
    }
#endif
}

void QRImageDecoder::decodePicture(QImage picture)
{
    qDebug()<<"QRImageDecoder::decodePicture:"<<picture;
    picture.convertTo(QImage::Format_Grayscale8,Qt::MonoOnly);

    auto str = detector->decode_grey(picture.bits(), picture.height(),picture.bytesPerLine());
    WasmImageProvider::img=picture;
    setid();
    qDebug()<<"QRImageDecoder::decodePicture:"<<picture;
    auto qstr=QString::fromStdString(str);
    qDebug()<<"str:"<<qstr;
    if(qstr!="")
    {
        text=qstr;
        //emit text_changed();
    }
}

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
    source=QString::number(QRandomGenerator::global()->generate());
    emit source_changed();
}

