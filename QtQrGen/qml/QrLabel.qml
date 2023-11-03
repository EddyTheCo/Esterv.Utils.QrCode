import QtQuick.Controls
import QtQuick
import MyDesigns
import QtQrGen



Text
{
    id:root
    property string description:"";
    required property string address;

    PayQrPop
    {
        id:popup_
        address:root.address
        description:root.address
        visible:false
        closePolicy: Popup.CloseOnPressOutside
        anchors.centerIn: Overlay.overlay
        focus: false
        modal:false
        width:300
    }

    text:((root.description)?("<b>"+ root.description +':   </b>'):'') +' <font color=\"'+CustomStyle.frontColor2+'\">'+ root.address +'</font>'
    elide:Text.ElideRight
    horizontalAlignment: TextEdit.AlignLeft
    fontSizeMode:Text.VerticalFit
    color:CustomStyle.frontColor1
    MouseArea {
        anchors.fill: parent
        onClicked: popup_.visible=true;
    }
}
