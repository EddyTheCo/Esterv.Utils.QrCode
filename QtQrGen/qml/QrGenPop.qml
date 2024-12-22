import QtQuick 2.0
import QtQuick.Controls
import QtQuick.Layouts
import Esterv.CustomControls
import Esterv.Styles.Simple

Popup {
    id: control
    required property string textData
    property bool showClose: false

    ColumnLayout {
        anchors.fill: parent
        Item {
            Layout.fillHeight: true
            Layout.fillWidth: true
            Layout.minimumHeight: 50
            Layout.maximumHeight: 100
            Switch {
                id: showdata
                text: qsTr("Show text")
            }
            CloseButton {
                id: cbutton
                anchors.top: parent.top
                radius: width
                anchors.right: parent.right
                visible: control.showClose

                flat: true
                onClicked: {
                    control.visible = false;
                }
            }
        }
        Item {
            Layout.minimumHeight: 100
            Layout.minimumWidth: 200
            Layout.fillWidth: true
            Layout.fillHeight: true
            ScrollView {
                anchors.fill: parent
                TextArea {
                    id: tex
                    text: control.textData
                    readOnly: true
                    wrapMode: Text.Wrap
                }
            }
            visible: showdata.checked
        }

        QrGenImage {
            id: qrgenimage
            textData: control.textData
            visible: !tex.visible
            Layout.fillHeight: true
            Layout.fillWidth: true
            Layout.margins: 0
        }
    }
}
