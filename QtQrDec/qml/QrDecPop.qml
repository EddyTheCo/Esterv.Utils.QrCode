import QtQuick 2.0
import QtQuick.Controls
import QtQuick.Layouts
import Esterv.Styles.Simple
import Esterv.CustomControls.QrDec
import Esterv.CustomControls

Popup
{
    id:control
    property bool showClose:true;
    property string data:""
    onOpened: QRImageDecoder.start()
    onClosed: QRImageDecoder.stop()
    Connections {
        target: QRImageDecoder
        function onDecodedQR(data) {
            if(control.enabled&&control.visible)
            {
                control.data=data;
                control.visible=false;
            }
        }
    }
    QrCam
    {
        anchors.fill: parent
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
            control.visible=false;
        }
    }
}
