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


     Image {
         id:img
         anchors.centerIn:parent
         sourceSize.width: Math.min(control.width,control.height)-30
         source: "image://qrcode/"+Style.frontColor1+"/"+control.textData
     }
}
