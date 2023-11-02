import QtQuick 2.0
import QtQuick.Controls
import QtQrDec
Item
{
    id:root
    signal gotdata(string data);
    implicitWidth: preview.implicitWidth
    implicitHeight: preview.implicitHeight
    function stop() {
        QRImageDecoder.stop();
    }
    function start() {
        QRImageDecoder.start();
    }
    Connections {
        target: QRImageDecoder
        function onText_changed(boo) {
            root.gotdata(QRImageDecoder.text)
            QRImageDecoder.clear();
        }
    }
    Image {
        id: preview
        anchors.fill: root
        cache : false
        source: "image://wasm/"+QRImageDecoder.source
    }


}
