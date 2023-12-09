import QtQuick.Controls
import QtQuick

import Esterv.Styles.Simple


Text
{
    id:control
    property int popWidth:300
    property int popHeight:500
    QrGenPop
    {
        id:qrgenpop
        textData:control.text
        visible:false
        closePolicy: Popup.CloseOnPressOutside
        anchors.centerIn: Overlay.overlay
        width:control.popWidth
        height:control.popHeight
    }
    color:Style.frontColor1
    elide:Text.ElideRight
    horizontalAlignment: TextEdit.AlignLeft

    rightPadding: control.height*0.9

    Rectangle {
        id:qricon
        height:Math.min(parent.height,font.pixelSize)
        width:height
        x: parent.contentWidth
        color: "transparent"
        ShaderEffect {
            id: shader
            property var src: qricon;
            property color fcolor:Style.frontColor2
            property var pixelStep: Qt.vector2d(1/src.width, 1/src.height)
            fragmentShader: "qrc:/esterVtech.com/imports/Designs/frag/qrscanner.frag.qsb"
            anchors.fill: parent
        }

    }
    MouseArea {
        anchors.fill: parent
        onClicked: {
            qrgenpop.open();
        }
    }
}
