import QtQuick.Controls
import QtQuick
import MyDesigns

Rectangle {
    id:root
    required property string address
    property string url
    radius: 10

    TextClipboard
    {
        id:tclip
        text:root.address
    }

    Image {
        id:img
        anchors.centerIn:parent
        sourceSize.width: root.width-10
        source: "image://qrcodeblack/"+root.address
        MouseArea {
            anchors.fill: img
            hoverEnabled :true
            onEntered: tooltip.visible=!tooltip.visible
            onExited: tooltip.visible=!tooltip.visible
            onClicked:
            {

               tclip.copy();
                if(root.url)
                {
                    Qt.openUrlExternally(root.url)
                }
            }
        }
    }
    ToolTip
    {
        id:tooltip
        visible: false
        text:qsTr("Copy")
    }


}
