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
                console.log("devices:",devices.videoInputs);
                devices.videoInputs.forEach((Cdev)
                                            => {
                                                console.log("dev:",Cdev.position);
                                                if(Cdev.position===1)
                                                {
                                                    console.log("equal",Cdev.position)
                                                    camera.cameraDevice=Cdev;
                                                }
                                            });
                console.log("device:",camera.cameraDevice);
                console.log("Formats:",camera.cameraDevice.videoFormats);
                console.log("Camera.resolution:",camera.cameraFormat.resolution);
                camera.cameraFormat=camera.cameraDevice.videoFormats[0];
                camera.cameraDevice.videoFormats.forEach((form) => {

                console.log("Format.minFrameRate:",form.minFrameRate);
                console.log("Format.pixelFormat:",form.pixelFormat);
                console.log("Format.resolution:",form.resolution);
                                                         });

                console.log("Camera.resolution:",camera.cameraFormat.resolution);
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
        interval: 5000; running: false; repeat: true
        onTriggered:
        {

            if( imageCapture.readyForCapture )
            {
                console.log("READY");
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


