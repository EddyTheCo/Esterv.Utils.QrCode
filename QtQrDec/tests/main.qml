import QtQuick 2.0
import QtQml
import Qrdecoder 1.0
import QtQuick.Controls
import QtQuick.Dialogs
import QtMultimedia

Window {
    visible: true
    width: 800
    height:800
    title: qsTr("Qr code decoding")
    color: "#161616"

    VideoOutput {
        id: videoOutput
        anchors.centerIn: parent
        width:800
        height:400
    }
    Camera {
                id: camera
                active: false
            }
    CaptureSession {
        id: capturesession
        camera: camera
        videoOutput: videoOutput
        imageCapture: ImageCapture {
            id: imageCapture
            onImageCaptured: {
                CodeDec.source = imageCapture.preview
            }

        }

    }

    Connections {
        target: CodeDec
        function onTextChanged() {
            timer.stop();
        }
    }

    Timer {
        id: timer
        interval: 500;  repeat: true
        onTriggered: imageCapture.capture()
    }


  Button {
        id: scanbutt
        enabled:!(timer.running)
        text: enabled?"Scan":"Scanning"
        background: Rectangle {
            opacity: scanbutt.enabled?1.0:0.3
            color: scanbutt.down ? "#d0d0d0" : "#161616"
            radius: 5
            border.color:"white"
            border.width: 2
        }
        width:150
        height:75
        anchors.top: videoOutput.bottom
        anchors.horizontalCenter:videoOutput.horizontalCenter
        onClicked: {
                timer.start();
        }
    }

    Rectangle
    {
        border.color:"white"
        border.width: 2
        radius: 10
        width:videoOutput.width/2
        height: 100
        color:"transparent"
        anchors.bottom: videoOutput.top
        anchors.horizontalCenter:videoOutput.horizontalCenter
        ScrollView {
            width:parent.width
            height:parent.height
            Label {
                color: "white"
                anchors.centerIn: parent
                width:parent.width
                text: CodeDec.text
                font.pixelSize: 22
            }
        }
    }


}
