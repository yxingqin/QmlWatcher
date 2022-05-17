import QtQuick 2.0
import XQuick 1.0


Rectangle {
    width: 640
    height: 480
    XButton {
        onClick: {
            console.log("我被点击了")
        }
    }
    MyItem {
        width: 100
        height: 100
        anchors.centerIn: parent
        color: "red"
        clip: false
        Text {
            anchors.centerIn: parent
            font.pixelSize: 100
            text: "Qml study"

        }
    }
}
