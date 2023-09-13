import QtQuick 2.0
import QtMultimedia
import QtQrDec
Item
{
    id:root
    property alias textdata : decoder.text
    VideoOutput {
        id: videoOutput
        anchors.fill: root
    }
    Camera {
        id: camera
        active: true
    }
    QRImageDecoder{
        id:decoder
    }

    CaptureSession {
        id: capturesession
        camera: camera
        videoOutput: videoOutput
        imageCapture: ImageCapture {
            id: imageCapture
            onImageCaptured: {
                decoder.source = imageCapture.preview
            }

        }
    }
    Timer {
        id: timer
        interval: 500; running: true; repeat: true
        onTriggered: imageCapture.capture()
    }
}


