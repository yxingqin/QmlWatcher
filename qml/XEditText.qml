import QtQuick 2.0
import QtQuick.Controls 2.11
Rectangle {
    id: root
    border.color: "grey"
    property alias text: ti.text
    signal doubleClicked();
    TextInput {
        id: ti
        anchors.fill: parent
        font.pixelSize: 20
        text: ""
        clip: true
        MouseArea {
            anchors.fill: parent
            onDoubleClicked: {
                root.doubleClicked();
            }
            onPressed: {
                parent.focus = true
            }
        }
    }
}
