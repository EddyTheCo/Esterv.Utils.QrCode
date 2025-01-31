import QtQuick
import QtQuick.Controls
import QtQuick.Layouts
import Esterv.Styles.Simple
import Esterv.CustomControls.QrDec
import Esterv.CustomControls

ApplicationWindow {
    id: window
    visible: true

    background: Rectangle {
        color: Style.backColor1
    }
    ThemeSwitch {
        id: themeswitch
        width: 45
        height: width
    }
    QrTextField {
        anchors.top: themeswitch.bottom
        anchors.horizontalCenter: parent.horizontalCenter
        width: 300
        height: 60
        popWidth: Math.max(parent.width * 0.5, 300)
        popHeight: Math.max(parent.height * 0.5, 500)
    }
}
