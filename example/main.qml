import QtQuick 2.15
import QtQuick.Layouts 1.15
import QtQuick.Controls 2.15
import QtQuick.Window 2.15

Rectangle {
    width: 400
    height: 800
    MyItem {
        color: "red"
        Text {
            anchors.centerIn: parent
            text: "text"
            font.pixelSize: 100
        }
        anchors.fill: parent
    }
}
