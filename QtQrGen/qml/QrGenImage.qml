import QtQuick.Controls
import QtQuick
import QtQml
import Esterv.Styles.Simple

Rectangle {
    id:control
    required property string textData
    implicitWidth: 100
    implicitHeight: 100

    radius: Math.min(width,height)*0.8*Style.roundedScale/Style.Scale.Full
    color:Style.backColor3

    Image {
        id:img
        anchors.centerIn:parent
        sourceSize.width: Math.min(control.width,control.height)-control.radius-10
        source: "image://qrcode/"+Style.frontColor1+"/"+control.textData
        MouseArea {
            anchors.fill: img
            id:mousearea
            hoverEnabled:true
            onClicked:
            {
                console.log(control.textData);
            }
            ToolTip.visible: mousearea.containsMouse
            ToolTip.timeout: 2000
            ToolTip.text:qsTr("Copy")
        }
    }



}
