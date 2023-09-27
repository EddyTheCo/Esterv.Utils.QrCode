import QtQuick 2.0
import QtQuick.Controls
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
    Switch {
        id:useTorch
        opacity: checked ? 0.75 : 0.25
        anchors.bottom: preview.bottom
        anchors.horizontalCenter: preview.horizontalCenter
        visible:!startcamera.visible&&QRImageDecoder.hasTorch
        onCheckedChanged:
        {
            QRImageDecoder.useTorch=useTorch.checked;
        }
    }
    MyButton
    {
        id:startcamera
        anchors.centerIn: root
        text:qsTr("Scan Qr")
        onClicked:
        {
            QRImageDecoder.start();
            startcamera.visible=false;
        }
    }

}
