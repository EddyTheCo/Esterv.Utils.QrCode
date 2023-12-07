import QtQuick
import QtQuick.Controls
import QtQuick.Layouts
import Esterv.Styles.Simple
import Esterv.CustomControls.QrDec
import Esterv.CustomControls

ApplicationWindow {
    visible: true
    id:window

    background:Rectangle
    {
        color:Style.backColor1
    }
    ThemeSwitch
    {
        id:themeswitch
        width:45
        height:width
    }
    QrTextField
    {
        anchors.top:themeswitch.bottom
        anchors.horizontalCenter:parent.horizontalCenter
        width:300
        height:60
        popWidth:parent.width*0.5
        popHeight:parent.height*0.5
    }






}
