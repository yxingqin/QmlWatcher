import QtQuick 2.0
import XQuick 1.0
import QtQuick.Window 2.11

Rectangle {
    width:100
    height:100
    // title:"qml"
    // visible:true
    XButton {

        anchors.centerIn:parent
        onClick: {
            console.log("Xbutton");
        }
    }
    MyItem {
        width:100
        height:100
        color:"red"
    }
}