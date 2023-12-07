import QtQuick 2.0
import QtQuick.Controls
import QtQuick.Layouts
import Esterv.Styles.Simple
import Esterv.CustomControls.QrDec

TextField
{
    id:control
    property int popWidth:300
    property int popHeight:500
    rightPadding: control.height*0.9
    QrDecPop
    {
        id:qrpop
        visible:false
        closePolicy: Popup.CloseOnPressOutside
        anchors.centerIn: Overlay.overlay
        width:control.popWidth
        height:control.popHeight
    }
    text:qrpop.data
    Rectangle {
        id:qricon
        height:Math.min(parent.height,font.pixelSize)
        width:height
        anchors.right: parent.right
        anchors.verticalCenter: control.verticalCenter
        color: "transparent"
        visible: !control.text&&control.enabled
        ShaderEffect {
            id: shader
            property var src: qricon;
            property color fcolor:Style.frontColor2
            property var pixelStep: Qt.vector2d(1/src.width, 1/src.height)
            fragmentShader: "qrc:/esterVtech.com/imports/Designs/frag/qrscanner.frag.qsb"
            anchors.fill: parent
        }
        MouseArea {
            anchors.fill: parent
            onClicked: {
                qrpop.open();
            }
        }
    }


}
