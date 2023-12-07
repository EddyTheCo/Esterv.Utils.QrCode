import QtQuick.Controls
import QtQuick
import QtQml
import Esterv.Styles.Simple

Control
{
     id:control
     required property string textData
     implicitWidth: 100
     implicitHeight: 100
     background: Rectangle {
             radius: Math.min(width,height)*0.8*Style.roundedScale/Style.Scale.Full
             color:Style.backColor3
     }
     Image {
         id:img
         anchors.centerIn:parent
         sourceSize.width: Math.min(control.width,control.height)-control.background.radius-10
         source: "image://qrcode/"+Style.frontColor1+"/"+control.textData
     }
}
