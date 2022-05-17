import QtQuick.Window 2.11
import QtQuick 2.11
import QtQuick.Layouts 1.11
import QtQuick.Controls 2.0
import QmlWatcher 1.0
Window {
    id: root
    minimumWidth: 400
    maximumWidth: 500
    maximumHeight: 200
    width: 500
    height: 200
    title: "qml预览器"
    visible: true
//    flags: Qt.WindowCloseButtonHint
    QmlWatcher {
        id: watcher
        onWatcherClose:{
            root.visible=true;
        }
    }
    ColumnLayout {
        anchors.fill: parent
        Layout.alignment: Qt.AlignLeft
        RowLayout {
            Layout.fillWidth: true
            Layout.fillHeight: true
            Text {
                color: "darkslategrey"
                font.pixelSize: 20
                text: qsTr("basicPath: ")
            }
            XEditText {
                Layout.preferredHeight: parent.height
                Layout.fillWidth: true
                id: et_qmlpath
                text: watcher.basicPath
            }

        }
        RowLayout {

            Layout.fillHeight: true
            Layout.fillWidth: true
            Text {
                color: "darkslategrey"
                font.pixelSize: 20
                text: qsTr("qmlFile: ")
            }
            XEditText {
                Layout.preferredHeight: parent.height
                Layout.fillWidth: true
                id: et_qmlfile
                text: watcher.qmlFile
                onDoubleClicked: {
                }
            }
        }
        RowLayout {
            Layout.fillHeight: true
            Layout.fillWidth: true

            Text {
                color: "darkslategrey"
                font.pixelSize: 20
                text: qsTr("importPath: ")
            }
            XEditText {
                Layout.preferredHeight: parent.height
                Layout.fillWidth: true
                id: et_qmlimport
                text: watcher.importPath
                onDoubleClicked: {

                }
            }
        }
        RowLayout {

            Button {
                Layout.fillWidth: true
                Layout.margins: 10
                text: qsTr("开启实时预览")
                onClicked: {
                   watcher.openListen();
                   root.visible=false;
                }
            }
//            Button {
//                Layout.fillWidth: true
//                Layout.margins: 10
//                text: qsTr("关闭实时预览")
//                onClicked: {
//                    warcher.closeListen();
//                }
//            }
        }
    }
}
