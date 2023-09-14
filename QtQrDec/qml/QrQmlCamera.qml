import QtQuick 2.0
import QtMultimedia
import QtQrDec
import MyDesigns
Item
{
    id:root
    signal gotdata(string data);
    function stop() {
        timer.stop();
        camera.stop();
        startcamera.visible=true;
        }

    VideoOutput {
        id: videoOutput
        anchors.fill: root
    }
    Camera {
        id: camera
        active: false
        onErrorOccurred: (error,errorString)=> {
                             console.log(errorString)
                             console.log(error)
                         }

    }
    Connections {
        target: QRImageDecoder
        function onText_changed(boo) {
            root.gotdata(QRImageDecoder.text)
        }
    }
    CaptureSession {
        id: capturesession
        camera: camera
        videoOutput: videoOutput
        imageCapture: ImageCapture {
            id: imageCapture
            onImageCaptured: {
                QRImageDecoder.source = imageCapture.preview
            }

        }
    }
    Timer {
        id: timer
        interval: 500; running: false; repeat: true
        onTriggered: imageCapture.capture()
    }
    MyButton
    {
        id:startcamera
        anchors.centerIn: root
        text:qsTr("ScanQr")
        onClicked:
        {
            camera.start();
            timer.start();
            startcamera.visible=false;
        }
    }
}


