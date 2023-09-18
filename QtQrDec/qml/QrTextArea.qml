import QtQuick 2.0
import QtQuick.Controls
import QtQuick.Layouts
import MyDesigns

Popup
{
    id:popup_
    property string description;
    property string placeholder;
    signal clicked();

    onClosed: qrscanner.stop();
    background: Rectangle
    {
        id:bck
        color:CustomStyle.backColor1
        border.width:1
        border.color:CustomStyle.frontColor1
        radius:Math.min(width,height)*0.05
    }
    ColumnLayout
    {
        anchors.fill: popup_
        MyTextArea
        {
            id:recaddress
            label.text: (popup_.description)?popup_.description:""
            textarea.placeholderText: (popup_.placeholder)?popup_.placeholder:""
            Layout.alignment: Qt.AlignHCenter
            Layout.margins:  20
            Layout.fillWidth: true
            Layout.fillHeight: true
            Layout.maximumWidth:400
            Layout.maximumHeight: 200
            focus:true
        }
        QrQmlCamera
        {
            id:qrscanner
            Layout.alignment: Qt.AlignCenter
            Layout.margins:  5
            Layout.fillHeight: true
            Layout.fillWidth: true
            onGotdata: (data)=> {
                           qrscanner.stop();
                           recaddress.textarea.text=data;
                       }
        }
        MyButton
        {
            id:send
            Layout.alignment: Qt.AlignRight
            Layout.margins:  15
            Layout.fillHeight: true
            Layout.maximumHeight:  50
            Layout.fillWidth: true
            Layout.maximumWidth: 2*height
            enabled: recaddress.textarea.text!==""
            onClicked:
            {
                popup_.close();
                popup_.clicked();
            }
            text:qsTr("Ok")
        }

    }
}

