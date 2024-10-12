import QtQuick
import QtQuick.Controls
import QtQuick.Layouts
import Esterv.Styles.Simple
import Esterv.CustomControls.QrGen
import Esterv.CustomControls

ApplicationWindow {
    id: window
    visible: true

    background: Rectangle {
        color: Style.backColor1
    }

    ThemeSwitch {
        id: themeswitch
    }

    QrText {
        anchors.horizontalCenter: parent.horizontalCenter
        anchors.top: themeswitch.bottom
        text: "smr1qp9rtwlc00ksp0mvet8ugwvqu03ygzr8s3x77w3df9qw9srm3hwk2l0v9kf"
        width: parent.width * 0.5
        font.pixelSize: 30
    }
}
