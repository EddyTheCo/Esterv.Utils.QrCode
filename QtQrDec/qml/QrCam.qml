import QtQuick 2.0
import QtQuick.Controls
import QtQuick.Layouts
import MyDesigns
import QtQrDec

QrQmlCamera
{
    id:qrscanner
    property bool showClose:false;

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
    }
    CloseButton
    {
        id:cbutton
        anchors.right: parent.right
        anchors.top: parent.top
        width: parent.width*0.15
        height:width
        visible: qrscanner.showClose
        onClicked:
        {
            qrscanner.stop();
            qrscanner.visible=false;
        }
    }
}
