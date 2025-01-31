#include "esterv/utils/qr_image_decoder.hpp"
#include <QGuiApplication>
#include <QImage>
#include <QQuickImageProvider>

#ifdef USE_EMSCRIPTEN

#include <emscripten.h>
#include <emscripten/bind.h>

EMSCRIPTEN_BINDINGS(qrdecoder) {
  emscripten::class_<Esterv::Utils::QrDec::QRImageDecoder>("QRImageDecoder")
      .function("reload", &Esterv::Utils::QrDec::QRImageDecoder::reload,
                emscripten::allow_raw_pointers())
      .class_function("instance",
                      &Esterv::Utils::QrDec::QRImageDecoder::instance,
                      emscripten::allow_raw_pointers());
}
// clang-format off
EM_JS(void, js_start, (), {
    if ('mediaDevices' in navigator && 'getUserMedia' in navigator.mediaDevices) {
        stream = navigator.mediaDevices.getUserMedia({video : {facingMode : 'environment'}, audio : false}).then((stream) => {
                      const settings = stream.getVideoTracks()[0].getSettings();
                      const width = settings.width;
                      const height = settings.height;

                      if (document.querySelector("#qrvideo") === null) {
                        let elemDiv = document.createElement('div');
                        elemDiv.style.cssText = 'display:none; position:absolute;width:100%;height:100%;';
                        elemDiv.innerHTML += '<video controls autoplay id="qrvideo" width="' +
                            width + 'px" height="' + height +
                            'px"></video><canvas id="qrcanvas" width="' +
                            width + 'px" height="' + height +
                            'px" ></canvas></div>';
                        document.body.appendChild(elemDiv);
                      }
                      const video = document.querySelector("#qrvideo");
                      video.srcObject = stream;
                      window.localStream = stream;

                      let canvas = document.querySelector("#qrcanvas");
                      let ctx = canvas.getContext("2d", { willReadFrequently: true });
                      const processFrame = function() {
                        ctx.drawImage(video, 0, 0, canvas.width, canvas.height);
                        const imageData = ctx.getImageData(0, 0, canvas.width, canvas.height);
                        const sourceBuffer = imageData.data;
                        const buffer = _malloc(sourceBuffer.byteLength);
                        HEAPU8.set(sourceBuffer, buffer);
                        Module.QRImageDecoder.instance().reload(buffer, video.width, video.height);
                        _free(buffer);
                        if (window.localStream.active) {
                          requestAnimationFrame(processFrame);
                        } else {
                          ctx.clearRect(0, 0, canvas.width, canvas.height);
                        }
                      };
                      processFrame();
                    })
            .catch(alert);
    }
});

EM_JS(void, js_stop, (), {
    if (window.localStream)
        window.localStream.getVideoTracks()[0].stop();
});
// clang-format on
namespace Esterv::Utils::QrDec {
#else
#include <thread>
#if QT_CONFIG(permissions)
#include <QPermission>
#endif

namespace Esterv::Utils::QrDec {

void QRImageDecoder::getCamera(void) {
  const QList<QCameraDevice> cameras = QMediaDevices::videoInputs();
  if (cameras.size()) {
    QCameraDevice best = cameras.front();
    for (const QCameraDevice &cameraDevice : cameras) {

      if (cameraDevice.position() == QCameraDevice::BackFace) {
        best = cameraDevice;
      }
    }
    m_camera = new QCamera(best, this);
  }
}

#endif
QRImageDecoder *QRImageDecoder::instance() {
  static QRImageDecoder *instance = new QRImageDecoder();
  return instance;
}
QRImageDecoder::QRImageDecoder(QObject *parent)
    : QObject(parent)

#ifndef USE_EMSCRIPTEN
      ,
      captureSession{new QMediaCaptureSession(this)},
      videoSink{new QVideoSink(this)}
#endif
{
#ifndef USE_EMSCRIPTEN
  std::thread decoding_thread([this]() {
    std::unique_lock lk(m_decoding_mutex);
    while (m_decode_running) {
      m_decoding_variable.wait(lk);
      decodePicture();
    }
  });
  decoding_thread.detach();
  captureSession->setVideoOutput(videoSink);
  QObject::connect(videoSink, &QVideoSink::videoFrameChanged, this,
                   [=](const QVideoFrame &Vframe) {
                     if (m_camera && m_camera->isActive() && Vframe.isValid()) {
                       auto picture = Vframe.toImage();
                       WasmImageProvider::img = picture;
                       setid();
                       if (m_state == Ready) {
                         {
                           std::lock_guard lk(m_decoding_mutex);
                           m_state = Decoding;
                         }
                         m_decoding_variable.notify_one();
                       }
                     }
                   });
  connect(this, &QRImageDecoder::useTorchChanged, this, [=]() {
    if (m_camera->isActive() && m_useTorch)
      m_camera->setTorchMode(QCamera::TorchOn);
    else
      m_camera->setTorchMode(QCamera::TorchOff);
  });
#endif
};
void QRImageDecoder::stop() {
#ifdef USE_EMSCRIPTEN
  js_stop();
#else
  if (m_camera)
    m_camera->stop();
#endif
};
void QRImageDecoder::start() {
#ifdef USE_EMSCRIPTEN
  clear();
  js_start();
#elif QT_CONFIG(permissions)
  QCameraPermission cPermission;
  switch (qApp->checkPermission(cPermission)) {
  case Qt::PermissionStatus::Undetermined:
    qApp->requestPermission(cPermission, this, &QRImageDecoder::start);
    return;
  case Qt::PermissionStatus::Denied:
    return;
  case Qt::PermissionStatus::Granted:
    if (!m_camera) {
      getCamera();
      if (m_camera) {
        captureSession->setCamera(m_camera);
        QObject::connect(m_camera, &QCamera::activeChanged, [=](bool var) {
          if (var && m_camera->isTorchModeSupported(QCamera::TorchOn)) {
            m_hasTorch = true;
            emit hasTorchChanged();
          }
        });

        QObject::connect(m_camera, &QCamera::errorOccurred,
                         [](QCamera::Error error, const QString &errorString) {
                           qDebug() << "Camera Error:" << errorString;
                         });
      }
    }
    if (m_camera) {
      clear();
      m_camera->start();
    }

    return;
  }

#endif
}

void QRImageDecoder::decodePicture() {
  QImage picture = WasmImageProvider::img;
  picture.convertTo(QImage::Format_Grayscale8);
  const auto str = detector.decode_grey(picture.bits(), picture.height(),
                                        picture.bytesPerLine());
  const auto qstr = QString::fromStdString(str);
  if (qstr != "") {
    emit decodedQR(qstr);
  }
  m_state = QRImageDecoder::Ready;
}

QImage WasmImageProvider::img = QImage();
QImage WasmImageProvider::requestImage(const QString &id, QSize *size,
                                       const QSize &requestedSize) {
  return img;
}
void QRImageDecoder::clear(void) {
  WasmImageProvider::restart();
  setid();
}
void WasmImageProvider::restart(void) {
  WasmImageProvider::img = QImage(QSize(200, 150), QImage::Format_RGBA8888);
  WasmImageProvider::img.fill("black");
}
void QRImageDecoder::reload(int offset, int width, int height) {
  auto imgarr = reinterpret_cast<uchar *>(offset);
  WasmImageProvider::img =
      QImage(imgarr, width, height, QImage::Format_RGBA8888);
  setid();
  if (m_state == Ready) {
    m_state = Decoding;
    decodePicture();
  }
}
void QRImageDecoder::setid() {
  static quint8 index = 0;
  m_source = "qrimage" + QString::number(index);
  emit sourceChanged();
  index++;
}
}
