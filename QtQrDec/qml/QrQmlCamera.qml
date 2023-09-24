import QtQuick 2.0
import MyDesigns
import QtQrDec
Item
{

    id:root
    signal gotdata(string data);
    function stop() {
        QRImageDecoder.stop();
        startcamera.visible=true;
    }

    Connections {
        target: QRImageDecoder
        function onText_changed(boo) {
            root.gotdata(QRImageDecoder.text)

        }
    }
    Image {
        id: preview
        anchors.fill: root
        cache : false
        source: "image://wasm/"+QRImageDecoder.source
        visible: !startcamera.visible
    }

    MyButton
    {
        id:startcamera
        anchors.centerIn: root
        text:qsTr("ScanQr")
        onClicked:
        {
            QRImageDecoder.start();
            startcamera.visible=false;
        }
    }

}
