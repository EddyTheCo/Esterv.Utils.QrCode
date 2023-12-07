
import QtQuick
import QtQuick.Controls
import QtQuick.Layouts
import Esterv.Styles.Simple
import Esterv.CustomControls.QrGen
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
    }

    QrGenImage
    {
        anchors.horizontalCenter:parent.horizontalCenter
        anchors.top:themeswitch.bottom
        width:parent.width*0.5
        height:parent.height*0.5
        //data:"https://https://eddytheco.github.io/"
    }









}
