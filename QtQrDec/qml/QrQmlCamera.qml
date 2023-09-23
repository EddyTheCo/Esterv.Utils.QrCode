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
    MediaDevices {
        id: devices
    }
    Camera {
        id: camera
        active: false
        cameraDevice: devices.defaultVideoInput
        onErrorOccurred: (error,errorString)=> {
                             console.log( devices.videoInputs);
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
    Connections {
        target: QRImageDecoder
        function onPermissionRequested(boo) {
            if(boo)
            {
                console.log( devices.videoInputs);
                console.log(camera.cameraFormat)

                devices.videoInputs.forEach((Cdev)
                                            => {
                                                if(Cdev.position===Cdev.BackFace)
                                                {
                                                    camera.cameraDevice=Cdev;
                                                }
                                            });


                camera.start();
                timer.start();
                startcamera.visible=false;
            }
        }
    }

    CaptureSession {
        id: capturesession
        camera: camera
        videoOutput: videoOutput
        imageCapture: ImageCapture {
            id: imageCapture
            onErrorOccurred:(requestId, error, message)=> {
                                console.log("capture error:",message)

            }

            onImageCaptured: {
                console.log("onImageCaptured");
                QRImageDecoder.source = imageCapture.preview
            }

        }
    }
    Timer {
        id: timer
        interval: 500; running: false; repeat: true
        onTriggered:
        {

            if( imageCapture.readyForCapture )
            {
                imageCapture.capture();
            }
        }
    }
    MyButton
    {
        id:startcamera
        anchors.centerIn: root
        text:qsTr("ScanQr")
        onClicked:
        {
            QRImageDecoder.requestPermision();
        }
        width:100
        height:width*0.5
    }
}


