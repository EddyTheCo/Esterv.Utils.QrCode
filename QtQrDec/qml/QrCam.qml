import QtQuick 2.0
import QtQuick.Controls
import QtQuick.Layouts
import Esterv.Styles.Simple
import Esterv.CustomControls
import Esterv.CustomControls.QrDec
Image
{
    id:control
    property bool showClose:true;
    signal gotdata(string data);

    cache : false
    source: "image://wasm/"+QRImageDecoder.source

    Connections {
        target: QRImageDecoder
        function onText_changed(boo) {
            control.gotdata(QRImageDecoder.text)
        }
    }

    Switch {
        id:useTorch
        opacity: checked ? 0.75 : 0.25
        anchors.bottom: parent.bottom
        anchors.horizontalCenter: parent.horizontalCenter
        visible:QRImageDecoder.hasTorch
        onCheckedChanged:
        {
            QRImageDecoder.useTorch=useTorch.checked;
        }
        text:qsTr("Torch")
    }
    CloseButton
    {
        id:cbutton
        anchors.right: parent.right
        anchors.top: parent.top
        visible: control.showClose
        radius:width
        flat:true
        onClicked:
        {
            QRImageDecoder.stop();
            control.visible=false;
        }
    }
}
