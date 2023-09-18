import QtQuick 2.0
import QtQuick.Controls
import QtQuick.Layouts
import MyDesigns

Popup {
    id: root
    required property string address;
    property string url;
    required property string description;
    property alias textarea:tex
    property alias qrcode:qrcode_;

    background: Rectangle
    {
        id:bck
        color:CustomStyle.backColor1
        border.width:1
        border.color:CustomStyle.frontColor1
        radius:Math.min(width,height)*0.05

    }

    modal: true
    focus: true

    ColumnLayout
    {
        anchors.fill: parent
        spacing:10
        MyTextArea
        {
            id:tex
            Layout.fillWidth: true
            Layout.fillHeight:  true
            Layout.alignment: Qt.AlignTop|Qt.AlignHCenter
            Layout.minimumHeight:  100
            label.visible: false
            textarea.text: root.description
            textarea.readOnly: true
            textarea.wrapMode: Text.Wrap
        }

        AddressQr
        {
            id:qrcode_
            address:root.address
            url:root.url
            Layout.preferredWidth: tex.width*0.75
            Layout.preferredHeight: width

            Layout.alignment: Qt.AlignCenter
        }
    }



}

