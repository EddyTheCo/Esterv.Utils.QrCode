import QtQuick 2.0
Item
{
    id:root
    signal gotdata(string data);
    function stop() {
	QRImageDecoder.stop();
        }

    Connections {
        target: QRImageDecoder
        function onText_changed(boo) {
            root.gotdata(QRImageDecoder.text)
        }
    }
	MyButton
    {
        id:startcamera
        anchors.centerIn: root
        text:qsTr("ScanQr")
        onClicked:
        {
		
	QRImageDecoder.start();
        }
    }
}


