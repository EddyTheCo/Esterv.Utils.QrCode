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
    ColumnLayout {
        anchors.fill: parent
        RowLayout {
            id: rowlayout
            Layout.fillHeight: true
            Layout.fillWidth: true
            Layout.minimumHeight: 70
            Layout.minimumWidth: 300
            ThemeSwitch {
                id: themeswitch
            }
            Label {
                id: label
                Layout.fillHeight: true
                Layout.fillWidth: true
                horizontalAlignment: Text.AlignHCenter
                verticalAlignment: Text.AlignBottom
                text: ""
                elide: Text.ElideRight
                color: Style.frontColor2
            }

            Switch {
                id: onoff

                onCheckedChanged: {
                    (onoff.checked) ? QRImageDecoder.start() : QRImageDecoder.stop();
                }
            }
        }

        QrCam {
            Layout.fillHeight: true
            Layout.fillWidth: true
            Layout.margins: 20
        }
        Connections {
            target: QRImageDecoder
            function onDecodedQR(data) {
                label.text = data;
            }
        }
    }
}
